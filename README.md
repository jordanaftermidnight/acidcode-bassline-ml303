# acidcode-bassline-ml303

Hardware build, firmware, and integration work for the **ML-303** — Mathias Schaffrath's TB-303 clone (originally distributed via acidcode.de, now discontinued).

## What this repo covers

- **Frontpanel** (`frontpanel/`) — Panel design files, button matrix adapters, build instructions (V5/V6), DIYLC layouts, BOM tools. The original Conrad 3-pin tactile switches are discontinued; this directory contains the complete adapter solution for using standard 4-pin switches.
- **Firmware** (`firmware/`) — Arduino Pro Micro and PIC18LF452 code for adding an I2C LCD and Arduino-controlled effects chain to the ML-303.
- **Docs** (`docs/`) — Wiring diagrams, packet-protocol diagram, build guide, troubleshooting.

## Hardware

- ML-303 V5 mainboard (PIC18LF452 @ 10 MHz, firmware V7.02 from July 2008)
- Arduino Nano (ATmega328P, 5 V / 16 MHz)
- I2C LCD 16x2 (PCF8574 backpack, red backlight)
- LFO modulation sub-assembly on stripboard (Phase 3 — see [`docs/hardware/diagrams/lfo_mod_wiring.svg`](docs/hardware/diagrams/lfo_mod_wiring.svg))

## Enclosure constraints

The metal panel stays as stock as possible. **No new holes** will be drilled. The existing panel inventory on this 2018-revision panel:

**Audio I/O (front, except where noted)**
- **AUDIO IN** jack (rear) — external audio routed through the VCF + VCA (not a passive mix like a real TB-303); gain set by the internal "Adj. Input" trimmer; activates when WAVEFORM switch is in middle (EXT) position
- **LINE OUT** jack (front, top-right)
- **HEADPHONE** jack (front, top-right)

**Mod controls (front)**
- **AT-ONE** toggle (upper-left) with LED indicator above — panel label inherited from xpo's **AT-1 attenuator kit** (Acidcode sale listings reference it as "delivered separately, not installed"). The kit was not supplied with this unit and its schematic is undocumented. Repurposed for **Phase 3** as the LFO enable toggle: gates the Arduino-generated CV to the VCF cutoff modulation input. The LED indicator above the toggle is PWM-driven by the Arduino at the LFO rate (visible regardless of toggle position, so the rate is always observable). Panel sticker can be reprinted as `LFO` / `MOD` once verified.
- **DRIVE** pot (next to AT-ONE) — identified from the V6 PCB silkscreen "**HIGHP DISTORTION**" (xpo_construction.pdf p.14). Internal distortion stage with optional HIGHPASS toggle near VOLUME ("if switch is not used you must solder a bridge here").

Effects routing for added gear (Phase 3+) uses **LINE OUT → external box → AUDIO IN** as an effects loop, with WAVEFORM=EXT muting the internal VCO. No internal taps, no new holes.

## Phase plan

| Phase | Goal | Status |
|-------|------|--------|
| 1 | I2C bus PIC → Arduino → LCD; sequencer data on display | Firmware scaffolded; bench-test pending |
| 2 | Multi-page LCD with button-navigable UI (LFO rate/depth on FX page) | Pending |
| 3 | Arduino-generated LFO → VCF cutoff modulation via AT-ONE toggle | Firmware drafted; stripboard build pending |
| 4 | BD trigger I/O integration + remaining V6 mods | Pending |

## Phase 3 design

A triangle-wave LFO is generated on the Nano as PWM, smoothed by a small RC network on a stripboard, gated by the AT-ONE toggle, and injected into the ML-303's existing **V6 "VCF CUTOFF MODULATION INPUT"** pads. The LED above the AT-ONE toggle is driven separately by Arduino PWM and tracks the LFO waveform — so the rate is always visible regardless of whether the toggle has the CV routed to the filter.

See [`docs/hardware/diagrams/lfo_mod_wiring.svg`](docs/hardware/diagrams/lfo_mod_wiring.svg) for the full wiring (Arduino pins → stripboard → toggle → V6 pad → LED), the BOM, and behaviour notes.

Defaults in `firmware/arduino/phase1_i2c_lcd/pins.h`: rate 2.5 Hz, depth ~78 %, centre at mid-rail (~2.5 V after the RC filter). Phase 2's LCD UI will expose these for live tweaking.

### Deferred / dropped

- **JF-33 PT2399 analog delay** (deferred) — no space inside the enclosure for the PCB. Could only re-enter scope if it can be panel-mounted without new holes and its knobs are removed (control would come from the Arduino or external CV).
- **Great Destroyer bit crusher** (dropped) — the onboard DRIVE pot is the V6 "HIGHP DISTORTION" stage, which already provides analog distortion. An external bit crusher in a LINE OUT → AUDIO IN loop would be redundant.

## Phase 1 design

The PIC18LF452 acts as I²C master on a 100 kHz bus and pushes a **9-byte, XOR-checksummed sequencer packet** to the Arduino slave (address `0x43`) once per step. The Arduino drives a PCF8574-backed 16×2 LCD that lives on the same bus.

Two diagrams in [`docs/hardware/diagrams/`](docs/hardware/diagrams/) cover the moving parts:

- [`i2c_bus_topology.svg`](docs/hardware/diagrams/i2c_bus_topology.svg) — three-node bus with pin numbers, addresses, pull-up rules, timing notes
- [`packet_layout.svg`](docs/hardware/diagrams/packet_layout.svg) — 9 bytes byte-by-byte, the `seq_flags` bit map, and a worked checksum example

Firmware notes worth knowing before reading the code:

- The struct is defined in **two places** on purpose — `firmware/pic/ml303_data.h` (XC8) and `firmware/arduino/phase1_i2c_lcd/phase1_i2c_lcd.ino` (avr-gcc). A `static_assert(sizeof(...) == 9)` on the Arduino side catches drift at compile time.
- LCD writes are **dirty-tracked**: each row is only redrawn when its formatted text actually changed since the last frame. This keeps the shared I²C bus quiet while the sequencer holds steady on a step.
- The Arduino's `onI2CReceive` handler does the bare minimum (copy bytes, set flag). Checksum validation and LCD output run in `loop()`.

## Build flow (Phase 1)

```
1. firmware/arduino/tests/i2c_scanner.ino    → confirm LCD address (0x27 vs 0x3F)
2. firmware/arduino/tests/lcd_test.ino       → confirm LCD wiring
3. firmware/arduino/phase1_i2c_lcd/          → upload main firmware (LCD shows "Waiting for PIC")
4. firmware/pic/                             → integrate I2C master into PIC firmware
5. Connect PIC ↔ Arduino ↔ LCD on shared I2C bus
```

See [`docs/firmware/build-guide.md`](docs/firmware/build-guide.md) for the step-by-step, [`docs/hardware/wiring-diagram.md`](docs/hardware/wiring-diagram.md) for pin maps, [`docs/hardware/inter-board-cable-pinout.md`](docs/hardware/inter-board-cable-pinout.md) + [`docs/hardware/diagrams/inter_board_cable_pinout.svg`](docs/hardware/diagrams/inter_board_cable_pinout.svg) for the V5 analog↔digital cable pinout (10-pin DIGITAL_CON1 with PIC18LF452 mapping), and [`docs/hardware/troubleshooting.md`](docs/hardware/troubleshooting.md) when something goes wrong.

## Status

Buttons replaced (frontpanel work complete). Phase 1 firmware written but not yet flashed to hardware — the next concrete step is Stage 1 of the build guide (Arduino-only bringup, PIC disconnected).
