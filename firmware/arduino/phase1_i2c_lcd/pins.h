// Phase 1 pin and constant definitions.
// Centralized so changing a pin doesn't require chasing through .ino files.

#pragma once

#include <stdint.h>

// ---- I2C addresses ----
// Arduino slave address chosen to avoid the LCD backpack range (0x20-0x27,
// 0x38-0x3F) and common sensor ranges. 0x43 is unused on this bus.
static const uint8_t ARDUINO_I2C_ADDRESS = 0x43;

// PCF8574 LCD backpacks ship as either 0x27 or 0x3F depending on the chip
// variant (PCF8574 vs PCF8574A). Run i2c_scanner.ino to confirm.
#ifndef LCD_I2C_ADDRESS
#define LCD_I2C_ADDRESS 0x27
#endif

// ---- Display timing ----
static const uint16_t PAGE_ROTATE_MS = 3000;   // Auto-rotate page every 3s
static const uint8_t  LCD_COLS = 16;
static const uint8_t  LCD_ROWS = 2;

// ---- Status LED ----
// Nano on-board LED (D13). Toggles on every successful packet receive so a
// stalled link is obvious without a serial monitor.
#ifndef STATUS_LED
#define STATUS_LED LED_BUILTIN
#endif

// ---- I2C pins (informational) ----
// The Wire library uses the board's hardware I2C pins automatically:
//   Nano (ATmega328P):    SDA = A4, SCL = A5
//   Pro Micro (32U4):     SDA = D2, SCL = D3
// No pin numbers are passed to Wire.begin() — changing boards just works.

// ---- Serial debug ----
static const uint32_t DEBUG_BAUD = 115200;

// ---- LFO (Phase 3) ----
// PWM output → RC smoothing filter → 100 kΩ series → AT-ONE toggle →
// existing V6 "VCF CUTOFF MODULATION INPUT" pads. Arduino's default
// Timer1 PWM at 490 Hz; the 10 kΩ + 1 µF RC has its corner at ~16 Hz,
// so the carrier is suppressed to ~3 % at the filter input.
#ifndef LFO_PWM_PIN
#define LFO_PWM_PIN 9    // OC1A
#endif

// LED brightness modulated by the LFO. Always shows the rate
// regardless of toggle position — the toggle just gates the modulation
// signal to the filter, the LED reflects the internal LFO state.
#ifndef LFO_LED_PIN
#define LFO_LED_PIN 10   // OC1B
#endif

// LFO defaults. Rate is stored as Hz × 10 for 0.1 Hz resolution.
static const uint16_t LFO_DEFAULT_RATE_HZ_X10 = 25;   // 2.5 Hz
static const uint8_t  LFO_DEFAULT_DEPTH       = 200;  // ~78 % swing around centre
static const uint8_t  LFO_DEFAULT_CENTER      = 128;  // mid-rail (2.5 V after filter)
