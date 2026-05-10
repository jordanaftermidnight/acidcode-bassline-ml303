# Phase 1 build guide

End-to-end procedure to get the LCD displaying real-time sequencer data from the PIC.

## Prerequisites

- ML-303 V5 with PIC18LF452, firmware V7.02 source available
- Arduino Pro Micro (5V/16MHz)
- I2C LCD 16x2 with PCF8574 backpack
- Arduino IDE 2.x or `arduino-cli`
- MPLAB X IDE 5.x+ with XC8 compiler 2.x
- Multimeter; logic analyzer optional but very useful

## Stage 1 — Arduino-side bringup (no PIC connected)

1. **Install the Arduino library** "LiquidCrystal I2C" by Frank de Brabander.
2. **Wire the LCD** to the Arduino: VCC→VCC, GND→GND, SDA→Pin 2, SCL→Pin 3.
3. **Upload `firmware/arduino/tests/i2c_scanner.ino`**. Open Serial Monitor at 115200. Confirm the LCD address (expect 0x27 or 0x3F). Write it down.
4. **Upload `firmware/arduino/tests/lcd_test.ino`**. The LCD should read `ML-303 LCD OK / Phase 1 ready` with backlight blinking once per second. If blank: contrast pot, then verify wiring. See `docs/hardware/troubleshooting.md`.
5. **If the LCD address is 0x3F**, edit `firmware/arduino/phase1_i2c_lcd/pins.h` and change `LCD_I2C_ADDRESS` to 0x3F (or pass `-DLCD_I2C_ADDRESS=0x3F` to `arduino-cli compile`).
6. **Upload `firmware/arduino/phase1_i2c_lcd/phase1_i2c_lcd.ino`**. The LCD should show `ML-303 Ready / Waiting for PIC`. Status LED off. Serial monitor prints the addresses and packet size on boot.

Stage 1 done when: LCD shows the boot banner and Serial reports the addresses.

## Stage 2 — PIC-side firmware additions

1. **Open the existing ML-303 PIC project** in MPLAB X.
2. **Add three files** from `firmware/pic/`:
   - `ml303_data.h` → Header Files
   - `i2c_master.h` → Header Files
   - `i2c_master.c` → Source Files
3. **In your hardware init** (the routine that sets up TRIS, oscillator, etc.), add:
   ```c
   #include "i2c_master.h"
   #include "ml303_data.h"
   ...
   I2C_Master_Init();
   ```
4. **In your step-advance routine** (called once per sequencer tick), add a call to a packet-builder function. The exact code depends on your existing globals — see `firmware/pic/README.md` for a reference implementation.
5. **Build.** Should compile clean with XC8. Warnings about implicit casts in `__attribute__((packed))` are harmless.
6. **Flash** the PIC (PICkit 3/4/5 or compatible programmer). Power-cycle.

Stage 2 done when: ML-303 still functions normally (audio works, sequencer runs). The Arduino isn't connected yet, so the PIC's I2C transmits will NACK silently — that's expected and doesn't break anything because `I2C_Master_SendPacket` returns the error code and the caller ignores it.

## Stage 3 — Connect the bus

With both devices powered down:

1. **Run SDA** from PIC pin 23 (RC4) to Arduino pin 2.
2. **Run SCL** from PIC pin 18 (RC3) to Arduino pin 3.
3. **Confirm shared ground** — the PIC's GND and the Arduino's GND must be the same net.
4. **Power up both.** The LCD should switch from `Waiting for PIC` to live sequencer data within one step.

Stage 3 done when: Status LED toggles per step, page 0 shows live `P### S## ###BPM`, and pages 1/2 cycle every 3 s.

## Acceptance test

Run for 5 minutes with the sequencer playing a pattern. Check:

- [ ] Status LED toggles consistently (no missed beats)
- [ ] Page 2 (system) shows error count = 0 or very close
- [ ] Audio output is unaffected (A/B with Arduino unpowered)
- [ ] LCD updates feel responsive (<100 ms latency from step change to display)

Pass = Phase 1 complete.

## What's next

- Phase 2 will replace the simple page rotation with button-controllable pages and richer rendering (step grid bargraph, pattern name, etc.).
- Phase 3 introduces JF-33 control via PWM pins 5/6/9 and inserts the delay between VCF and VCA.
