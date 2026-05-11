# Phase 1 wiring

Four wires — PIC, Arduino, and LCD share a single 100 kHz I2C bus.

## Diagrams

Full SVG versions live in [`diagrams/`](diagrams/):

- [I²C bus topology](diagrams/i2c_bus_topology.svg) — pin-level node-and-net diagram with addresses, pull-up rules, and timing notes
- [Packet layout](diagrams/packet_layout.svg) — 9-byte struct with field offsets, flag-bit breakdown, and a worked checksum example

## Bus topology (ASCII)

```
        +5V ────┬─────────┬─────────┬─────
                │         │         │
              [PIC]    [Arduino] [LCD]
                │         │         │
        SDA ────┼─────────┼─────────┼─────  A4 on Arduino Nano
        SCL ────┼─────────┼─────────┼─────  A5 on Arduino Nano
                │         │         │
        GND ────┴─────────┴─────────┴─────
```

## Pin map

| Net  | PIC18LF452       | Arduino Nano | LCD backpack |
|------|------------------|--------------|--------------|
| SDA  | Pin 23 (RC4)     | A4           | SDA          |
| SCL  | Pin 18 (RC3)     | A5           | SCL          |
| +5V  | Pin 11 (VDD)     | 5V (or VIN)  | VCC          |
| GND  | Pin 12, 31 (VSS) | GND          | GND          |

## Pull-ups

The PCF8574 LCD backpack ships with 4.7 kΩ pull-ups already installed on SDA and SCL. **Do not add more** — additional pull-ups in parallel will load the bus. If you see weak/garbled signals, _remove_ the LCD pull-ups and replace with a single pair of 2.2 kΩ resistors at the Arduino end.

## Wire length

Keep the total bus under 30 cm at 100 kHz. The Arduino mounts directly above the sequencer board on 10 mm standoffs, so the PIC↔Arduino run is ~5 cm. The LCD lives on the front panel — route its pair as twisted pair if it's longer than 15 cm.

## Power budget

| Device           | Current (mA) |
|------------------|--------------|
| Arduino Nano (no USB) | ~30 |
| PCF8574 LCD (backlight on) | ~30 |
| **Total added** | **~60** |

The ML-303 on-board +5V regulator (LM7805 in a TO-220 with heatsink) is rated for 1 A and currently draws well under that. 60 mA additional load is comfortable.

If the regulator runs hot after adding the Arduino + LCD: feed the Arduino's **VIN** pin (not 5V) from the unregulated +9V rail — the Nano's onboard regulator drops it to 5 V locally and offloads heat from the ML-303 regulator.

## Mounting

- Arduino on 10 mm M2.5 standoffs above the sequencer PCB. Position so the USB connector is reachable at the rear panel for re-flashing.
- LCD bolts to the front panel. Run the 4-wire harness to the Arduino as twisted pair for SDA/SCL, separate pair for power.
- Strain-relieve the LCD harness at both ends — front-panel removal will eventually tug it.

## Signal-integrity sanity checks (with a scope)

- SDA/SCL rise time should be under 1 µs (300 ns is typical with 4.7 kΩ pull-ups and ~30 pF bus capacitance).
- No undershoot below -0.3 V or overshoot above +5.5 V.
- Logic levels: VOL < 0.4 V, VOH > 4.0 V.
