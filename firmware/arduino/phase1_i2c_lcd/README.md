# Arduino Phase 1 firmware

I2C slave on the ML-303 bus. Receives a 9-byte sequencer packet from the
PIC every step, validates the XOR checksum, and renders the state across
three auto-rotating LCD pages.

## Build

- **IDE:** Arduino IDE 2.x or `arduino-cli`
- **Board:** Arduino Nano (ATmega328P, 5V/16MHz). "Old Bootloader" variant for many clones.
- **Library:** `LiquidCrystal I2C` by Frank de Brabander (install via Library Manager)

```bash
arduino-cli compile --fqbn arduino:avr:nano:cpu=atmega328 phase1_i2c_lcd
arduino-cli upload  --fqbn arduino:avr:nano:cpu=atmega328 --port /dev/cu.usbserial-* phase1_i2c_lcd
# For clones with the older bootloader, use cpu=atmega328old instead.
```

## Bringup order

1. **Run `tests/i2c_scanner.ino`** standalone (no PIC connected). Confirm the LCD address — most clones are 0x27, some are 0x3F. If it's 0x3F, recompile this sketch with `-DLCD_I2C_ADDRESS=0x3F`.
2. **Run `tests/lcd_test.ino`** — confirms the LCD wiring and contrast.
3. **Flash this sketch.** With no PIC connected, the LCD should show `ML-303 Ready / Waiting for PIC`. The on-board LED stays off.
4. **Connect PIC.** Once the modified PIC firmware sends packets, the LED toggles per packet, the sequencer page populates, and pages auto-rotate every 3 s.

## Pages

- **Page 0 — sequencer**: pattern, step, tempo / note, velocity, R-A-S flags
- **Page 1 — effects**: placeholder until Phase 3 (Great Destroyer routing)
- **Page 2 — system**: packet count, error count, uptime

## Debug

Open the Arduino Serial Monitor at 115200. The firmware prints addresses on boot and logs every checksum mismatch. The Nano uses a CH340/FT232 USB-serial bridge — enumeration is immediate; if you don't see boot output, check that the right `/dev/cu.usbserial-*` port is selected and that no other monitor (e.g. screen, minicom) is holding it.

## Tunables (in `pins.h`)

- `PAGE_ROTATE_MS` — page auto-rotate interval
- `LCD_I2C_ADDRESS` — LCD backpack address
- `ARDUINO_I2C_ADDRESS` — change only if 0x43 collides with another future device
