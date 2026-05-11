# PIC18LF452 I2C master integration

These three files add I2C-master capability to the existing ML-303 firmware (V7.02). The PIC pushes a sequencer-state packet to the Arduino at address `0x43` once per step.

See [`../../docs/hardware/diagrams/packet_layout.svg`](../../docs/hardware/diagrams/packet_layout.svg) for the byte-by-byte protocol view (field offsets, `seq_flags` bit map, worked checksum example).

## Files

- `ml303_data.h` — protocol contract (struct layout + flag bits + checksum). Defines `ARDUINO_I2C_ADDRESS`, `ML303_PACKET_SIZE = 9`, the `PIC_to_Arduino_t` struct, and `ml303_checksum()`. The same struct is mirrored in the Arduino `.ino` because XC8 and avr-gcc can't share a header; a `static_assert` on the Arduino side catches any drift at compile time.
- `i2c_master.h` / `i2c_master.c` — MSSP-based I2C master driver. 100 kHz at 10 MHz Fosc (`SSPADD = 24`).

## Integrating into the existing firmware

1. **Add the files** to the MPLAB X project (`File > Add Existing Item...`). Drop `i2c_master.c` into Source Files and the headers into Header Files.

2. **Initialize once at boot.** In your existing `main()` or hardware-init routine, after the oscillator and other peripherals are stable:
   ```c
   #include "i2c_master.h"
   #include "ml303_data.h"

   I2C_Master_Init();
   ```

3. **Send a packet per step.** Wherever the sequencer advances the step (the routine that updates the gate output / DAC), build and emit a packet:
   ```c
   void send_step_to_arduino(void) {
       PIC_to_Arduino_t pkt;
       pkt.current_step    = g_step;          // your existing globals
       pkt.current_pattern = g_pattern;
       pkt.tempo_bpm       = g_tempo;
       pkt.button_state    = g_button_state;
       pkt.sequencer_flags = (g_running ? SEQ_RUNNING : 0)
                           | (g_accent  ? SEQ_ACCENT  : 0)
                           | (g_slide   ? SEQ_SLIDE   : 0);
       pkt.note_value      = g_note;
       pkt.velocity        = g_velocity;
       pkt.checksum        = ml303_checksum((const uint8_t*)&pkt, ML303_PACKET_SIZE - 1);

       (void)I2C_Master_SendPacket(ARDUINO_I2C_ADDRESS, &pkt, ML303_PACKET_SIZE);
   }
   ```

   Worst-case transmit time at 100 kHz: ~1 ms (9 bytes × 9 bits / 100 kHz + framing). Safe to call from the step-tick path without disrupting timing-critical code, but **don't call it from an ISR** — `I2C_Master_Wait()` busy-loops.

4. **Compile flags.** No special flags needed. XC8 v2.x with C99 is fine. The `__attribute__((packed))` in `ml303_data.h` is honored by XC8.

## Verifying

- Before changing real firmware, build a minimal test main that calls `I2C_Master_Init()` then sends a hardcoded packet in a loop. The Arduino's status LED should toggle and the LCD should show the test values.
- A logic analyzer on RC3/RC4 is the fastest way to debug — look for the `0x86` address byte (0x43 << 1) followed by 9 data bytes and an ACK on each.

## Pin reference

| Signal | PIC pin | Arduino Nano pin |
|--------|---------|------------------|
| SCL    | 18 (RC3) | A5 |
| SDA    | 23 (RC4) | A4 |
| GND    | 12 / 31  | GND |
| VCC    | 11 (+5V) | 5V |
