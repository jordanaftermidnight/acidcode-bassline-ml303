// I2C bus scanner for ML-303 Phase 1 bringup.
//
// Prints every responding 7-bit address (1..127). Use this to confirm the
// PCF8574 LCD backpack address: most clones answer at 0x27, some at 0x3F.
// The Arduino itself will later answer at 0x43, but at this stage it is a
// master so its own address won't appear.
//
// Wiring: SDA=Pin 2, SCL=Pin 3 on Pro Micro. Pull-ups on the LCD backpack
// are usually sufficient; if no devices show up, check power and wiring
// before reaching for external pull-ups.

#include <Wire.h>

void setup() {
  Wire.begin();
  Serial.begin(115200);
  while (!Serial) { ; }   // Pro Micro: USB CDC needs time to enumerate
  Serial.println(F("I2C scanner — ML-303 Phase 1 bringup"));
}

void loop() {
  uint8_t found = 0;
  Serial.println(F("Scanning..."));

  for (uint8_t addr = 1; addr < 127; addr++) {
    Wire.beginTransmission(addr);
    uint8_t err = Wire.endTransmission();

    if (err == 0) {
      Serial.print(F("  device at 0x"));
      if (addr < 16) Serial.print('0');
      Serial.println(addr, HEX);
      found++;
    } else if (err == 4) {
      Serial.print(F("  unknown error at 0x"));
      if (addr < 16) Serial.print('0');
      Serial.println(addr, HEX);
    }
  }

  if (found == 0) {
    Serial.println(F("No devices. Check wiring, power, and pull-ups."));
  } else {
    Serial.print(F("Total: "));
    Serial.println(found);
  }

  delay(5000);
}
