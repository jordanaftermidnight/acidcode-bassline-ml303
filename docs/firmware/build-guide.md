# Phase 1 build guide

End-to-end procedure to get the LCD displaying real-time sequencer data from the PIC.

For visual references while reading along:
- [`../hardware/diagrams/i2c_bus_topology.svg`](../hardware/diagrams/i2c_bus_topology.svg) — pin-level bus diagram
- [`../hardware/diagrams/packet_layout.svg`](../hardware/diagrams/packet_layout.svg) — 9-byte packet anatomy

## Prerequisites

- ML-303 V5 with PIC18LF452, firmware V7.02 source available
- Arduino Nano (ATmega328P, 5V/16MHz)
- I2C LCD 16x2 with PCF8574 backpack
- Arduino IDE 2.x or `arduino-cli`
- MPLAB X IDE 5.x+ with XC8 compiler 2.x
- Multimeter; logic analyzer optional but very useful

## Stage 1 — Arduino-side bringup (no PIC connected)

1. **Install the Arduino library** "LiquidCrystal I2C" by Frank de Brabander.
2. **Wire the LCD** to the Arduino: VCC→5V, GND→GND, SDA→A4, SCL→A5.
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

1. **Run SDA** from PIC pin 23 (RC4) to Arduino A4.
2. **Run SCL** from PIC pin 18 (RC3) to Arduino A5.
3. **Confirm shared ground** — the PIC's GND and the Arduino's GND must be the same net.
4. **Power up both.** The LCD should switch from `Waiting for PIC` to live sequencer data within one step.

Stage 3 done when: Status LED toggles per step, page 0 shows live `P### S## ###BPM`, and pages 1/2 cycle every 3 s.

> **Note on LCD behaviour during bench-test.** The Arduino dirty-tracks each LCD row — it only redraws a row when the formatted text changes. So if you pause the sequencer with `RUNNING` cleared, the screen will appear "frozen" on the last live frame. That's not a bug, that's the bus-quieting optimization at work. The status LED still toggles on every received packet, so use that to confirm the link is alive.

## Acceptance test

Run for 5 minutes with the sequencer playing a pattern. Check:

- [ ] Status LED toggles consistently (no missed beats)
- [ ] Page 2 (system) shows error count = 0 or very close
- [ ] Audio output is unaffected (A/B with Arduino unpowered)
- [ ] LCD updates feel responsive (<100 ms latency from step change to display)

Pass = Phase 1 complete.

## What's next

- Phase 2 will replace the simple page rotation with button-controllable pages and richer rendering (step grid bargraph, pattern name, LFO rate/depth controls on the FX page, etc.).
- Phase 3 wires the Arduino-generated LFO into the V6 "VCF CUTOFF MODULATION INPUT" pads via a small stripboard sub-assembly (RC smoothing filter + series resistor + LED current-limit) and the AT-ONE toggle as the gate. See `docs/hardware/diagrams/lfo_mod_wiring.svg` for the full diagram and BOM. The LFO firmware is already in `phase1_i2c_lcd.ino` (runs continuously on PWM pin D9; LED brightness tracks waveform on D10) — bench-tested once the stripboard is built.
- The Great Destroyer bit crusher is dropped (the onboard DRIVE pot = V6 HIGHP DISTORTION already provides analog distortion). JF-33 PT2399 delay stays deferred — see README for the conditions under which it could come back.
- The JF-33 PT2399 delay is deferred (won't fit inside the enclosure). See the README "Deferred" section for the conditions under which it could come back.
