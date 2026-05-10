# acidcode-bassline-ml303

Hardware build, firmware, and integration work for the **ML-303** — Mathias Schaffrath's TB-303 clone (originally distributed via acidcode.de, now discontinued).

## What this repo covers

- **Frontpanel** (`frontpanel/`) — Panel design files, button matrix adapters, build instructions (V5/V6), DIYLC layouts, BOM tools. The original Conrad 3-pin tactile switches are discontinued; this directory contains the complete adapter solution for using standard 4-pin switches.
- **Firmware** (`firmware/`) — Arduino Pro Micro and PIC18LF452 code for adding an I2C LCD and Arduino-controlled effects chain to the ML-303.
- **Docs** (`docs/`) — Wiring diagrams, build guide, troubleshooting.

## Hardware

- ML-303 V5 mainboard (PIC18LF452, firmware V7.02)
- Arduino Pro Micro (5V/16MHz)
- I2C LCD 16x2 (PCF8574 backpack, red backlight)
- JF-33 PT2399 analog delay (Phase 3)
- Great Destroyer bit crusher (Phase 4)

## Phase plan

| Phase | Goal | Status |
|-------|------|--------|
| 1 | I2C bus PIC → Arduino → LCD; sequencer data on display | In progress |
| 2 | Multi-page LCD (sequencer / effects / system) | Pending |
| 3 | JF-33 delay PWM control, tempo sync, audio path insertion | Pending |
| 4 | Great Destroyer + BD trigger I/O + V6 features | Pending |

## Build flow (Phase 1)

```
1. firmware/arduino/tests/i2c_scanner.ino    → confirm LCD address (0x27 vs 0x3F)
2. firmware/arduino/tests/lcd_test.ino       → confirm LCD wiring
3. firmware/arduino/phase1_i2c_lcd/          → upload main firmware
4. firmware/pic/                             → integrate I2C master into PIC firmware
5. Connect PIC ↔ Arduino ↔ LCD on shared I2C bus
```

See `docs/firmware/build-guide.md` for step-by-step.

## Status

Buttons replaced (frontpanel work complete). Phase 1 firmware ready to flash and bench-test.
