# Phase 1 wiring

Four wires — PIC, Arduino, and LCD share a single 100 kHz I2C bus.

## Bus topology

```
        +5V ────┬─────────┬─────────┬─────
                │         │         │
              [PIC]    [Arduino] [LCD]
                │         │         │
        SDA ────┼─────────┼─────────┼─────  Pin 2 on Arduino
        SCL ────┼─────────┼─────────┼─────  Pin 3 on Arduino
                │         │         │
        GND ────┴─────────┴─────────┴─────
```

## Pin map

| Net  | PIC18LF452       | Arduino Pro Micro | LCD backpack |
|------|------------------|-------------------|--------------|
| SDA  | Pin 23 (RC4)     | Pin 2 (SDA)       | SDA          |
| SCL  | Pin 18 (RC3)     | Pin 3 (SCL)       | SCL          |
| +5V  | Pin 11 (VDD)     | VCC               | VCC          |
| GND  | Pin 12, 31 (VSS) | GND               | GND          |

## Pull-ups

The PCF8574 LCD backpack ships with 4.7 kΩ pull-ups already installed on SDA and SCL. **Do not add more** — additional pull-ups in parallel will load the bus. If you see weak/garbled signals, _remove_ the LCD pull-ups and replace with a single pair of 2.2 kΩ resistors at the Arduino end.

## Wire length

Keep the total bus under 30 cm at 100 kHz. The Arduino mounts directly above the sequencer board on 10 mm standoffs, so the PIC↔Arduino run is ~5 cm. The LCD lives on the front panel — route its pair as twisted pair if it's longer than 15 cm.

## Power budget

| Device           | Current (mA) |
|------------------|--------------|
| Arduino Pro Micro | ~50 |
| PCF8574 LCD (backlight on) | ~30 |
| **Total added** | **~80** |

The ML-303 on-board +5V regulator (LM7805 in a TO-220 with heatsink) is rated for 1 A and currently draws well under that. 80 mA additional load is comfortable.

If the regulator runs hot after adding the Arduino + LCD: feed the Arduino's RAW pin (not VCC) from the unregulated +9V rail — Pro Micro's onboard regulator drops it to 5 V locally and offloads heat from the ML-303 regulator.

## Mounting

- Arduino on 10 mm M2.5 standoffs above the sequencer PCB. Position so the USB connector is reachable at the rear panel for re-flashing.
- LCD bolts to the front panel. Run the 4-wire harness to the Arduino as twisted pair for SDA/SCL, separate pair for power.
- Strain-relieve the LCD harness at both ends — front-panel removal will eventually tug it.

## Signal-integrity sanity checks (with a scope)

- SDA/SCL rise time should be under 1 µs (300 ns is typical with 4.7 kΩ pull-ups and ~30 pF bus capacitance).
- No undershoot below -0.3 V or overshoot above +5.5 V.
- Logic levels: VOL < 0.4 V, VOH > 4.0 V.
