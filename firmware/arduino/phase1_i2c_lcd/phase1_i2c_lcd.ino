// ML-303 Phase 1 — Arduino Pro Micro firmware.
//
// Role: I2C slave on the ML-303 bus. Receives a 9-byte sequencer packet
// from the PIC18LF452 every step and renders the current state on a
// PCF8574-backed 16x2 LCD that lives on the same I2C bus.
//
// Bus topology:
//   PIC (master, 100 kHz)  ──┬── Arduino (slave 0x43, this firmware)
//                            └── LCD    (slave 0x27 or 0x3F)
//
// Multi-master note: the Arduino acts as master only when writing to the
// LCD, and only from loop() — never from the receive ISR. The PIC drives
// the bus the rest of the time. Wire's master ops yield while the bus is
// busy, so contention is handled implicitly. If you see garbled LCD text
// under heavy load, increase MIN_DISPLAY_INTERVAL_MS.

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "pins.h"

// ---- Shared protocol with PIC (must match firmware/pic/ml303_data.h) ----
#define SEQ_RUNNING  0x01
#define SEQ_ACCENT   0x02
#define SEQ_SLIDE    0x04

typedef struct __attribute__((packed)) {
  uint8_t  current_step;     // 0..15
  uint8_t  current_pattern;  // 0..127
  uint16_t tempo_bpm;        // 60..200
  uint8_t  button_state;
  uint8_t  sequencer_flags;  // SEQ_*
  uint8_t  note_value;       // MIDI 24..96
  uint8_t  velocity;         // 0..127
  uint8_t  checksum;         // XOR of preceding 8 bytes
} PIC_to_Arduino_t;

static const uint8_t PACKET_SIZE = sizeof(PIC_to_Arduino_t);  // 9 bytes
static_assert(sizeof(PIC_to_Arduino_t) == 9, "packet must be exactly 9 bytes — check struct packing");

// ---- Display timing ----
// Don't redraw faster than this — the LCD is slow and the I2C bus is
// shared. 50 ms gives a fluid feel without saturating the bus.
static const uint16_t MIN_DISPLAY_INTERVAL_MS = 50;

// ---- State ----
LiquidCrystal_I2C lcd(LCD_I2C_ADDRESS, LCD_COLS, LCD_ROWS);

// volatile because writeBuf is touched from the receive ISR.
static volatile uint8_t  writeBuf[PACKET_SIZE];
static volatile bool     packetReady = false;
static volatile uint16_t errorCount = 0;
static volatile uint32_t packetCount = 0;

// Shadow copy used by loop() — not volatile since only loop() reads it.
static PIC_to_Arduino_t pic;
static bool haveData = false;

static uint8_t  currentPage = 0;
static uint32_t lastPageSwitchMs = 0;
static uint32_t lastDrawMs = 0;
static uint32_t bootMs = 0;

// ---------------------------------------------------------------------------
// Receive ISR. Keep it minimal: copy bytes into a buffer, set a flag, leave.
// Validation and LCD work happen in loop().
// ---------------------------------------------------------------------------
void onI2CReceive(int n) {
  if (n != PACKET_SIZE) {
    // Drain the buffer so subsequent packets aren't misaligned.
    while (Wire.available()) Wire.read();
    errorCount++;
    return;
  }
  for (uint8_t i = 0; i < PACKET_SIZE; i++) {
    writeBuf[i] = Wire.read();
  }
  packetReady = true;
}

static uint8_t computeChecksum(const uint8_t *buf, uint8_t len) {
  uint8_t x = 0;
  for (uint8_t i = 0; i < len; i++) x ^= buf[i];
  return x;
}

// Cached last rendered text for each LCD row. writeLine() compares against
// these so unchanged rows skip the ~24 ms of I2C+LCD traffic per refresh.
static char prevLine[LCD_ROWS][LCD_COLS + 1];

// Pads to LCD_COLS with spaces and only writes if the row changed.
static void writeLine(uint8_t row, const char *s) {
  if (row >= LCD_ROWS) return;
  if (strcmp(s, prevLine[row]) == 0) return;
  lcd.setCursor(0, row);
  lcd.print(s);
  for (uint8_t i = strlen(s); i < LCD_COLS; i++) lcd.print(' ');
  strncpy(prevLine[row], s, LCD_COLS);
  prevLine[row][LCD_COLS] = '\0';
}

// Forces the next writeLine() for every row to actually push to the LCD.
// Call when leaving a page so the new page paints over whatever was there.
static void invalidateLineCache() {
  for (uint8_t r = 0; r < LCD_ROWS; r++) prevLine[r][0] = '\1';  // sentinel, can't match snprintf output
}

static void renderPage0_sequencer() {
  // Line 1: "P001 S03 120BPM " (pattern, step, tempo)
  char l1[LCD_COLS + 1];
  snprintf(l1, sizeof(l1), "P%03u S%02u %3uBPM",
           (unsigned)(pic.current_pattern + 1),
           (unsigned)(pic.current_step + 1),
           (unsigned)pic.tempo_bpm);
  writeLine(0, l1);

  // Line 2: "N060 V100 RAS   " (note, velocity, run/accent/slide flags)
  char l2[LCD_COLS + 1];
  char rFlag = (pic.sequencer_flags & SEQ_RUNNING) ? 'R' : '.';
  char aFlag = (pic.sequencer_flags & SEQ_ACCENT)  ? 'A' : '.';
  char sFlag = (pic.sequencer_flags & SEQ_SLIDE)   ? 'S' : '.';
  snprintf(l2, sizeof(l2), "N%03u V%03u %c%c%c",
           (unsigned)pic.note_value,
           (unsigned)pic.velocity,
           rFlag, aFlag, sFlag);
  writeLine(1, l2);
}

static void renderPage1_effects() {
  // Phase 3/4 will populate this. Until then, show the placeholder.
  writeLine(0, "FX: bypass");
  writeLine(1, "Delay -- BC --");
}

static void renderPage2_system() {
  uint32_t uptimeS = (millis() - bootMs) / 1000UL;
  uint32_t pkts;
  uint16_t errs;
  noInterrupts();
  pkts = packetCount;
  errs = errorCount;
  interrupts();

  char l1[LCD_COLS + 1];
  snprintf(l1, sizeof(l1), "Pkt %lu", (unsigned long)pkts);
  writeLine(0, l1);

  char l2[LCD_COLS + 1];
  snprintf(l2, sizeof(l2), "Err %u Up %lus", (unsigned)errs, (unsigned long)uptimeS);
  writeLine(1, l2);
}

static void renderCurrentPage() {
  switch (currentPage) {
    case 0: renderPage0_sequencer(); break;
    case 1: renderPage1_effects();   break;
    case 2: renderPage2_system();    break;
  }
}

void setup() {
  bootMs = millis();
  pinMode(STATUS_LED, OUTPUT);
  digitalWrite(STATUS_LED, LOW);

  Serial.begin(DEBUG_BAUD);
  // Don't block on Serial — Pro Micro can run headless when bench-bringup is done.

  Wire.begin(ARDUINO_I2C_ADDRESS);
  Wire.onReceive(onI2CReceive);

  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("ML-303 Ready"));
  lcd.setCursor(0, 1);
  lcd.print(F("Waiting for PIC"));

  Serial.println(F("Phase 1 firmware up."));
  Serial.print(F("  arduino addr: 0x")); Serial.println(ARDUINO_I2C_ADDRESS, HEX);
  Serial.print(F("  lcd addr:     0x")); Serial.println(LCD_I2C_ADDRESS, HEX);
  Serial.print(F("  packet size:  ")); Serial.println(PACKET_SIZE);
}

void loop() {
  // 1. Drain any pending packet from the ISR.
  if (packetReady) {
    uint8_t local[PACKET_SIZE];
    noInterrupts();
    for (uint8_t i = 0; i < PACKET_SIZE; i++) local[i] = writeBuf[i];
    packetReady = false;
    interrupts();

    uint8_t expected = computeChecksum(local, PACKET_SIZE - 1);
    if (expected != local[PACKET_SIZE - 1]) {
      errorCount++;
      Serial.println(F("checksum mismatch"));
    } else {
      memcpy(&pic, local, PACKET_SIZE);
      packetCount++;
      haveData = true;
      digitalWrite(STATUS_LED, !digitalRead(STATUS_LED));
    }
  }

  // 2. Rotate page every PAGE_ROTATE_MS.
  uint32_t now = millis();
  if (now - lastPageSwitchMs >= PAGE_ROTATE_MS) {
    lastPageSwitchMs = now;
    currentPage = (currentPage + 1) % 3;
    invalidateLineCache();   // Force redraw on page switch
    lastDrawMs = 0;
  }

  // 3. Redraw at most every MIN_DISPLAY_INTERVAL_MS.
  if (haveData && (now - lastDrawMs) >= MIN_DISPLAY_INTERVAL_MS) {
    renderCurrentPage();
    lastDrawMs = now;
  }
}
