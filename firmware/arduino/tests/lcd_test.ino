// Standalone LCD test — confirms the I2C LCD backpack works before
// introducing the PIC into the bus topology.
//
// If the screen stays blank: the contrast pot on the PCF8574 backpack is
// often shipped fully turned down. Adjust it (small blue pot) until block
// characters appear, then drop in the actual text.
//
// Library: "LiquidCrystal I2C" by Frank de Brabander.

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#ifndef LCD_ADDR
#define LCD_ADDR 0x27   // Override at compile time if scanner reports 0x3F
#endif

LiquidCrystal_I2C lcd(LCD_ADDR, 16, 2);

void setup() {
  Wire.begin();
  Serial.begin(115200);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(F("ML-303 LCD OK"));
  lcd.setCursor(0, 1);
  lcd.print(F("Phase 1 ready"));

  Serial.print(F("LCD initialized at 0x"));
  Serial.println(LCD_ADDR, HEX);
}

void loop() {
  // Heartbeat: toggle backlight every second so a frozen LCD is obvious.
  static bool on = true;
  on = !on;
  if (on) lcd.backlight(); else lcd.noBacklight();
  delay(1000);
}
