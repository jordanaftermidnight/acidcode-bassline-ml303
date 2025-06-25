;#---------------------------------------------------------------
;# Save to EEPROM
;#---------------------------------------------------------------
; 00 / 00..FF = BYTE A
; 10 / 00..FF = BYTE B

eeprom_save

;# 24C65
	call	I2C_Init
	call	I2C_Start
	
	movlw	0xa0			; 
	call	I2C_SendByte

	bcf		XEEH, 7
	bcf		XEEH, 6
	bcf		XEEH, 5
	movf	XEEH,w			; set address
	call	I2C_SendByte
	movf	XEEL,w			; set address
	call	I2C_SendByte
	movf	XBYT, w
	call	I2C_SendByte
	
	call	I2C_Stop

	;; wait until write cycle is finished
IICL2_BANK_Write_Poll
	;; memo: time out counter should be inserted here!
	bcf	TMP_W2, 0
	call	I2C_Start
	movlw	0xa0
	call	I2C_SendByte
	btfsc	TMP_W2, 0
	goto IICL2_BANK_Write_Poll

	call	I2C_Stop		; stop IIC
	
	return	

;#---------------------------------------------------------------
;# Load from EEPROM
;#---------------------------------------------------------------
eeprom_load

	call	I2C_Init
	call	I2C_Start

	movlw	0xa0			; 
	call	I2C_SendByteFast

	movf	XEEH,w			; set address
	call	I2C_SendByteFast
	movf	XEEL,w			; set address
	call	I2C_SendByteFast

	call	I2C_Start		; start IIC again
	movlw	0xa1
	call	I2C_SendByteFast
	call	I2C_ReceiveByte		; read contol-byte
	movwf	XBYT
;	call	I2C_SendAck
;	call	I2C_ReceiveByte		; read byte
;	movwf	XBYT
;	call	I2C_SendNak
	call	I2C_Stop		; stop IIC

	return	

;; --------------------------------------------------------------------------
;;  Init Routine for I2C (prepares I2C, not used in init.inc, but before
;;  *every* use of the I2C bus)
;; --------------------------------------------------------------------------
I2C_Init


  	;# Pullups aktivieren
	bcf		INTCON2, NOT_RBPU

	; Outputs
	bcf	MEMBUS_TRIS, MEMBUS_SDA
	bcf	MEMBUS_TRIS, MEMBUS_SCL
	call pause600

	bsf	MEMBUS, MEMBUS_SDA
	bsf	MEMBUS, MEMBUS_SCL
	call pause600

	return

;; --------------------------------------------------------------------------
;;  Send Start Condition (SCL=1, SDA 1->0)
;; --------------------------------------------------------------------------
I2C_Start

	bsf	MEMBUS, MEMBUS_SDA	; SDA -> 1
	bsf	MEMBUS, MEMBUS_SCL	; SCL -> 1
	call pause600
	bcf	MEMBUS, MEMBUS_SDA	; SDA -> 0
	call pause600
	bcf	MEMBUS, MEMBUS_SCL	; SCL -> 0
	return

;; --------------------------------------------------------------------------
;;  Send Stop Condition (SCL=0->1, SDA 0->1)
;; --------------------------------------------------------------------------
I2C_Stop

	bcf	MEMBUS, MEMBUS_SCL	; SCL -> 0
	bcf	MEMBUS, MEMBUS_SDA	; SDA -> 0
	call pause600
	bsf	MEMBUS, MEMBUS_SCL	; SCL -> 1
	call pause600
	bsf	MEMBUS, MEMBUS_SDA	; SDA -> 1

  	;# Pullups deaktivieren
	bsf		INTCON2, NOT_RBPU

	return

;; --------------------------------------------------------------------------
;;  Check Ack
;; --------------------------------------------------------------------------
I2C_CheckAck

	bsf	MEMBUS_TRIS, MEMBUS_SDA	; SDA = input

	call pause600
	bsf	MEMBUS, MEMBUS_SCL	; SCL -> 1
;waitack
	call pause600
	call pause600
	btfsc	MEMBUS, MEMBUS_SDA
	bsf		LED_REG_TIME, LED_TIME
	
	bcf	MEMBUS, MEMBUS_SCL	; SCL -> 0
						; (wait > 1.3 us)

	bcf	MEMBUS_TRIS, MEMBUS_SDA	; SDA = output

	return
	
;; --------------------------------------------------------------------------
;;  Send Ack/Nak
;; --------------------------------------------------------------------------
I2C_SendNak

	;; currently SCL = 0 and SDA=1
	bsf	MEMBUS, MEMBUS_SDA	; SDA -> 1
	goto	I2C_SendAck_Cont
	;; ------------------------------------------------------------------
I2C_SendAck
	;; currently SCL = 0 and SDA=1
	bcf	MEMBUS, MEMBUS_SDA	; SDA -> 0
I2C_SendAck_Cont
	call pause600
	bsf	MEMBUS, MEMBUS_SCL	; SCL -> 1
	call pause600
	bcf	MEMBUS, MEMBUS_SCL	; SCL -> 0
	return
	
;; --------------------------------------------------------------------------
;;  Send Byte
;;  IN:	byte to send in W
;; --------------------------------------------------------------------------
I2C_SendByte

	movwf	I2C_BUFFER			; store value
	movlw	0x08				; loop 8 times
	movwf	I2C_CTR
I2C_SendByteLoop
	btfsc	I2C_BUFFER, 7
	bsf	MEMBUS, MEMBUS_SDA	; SDA -> 1
	btfss	I2C_BUFFER, 7
	bcf	MEMBUS, MEMBUS_SDA	; SDA -> 0
	call i2cpause ;OK
	call i2cpause ;OK
	call i2cpause ;OK
	call i2cpause ;OK
	call i2cpause ;OK
	call i2cpause ;OK +
	bsf	MEMBUS, MEMBUS_SCL	; SCL -> 1
	call i2cpause ;OK
	call i2cpause ;OK
	call i2cpause ;OK
	call i2cpause ;OK
	call i2cpause ;OK
	call i2cpause ;OK +
	bcf	MEMBUS, MEMBUS_SCL	; SCL -> 0
						; (wait > 1.3 us)
	rlcf	I2C_BUFFER, F			; shift left value
	decfsz	I2C_CTR, F			; loop
	goto	I2C_SendByteLoop
	call i2cpause ;OK
	call i2cpause ;OK
	call i2cpause ;OK +
;	call	I2C_SendNak	
	goto	I2C_CheckAck			; check the acknowledge

I2C_SendByteFast

	movwf	I2C_BUFFER			; store value
	movlw	0x08				; loop 8 times
	movwf	I2C_CTR
I2C_SendByteFastLoop
	btfsc	I2C_BUFFER, 7
	bsf	MEMBUS, MEMBUS_SDA	; SDA -> 1
	btfss	I2C_BUFFER, 7
	bcf	MEMBUS, MEMBUS_SDA	; SDA -> 0
	call pause600
	call pause600
	call pause600
	call pause600
	bsf	MEMBUS, MEMBUS_SCL	; SCL -> 1
	call pause600
	call pause600
	call pause600
	call pause600
	bcf	MEMBUS, MEMBUS_SCL	; SCL -> 0
						; (wait > 1.3 us)
	rlcf	I2C_BUFFER, F			; shift left value
	decfsz	I2C_CTR, F			; loop
	goto	I2C_SendByteFastLoop
	call pause600
	call pause600
;	call	I2C_SendNak	
	goto	I2C_CheckAck			; check the acknowledge

;; --------------------------------------------------------------------------
;;  Receive Byte
;;  OUT: received byte in W
;; --------------------------------------------------------------------------
I2C_ReceiveByte

	clrf	I2C_BUFFER
	bsf	MEMBUS_TRIS, MEMBUS_SDA
	movlw	0x08				; loop 8 times
	movwf	I2C_CTR
I2C_ReceiveByteLoop
	call pause600
	call pause600
	bsf	MEMBUS, MEMBUS_SCL	; SCL -> 1
	call pause600
	call pause600
	rlcf	I2C_BUFFER, F			; shift left buffer
	bcf	I2C_BUFFER, 0			; copy status of SDA into rightmost bit
	btfsc	MEMBUS, MEMBUS_SDA
	bsf	I2C_BUFFER, 0
	
	bcf	MEMBUS, MEMBUS_SCL	; SCL -> 0
						; (wait > 1.3 us)
	call pause600
	decfsz	I2C_CTR, F			; loop
	goto	I2C_ReceiveByteLoop

	movf	I2C_BUFFER, W			; now copy the received value into W

	bcf	MEMBUS_TRIS, MEMBUS_SDA
	return

i2cpause
	call i2cpause2
	call i2cpause2
	return

i2cpause2
	clrwdt
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	clrwdt
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	clrwdt
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	clrwdt
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
pause600
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	clrwdt
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop



	clrwdt
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	return

