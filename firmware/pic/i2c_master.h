/*
 * I2C master driver for PIC18LF452 MSSP module.
 *
 * Configured for 100 kHz at Fosc = 10 MHz:
 *   SSPADD = (Fosc / (4 * F_SCL)) - 1 = (10MHz / 400kHz) - 1 = 24
 *
 * SCL = RC3, SDA = RC4 (TRIS bits set as inputs per MSSP requirements;
 * the peripheral drives them).
 *
 * Usage from main sequencer code:
 *   I2C_Master_Init();
 *   I2C_Master_SendPacket(ARDUINO_I2C_ADDRESS, &pkt, sizeof pkt);
 */

#ifndef I2C_MASTER_H
#define I2C_MASTER_H

#include <stdint.h>

/* Initialize MSSP for I2C master mode at 100 kHz. */
void I2C_Master_Init(void);

/* Low-level primitives — exposed for advanced use; most callers want SendPacket. */
void I2C_Master_Start(void);
void I2C_Master_RepeatedStart(void);
void I2C_Master_Stop(void);
void I2C_Master_Wait(void);

/*
 * Write one byte to the bus. Returns 0 on ACK, 1 on NACK.
 * Caller is responsible for Start/Stop framing.
 */
uint8_t I2C_Master_Write(uint8_t b);

/*
 * High-level: send a buffer to a 7-bit slave address with full Start/Stop
 * framing. Returns 0 on success, 1 if address NACKed (slave absent),
 * 2 if a data byte NACKed mid-transfer.
 */
uint8_t I2C_Master_SendPacket(uint8_t slave_addr_7bit, const void *buf, uint8_t len);

#endif /* I2C_MASTER_H */
