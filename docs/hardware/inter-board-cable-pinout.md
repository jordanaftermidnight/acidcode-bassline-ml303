# ML-303 V5 inter-board cable pinout

The original V5 design routes signals between the **analog board** (audio path, VCF, VCA, VCO, 6-bit pitch DAC) and the **digital board** (PIC18LF452 sequencer, button matrix, LEDs, MIDI) through four separate ribbon-style cables. Per `frontpanel/build_instructions_v5/303xmas.pdf` and the parts list on page 62:

| Cable | Width | xpo name | Carries |
|-------|-------|----------|---------|
| 1 | **10-pin** | `DIGITAL_CON1` | Sequencer control bus (this doc) |
| 2 | 5-pin | "Midi-Daten" | MIDI in/out signals |
| 3 | 3-pin | (not detailed here) | Auxiliary |
| 4 | 2-pin × 4 | "Spannungsversorgung Digital" + others | **Power** (+VDC, GND) and other 2-wire links |

The 10-pin cable is the one most likely to be reworked when these boards are passed between owners, so it's the one this doc focuses on. The 2-pin power cable is the one to be **most paranoid about** — see "Risk notes" at the bottom.

## DIGITAL_CON1 (10-pin VCO/sequencer bus)

Signal direction is **digital → analog** for every line on this cable.

| CON1 pin | PIC18LF452 pin | PIC port name | Analog-board endpoint | Function |
|---------:|---------------:|---------------|------------------------|----------|
| **1**    | 40             | RB7           | D101 (1N4148) → R182 (1 kΩ) → drum-trigger output | **DRUM_TRIG** pulse |
| **2**    | 39             | RB6           | IC9 (74174) D-input | Pitch DAC data bit |
| **3**    | 38             | RB5           | IC9 D-input | Pitch DAC data bit |
| **4**    | 37             | RB4           | IC9 D-input | Pitch DAC data bit |
| **5**    | 36             | RB3           | IC9 D-input | Pitch DAC data bit |
| **6**    | 35             | RB2           | IC9 D-input | Pitch DAC data bit |
| **7**    | 34             | RB1           | IC9 D-input | Pitch DAC data bit |
| **8**    | 33             | RB0           | IC9 pin 9 (CLK) | Latch clock — rising edge captures D1–D6 into the 74174 |
| **9**    | 7              | RA5           | IC9 pin 1 (/MR) | Master reset — active low, clears Q1–Q6 to 0 |
| **10**   | 5              | RA3           | Extra control signal (lands outside the 74174 latch — likely SLIDE / ACCENT / GATE into IC13a or similar) | Aux control |

**Pitch DAC chain:** PIC writes a 6-bit value onto pins 2–7 of CON1 (in whatever bit order the firmware uses), pulses pin 8 (CLK), and IC9 latches it. The 74174's Q1–Q6 outputs drive an R-2R-style precision divider (MPR 200 kΩ network) to produce the 6-bit / 64-note pitch CV called out in the V5 spec sheet (`303xmas.pdf` p.56).

**No power, no ground on this cable.** Power and ground travel via the separate 2-pin cable. The PIC18LF452 VDD pins are 11 and 32; VSS pins are 12 and 31. These are reached only via the 2-pin power harness, not via DIGITAL_CON1.

## V5 cable orientation note

From `frontpanel/build_instructions_v5/readme.txt`:

> Wie Ihr seht wird immer der linke PIN vom Analog-Board mit dem rechten PIN vom Sequenzer-Board verbunden.
> ("As you can see, the LEFT pin from the Analog-Board is always connected to the RIGHT pin from the Sequencer-Board.")

This just means the two connectors physically face each other with mirrored orderings — pin 1 is on the left of one connector and on the right of the other. **The electrical mapping is still 1↔1 by pin number end-to-end.** Cables wired by physical position (rather than pin number) end up reversed.

## Verifying a reworked cable

When the cable has been cut and re-spliced (visible heat-shrink mid-run, wire colours that don't match between the two ends), colour is no longer trustworthy. Verify by continuity only.

1. **Power off both boards. Cable disconnected at both ends.**
2. **Identify pin 1** on each connector:
   - silkscreen "1" on the top side of the PCB near the header, OR
   - **square** pad (vs round for the others) on the solder side, OR
   - arrow/triangle moulded into the plastic shroud at one end of the connector.
   - If none of those: identify pin 1 functionally — it's the one tied to the 1N4148 diode + 1 kΩ resistor on the analog side.
3. **DMM in continuity mode.** Probe pin N on connector A, confirm pin N (same number) on connector B beeps. Repeat for N = 1 through 10.
4. **Reverse check:** also probe each pin against pin 10 and against any obvious chassis ground point — should *not* beep, since DIGITAL_CON1 carries no GND. Any beep here means a signal has been shorted to ground somewhere along the splice path; stop and re-trace.

## Risk notes

The 10-pin cable's mismatch consequences are mostly benign because **every wire is a TTL signal between two CMOS GPIOs**:

| Mismap | Consequence |
|--------|-------------|
| Two signal pins swapped among themselves | Scrambled scale, wrong notes, drum trigger on the wrong bit, latch stuck in reset, etc. **No hardware damage.** Matches the V5 troubleshooting symptom "Sprünge in der Tonleiter". |
| Two outputs simultaneously driving each other (one high, one low) | ~10 mA short-circuit current through both GPIO drivers. CMOS outputs tolerate this briefly; long exposure can degrade but rarely instantly damages. |
| Any pin shorted to GND (via a splice fault) | The PIC GPIO sinking 5 V through its internal pull-up sees ~5 mA — within spec. Output trying to drive high while shorted to GND sees full short current — same as the case above. |
| The cable plugged in reversed end-to-end | Drum trigger lands on a data line; reset lands on the drum trigger; etc. Scrambled but **non-destructive**. |

**The 2-pin power cable is the one the V5 readme warns about**, not this 10-pin signal cable. That cable carries ~6 V from the analog board's 7806 regulator to the digital board's VDD rail (PIC pins 11 and 32). Reversing it would put −6 V on VDD → instant PIC failure. The V5 readme:

> DAS NEUE SEQUENZER-BOARD IST NICHT VERPOLUNGSSICHER!
> ("The new sequencer board has no reverse-polarity protection.")

Continuity-check the 2-pin power cable with the same care as the 10-pin, and confirm which lug is +V at both ends before plugging in.

## References

- Analog-board schematic: `frontpanel/build_instructions_v5/a.gif` — connector labelled `DIGITAL_CON1` at the top-left; IC9 is the 74174 hex flip-flop.
- Digital-board schematic: `frontpanel/build_instructions_v5/d.gif` — matching 10-pin header at the bottom of the layout, fans out to PORTB and PORTA pins on the PIC18LF452.
- V5 manual: `frontpanel/build_instructions_v5/303xmas.pdf` — cable specs on p.26, troubleshooting on p.54, technical data on p.56, parts list on p.62.
- V5 readme: `frontpanel/build_instructions_v5/readme.txt` — orientation note + the all-caps reverse-polarity warning.
