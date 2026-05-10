/*
 * Shared protocol between PIC18LF452 (master) and Arduino Pro Micro (slave).
 *
 * IMPORTANT: the Arduino .ino keeps its own copy of this struct definition
 * for portability. If you change anything here, mirror it in
 * firmware/arduino/phase1_i2c_lcd/phase1_i2c_lcd.ino — the size assertion
 * in setup() will catch a divergence at boot.
 */

#ifndef ML303_DATA_H
#define ML303_DATA_H

#include <stdint.h>

/* I2C addresses (7-bit). */
#define ARDUINO_I2C_ADDRESS  0x43
#define ARDUINO_I2C_WRITE    (ARDUINO_I2C_ADDRESS << 1)        /* 0x86 */

/* Sequencer flag bits (sequencer_flags field). */
#define SEQ_RUNNING  0x01
#define SEQ_ACCENT   0x02
#define SEQ_SLIDE    0x04

/*
 * 9-byte packet. Packed because the PIC writes raw bytes onto the I2C bus
 * and the Arduino reinterprets them as a struct — natural alignment would
 * insert a pad before tempo_bpm and break the layout.
 */
typedef struct __attribute__((packed)) {
    uint8_t  current_step;      /* 0..15  */
    uint8_t  current_pattern;   /* 0..127 */
    uint16_t tempo_bpm;         /* 60..200, little-endian */
    uint8_t  button_state;
    uint8_t  sequencer_flags;   /* SEQ_RUNNING | SEQ_ACCENT | SEQ_SLIDE */
    uint8_t  note_value;        /* MIDI 24..96 */
    uint8_t  velocity;          /* 0..127 */
    uint8_t  checksum;          /* XOR of the 8 preceding bytes */
} PIC_to_Arduino_t;

#define ML303_PACKET_SIZE  9

/* Compute XOR checksum over the first (len) bytes of buf. */
static inline uint8_t ml303_checksum(const uint8_t *buf, uint8_t len) {
    uint8_t x = 0;
    for (uint8_t i = 0; i < len; i++) x ^= buf[i];
    return x;
}

#endif /* ML303_DATA_H */
