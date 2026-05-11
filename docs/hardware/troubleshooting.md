# Troubleshooting

See [`diagrams/i2c_bus_topology.svg`](diagrams/i2c_bus_topology.svg) for the bus reference and [`diagrams/packet_layout.svg`](diagrams/packet_layout.svg) for the protocol. For the original V5 analog↔digital inter-board cabling (10-pin `DIGITAL_CON1` and the 2-pin power harness), see [`inter-board-cable-pinout.md`](inter-board-cable-pinout.md) — the V5 board has no reverse-polarity protection so verify continuity before powering up if the cables have been reworked.

## LCD appears frozen on stable values

**Not a bug.** The Arduino dirty-tracks LCD rows — each row is only redrawn when its formatted text changes since the last render. Pause the sequencer (clear `SEQ_RUNNING`) or hold on the same step and the display will look static. To confirm the link is still alive without changing what's shown: watch the status LED (toggles per packet) or open Serial Monitor at 115200 (no `checksum mismatch` errors = packets flowing).

If you genuinely need a forced refresh for debugging, set `MIN_DISPLAY_INTERVAL_MS = 0` and add `invalidateLineCache()` at the top of `loop()`.

## LCD shows nothing

1. **Contrast pot.** PCF8574 backpacks ship with the contrast pot fully turned down. Adjust it (small blue pot) until block characters appear, then drop in real text.
2. **Wrong address.** Run `firmware/arduino/tests/i2c_scanner.ino` standalone. PCF8574 = 0x27, PCF8574A = 0x3F. Recompile the main sketch with `-DLCD_I2C_ADDRESS=0x3F` if needed.
3. **No power.** Probe VCC (should be +4.8 to +5.1 V) and confirm the backlight LED is lit.

## LCD reads "Waiting for PIC" forever

Means the Arduino booted fine but no valid packets are arriving.

1. **PIC firmware not updated.** Confirm `I2C_Master_Init()` is called and `send_step_to_arduino()` runs each step.
2. **SDA/SCL swapped.** Easy mistake — they're adjacent on both chips. Probe with a multimeter in continuity mode.
3. **PIC crashed.** Other ML-303 functions still work? If the audio engine is dead too, the PIC isn't running.
4. **Address mismatch.** PIC sending to 0x43 but Arduino listening on something else. Check both.
5. **Checksum mismatch.** Open Serial Monitor at 115200 — every bad packet logs `checksum mismatch`. If you see those, the bytes arrive but the XOR doesn't validate. Most often: the PIC code computes XOR over the wrong range. Should be the first 8 bytes, write the result into byte 9.

## Garbled or flickering display

1. **Bus speed too high for the wiring.** Drop to 50 kHz: change `SSPADD = 24` to `SSPADD = 49` in `i2c_master.c`. Also halve the Arduino-side rate (Wire library auto-follows the master, so usually no change needed).
2. **Multi-master contention.** The Arduino writes to the LCD as master while the PIC drives the bus. Wire's master ops yield, but heavy contention can cause gaps. Increase `MIN_DISPLAY_INTERVAL_MS` in `phase1_i2c_lcd.ino` from 50 to 100+.
3. **Cable too long or untwisted.** Keep total bus under 30 cm. Twist SDA with SCL.
4. **Insufficient bypass.** Add 100 nF ceramic from VCC to GND directly at the Arduino's VCC pin and at the LCD backpack.

## Communication works, then stops after a while

1. **Bus lockup.** A slave that holds SDA low without releasing it can wedge the bus. Power-cycle as a quick test. If it recurs, add a watchdog timeout in the PIC `I2C_Master_Wait()` and a recovery routine that toggles SCL nine times manually to clear a stuck slave.
2. **Power supply ripple.** Probe +5V with a scope at the regulator output under load. >100 mV ripple causes intermittent I2C errors. Add 470 µF at the Arduino's VCC pin.
3. **Intermittent connection.** Resolder the harness at both ends.

## Arduino doesn't enumerate over USB after upload

This is a Pro Micro thing, not an ML-303 thing.

- Reset twice quickly to enter bootloader.
- If still no luck: short RST to GND while plugged in, release after 0.5 s.
- Worst case, use the "burn bootloader" recovery procedure with another Arduino as ISP.

## ML-303 audio glitches when Arduino is connected

Almost always a ground loop or shared-power noise issue.

1. **Single ground point.** All three devices (PIC, Arduino, LCD) must share one ground reference. Don't take ground from two different points on the ML-303 board.
2. **USB ground noise.** When the Arduino is plugged into a computer for serial debug, the laptop ground can inject noise. Confirm by running on battery power or unplugging USB and check whether glitches stop.
3. **Switching regulator on Pro Micro clones.** Some clones use a switching regulator instead of LDO — emits noise at 1-2 MHz which can couple into the analog rails. Easiest fix: feed Pro Micro from the existing +5V (bypass its regulator).
