/*
 * ML-303 Arduino Hardware Test Sketch
 * 
 * This sketch tests all hardware components before full integration.
 * Run this first to verify your hardware is working correctly.
 * 
 * HARDWARE REQUIRED:
 * - Arduino Uno/Nano
 * - 16x2 LCD with contrast pot
 * - MCP4921 DAC
 * - 4 potentiometers (10k linear)
 * - 2 momentary switches
 * - MIDI interface circuit
 * 
 * SERIAL OUTPUT: 115200 baud
 */

#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <SPI.h>

// Pin assignments (same as main code)
const int LCD_RS = 12, LCD_E = 11, LCD_D4 = 10, LCD_D5 = 9, LCD_D6 = 8, LCD_D7 = 7;
const int BTN_RUN_STOP = 2, BTN_PATTERN = 3;
const int CLOCK_IN = 4, GATE_IN = 5, GATE_OUT = 6;
const int POT_CUTOFF = A0, POT_RESONANCE = A1, POT_ENVMOD = A2, POT_DECAY = A3;
const int MIDI_RX = A4, MIDI_TX = A5;
const int DAC_CS = 13;

LiquidCrystal lcd(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
SoftwareSerial midiSerial(MIDI_RX, MIDI_TX);

void setup() {
  Serial.begin(115200);
  Serial.println(F("ML-303 Hardware Test v1.0"));
  Serial.println(F("============================="));
  
  // Configure pins
  pinMode(BTN_RUN_STOP, INPUT_PULLUP);
  pinMode(BTN_PATTERN, INPUT_PULLUP);
  pinMode(CLOCK_IN, INPUT);
  pinMode(GATE_IN, INPUT);
  pinMode(GATE_OUT, OUTPUT);
  pinMode(DAC_CS, OUTPUT);
  
  digitalWrite(GATE_OUT, LOW);
  digitalWrite(DAC_CS, HIGH);
  
  // Initialize interfaces
  lcd.begin(16, 2);
  midiSerial.begin(31250);
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
  SPI.setClockDivider(SPI_CLOCK_DIV8);
  
  Serial.println(F("Starting hardware tests..."));
  delay(1000);
}

void loop() {
  Serial.println(F("\n=== HARDWARE TEST CYCLE ==="));
  
  testLCD();
  delay(1000);
  
  testPotentiometers();
  delay(1000);
  
  testButtons();
  delay(1000);
  
  testDAC();
  delay(1000);
  
  testMIDI();
  delay(1000);
  
  testDigitalInputs();
  delay(1000);
  
  testMemory();
  delay(3000);  // Pause between test cycles
}

void testLCD() {
  Serial.println(F("Testing LCD..."));
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("LCD TEST");
  lcd.setCursor(0, 1);
  lcd.print("Line 2 OK");
  
  Serial.println(F("  LCD: Check display shows 'LCD TEST' and 'Line 2 OK'"));
  Serial.println(F("  If blank, adjust contrast pot"));
  
  delay(2000);
  
  // Test all character positions
  lcd.clear();
  for (int i = 0; i < 16; i++) {
    lcd.setCursor(i, 0);
    lcd.print(i % 10);
    lcd.setCursor(i, 1);
    lcd.print((i + 5) % 10);
  }
  
  Serial.println(F("  LCD: Character position test complete"));
  delay(2000);
}

void testPotentiometers() {
  Serial.println(F("Testing potentiometers..."));
  
  for (int cycle = 0; cycle < 5; cycle++) {
    int cutoff = analogRead(POT_CUTOFF);
    int resonance = analogRead(POT_RESONANCE);
    int envmod = analogRead(POT_ENVMOD);
    int decay = analogRead(POT_DECAY);
    
    Serial.print(F("  Pots: "));
    Serial.print(cutoff); Serial.print(F(" "));
    Serial.print(resonance); Serial.print(F(" "));
    Serial.print(envmod); Serial.print(F(" "));
    Serial.println(decay);
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("POT TEST");
    lcd.setCursor(0, 1);
    lcd.print(cutoff); lcd.print(" ");
    lcd.print(resonance); lcd.print(" ");
    lcd.print(envmod); lcd.print(" ");
    lcd.print(decay);
    
    delay(500);
  }
  
  Serial.println(F("  Turn pots - values should change 0-1023"));
}

void testButtons() {
  Serial.println(F("Testing buttons..."));
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("BUTTON TEST");
  lcd.setCursor(0, 1);
  lcd.print("Press buttons");
  
  Serial.println(F("  Press RUN/STOP and PATTERN buttons"));
  
  unsigned long startTime = millis();
  bool runPressed = false, patternPressed = false;
  
  while (millis() - startTime < 5000) {  // 5 second test
    if (digitalRead(BTN_RUN_STOP) == LOW && !runPressed) {
      Serial.println(F("  RUN/STOP button: OK"));
      runPressed = true;
    }
    
    if (digitalRead(BTN_PATTERN) == LOW && !patternPressed) {
      Serial.println(F("  PATTERN button: OK"));
      patternPressed = true;
    }
    
    if (runPressed && patternPressed) break;
    delay(50);
  }
  
  if (!runPressed) Serial.println(F("  RUN/STOP button: NOT PRESSED"));
  if (!patternPressed) Serial.println(F("  PATTERN button: NOT PRESSED"));
}

void testDAC() {
  Serial.println(F("Testing DAC (MCP4921)..."));
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("DAC TEST");
  
  // Test DAC output sweep
  for (int value = 0; value <= 4095; value += 512) {
    writeDAC(value);
    
    Serial.print(F("  DAC output: "));
    Serial.print(value);
    Serial.print(F(" ("));
    Serial.print((value * 5.0) / 4095.0, 2);
    Serial.println(F("V)"));
    
    lcd.setCursor(0, 1);
    lcd.print("Out: ");
    lcd.print((value * 5.0) / 4095.0, 1);
    lcd.print("V     ");
    
    delay(500);
  }
  
  writeDAC(0);  // Reset to 0V
  Serial.println(F("  DAC: Sweep complete, check CV output with voltmeter"));
}

void testMIDI() {
  Serial.println(F("Testing MIDI..."));
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("MIDI TEST");
  lcd.setCursor(0, 1);
  lcd.print("Sending notes");
  
  // Send test MIDI notes
  for (int note = 60; note <= 72; note += 2) {
    Serial.print(F("  MIDI Note: "));
    Serial.println(note);
    
    midiSerial.write(0x90);  // Note on
    midiSerial.write(note);
    midiSerial.write(100);   // Velocity
    
    delay(200);
    
    midiSerial.write(0x80);  // Note off
    midiSerial.write(note);
    midiSerial.write(0);
    
    delay(200);
  }
  
  Serial.println(F("  MIDI: Test sequence sent"));
  
  // Check for MIDI input
  Serial.println(F("  Send MIDI to input for 3 seconds..."));
  unsigned long startTime = millis();
  int midiReceived = 0;
  
  while (millis() - startTime < 3000) {
    if (midiSerial.available()) {
      byte data = midiSerial.read();
      Serial.print(F("  MIDI RX: 0x"));
      Serial.println(data, HEX);
      midiReceived++;
    }
  }
  
  Serial.print(F("  MIDI input bytes received: "));
  Serial.println(midiReceived);
}

void testDigitalInputs() {
  Serial.println(F("Testing digital inputs..."));
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("DIGITAL TEST");
  
  // Test gate output
  Serial.println(F("  Testing gate output..."));
  for (int i = 0; i < 5; i++) {
    digitalWrite(GATE_OUT, HIGH);
    Serial.println(F("  Gate: HIGH"));
    delay(200);
    
    digitalWrite(GATE_OUT, LOW);
    Serial.println(F("  Gate: LOW"));
    delay(200);
  }
  
  // Monitor inputs
  Serial.println(F("  Monitoring inputs for 3 seconds..."));
  unsigned long startTime = millis();
  
  while (millis() - startTime < 3000) {
    bool clock = digitalRead(CLOCK_IN);
    bool gate = digitalRead(GATE_IN);
    
    lcd.setCursor(0, 1);
    lcd.print("CLK:");
    lcd.print(clock ? "1" : "0");
    lcd.print(" GATE:");
    lcd.print(gate ? "1" : "0");
    lcd.print("   ");
    
    delay(100);
  }
  
  Serial.println(F("  Digital input test complete"));
}

void testMemory() {
  Serial.println(F("Testing memory..."));
  
  extern int __heap_start, *__brkval;
  int v;
  int free_memory = (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
  
  Serial.print(F("  Free SRAM: "));
  Serial.print(free_memory);
  Serial.println(F(" bytes"));
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("MEMORY TEST");
  lcd.setCursor(0, 1);
  lcd.print("Free: ");
  lcd.print(free_memory);
  lcd.print("B");
  
  if (free_memory < 500) {
    Serial.println(F("  WARNING: Low memory!"));
    lcd.setCursor(0, 1);
    lcd.print("LOW MEMORY!");
  } else {
    Serial.println(F("  Memory: OK"));
  }
}

void writeDAC(int value) {
  value = constrain(value, 0, 4095);
  
  byte highByte = 0x30 | ((value >> 8) & 0x0F);
  byte lowByte = value & 0xFF;
  
  SPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE0));
  digitalWrite(DAC_CS, LOW);
  SPI.transfer(highByte);
  SPI.transfer(lowByte);
  digitalWrite(DAC_CS, HIGH);
  SPI.endTransaction();
}

/*
 * EXPECTED TEST RESULTS:
 * 
 * LCD Test: Should display text clearly (adjust contrast if needed)
 * Potentiometer Test: Values should change 0-1023 when turned
 * Button Test: Should detect button presses
 * DAC Test: CV output should sweep 0-5V (measure with voltmeter)
 * MIDI Test: Should send notes, receive input if connected
 * Digital Test: Gate output should toggle, inputs monitored
 * Memory Test: Should show >1500 bytes free for main code
 * 
 * If any test fails, check wiring and connections.
 * All tests should pass before loading main ML-303 code.
 */