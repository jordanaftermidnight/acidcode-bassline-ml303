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
// Pro Micro on-board LED. Toggles on every successful packet receive so a
// stalled link is obvious without a serial monitor.
#ifndef STATUS_LED
#define STATUS_LED LED_BUILTIN
#endif

// ---- Serial debug ----
// 115200 keeps Pro Micro USB-CDC happy and is fast enough not to delay loop().
static const uint32_t DEBUG_BAUD = 115200;
