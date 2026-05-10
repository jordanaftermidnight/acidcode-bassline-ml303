/*
 * PIC18LF452 MSSP I2C master implementation.
 * See i2c_master.h for protocol and timing notes.
 */

#include <xc.h>
#include "i2c_master.h"

/*
 * SSPADD value for 100 kHz at 10 MHz oscillator.
 * Formula: SSPADD = (Fosc / (4 * F_SCL)) - 1
 *        = (10_000_000 / 400_000) - 1 = 24
 * Drop to 49 for 50 kHz if you see noise-related corruption.
 */
#define SSPADD_100KHZ_AT_10MHZ  24

void I2C_Master_Init(void) {
    /* RC3=SCL, RC4=SDA must be inputs — the MSSP peripheral controls
     * direction internally. Setting TRIS as input avoids contention. */
    TRISCbits.TRISC3 = 1;
    TRISCbits.TRISC4 = 1;

    SSPSTAT = 0x00;                       /* slew rate control on, SMBus off */
    SSPCON1 = 0x28;                       /* SSPEN=1, master mode (0b1000) */
    SSPCON2 = 0x00;
    SSPADD  = SSPADD_100KHZ_AT_10MHZ;
}

void I2C_Master_Wait(void) {
    /* Bus idle when neither a Start/Stop/Restart/Ack/Receive is in progress
     * (low 5 bits of SSPCON2 all 0) AND R/W in SSPSTAT is 0. */
    while ((SSPCON2 & 0x1F) || (SSPSTAT & 0x04)) { ; }
}

void I2C_Master_Start(void) {
    I2C_Master_Wait();
    SSPCON2bits.SEN = 1;
    while (SSPCON2bits.SEN) { ; }
}

void I2C_Master_RepeatedStart(void) {
    I2C_Master_Wait();
    SSPCON2bits.RSEN = 1;
    while (SSPCON2bits.RSEN) { ; }
}

void I2C_Master_Stop(void) {
    I2C_Master_Wait();
    SSPCON2bits.PEN = 1;
    while (SSPCON2bits.PEN) { ; }
}

uint8_t I2C_Master_Write(uint8_t b) {
    I2C_Master_Wait();
    SSPBUF = b;
    while (SSPSTATbits.BF) { ; }          /* wait for transmit buffer empty */
    I2C_Master_Wait();
    return SSPCON2bits.ACKSTAT;           /* 0 = ACK, 1 = NACK */
}

uint8_t I2C_Master_SendPacket(uint8_t slave_addr_7bit, const void *buf, uint8_t len) {
    const uint8_t *p = (const uint8_t *)buf;

    I2C_Master_Start();

    if (I2C_Master_Write(slave_addr_7bit << 1) != 0) {
        I2C_Master_Stop();
        return 1;                         /* slave absent */
    }

    for (uint8_t i = 0; i < len; i++) {
        if (I2C_Master_Write(p[i]) != 0) {
            I2C_Master_Stop();
            return 2;                     /* mid-transfer NACK */
        }
    }

    I2C_Master_Stop();
    return 0;
}
