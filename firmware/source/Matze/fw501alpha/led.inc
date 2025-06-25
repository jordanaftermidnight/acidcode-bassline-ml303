LED_INIT	
	clrf	LEDBUS
	clrf	DATABUS

CLR_LEDS
	clrf	LED_REG_0
	clrf	LED_REG_1
	clrf	LED_REG_2
	clrf	LED_REG_3
	clrf	LED_REG_4
	clrf	LED_REG_5
	clrf	LED_REG_7
	return

LED_MPLEX
	bsf		KEYBUS,KEYBUS_A_IN
	bsf		KEYBUS,KEYBUS_B_IN
	bsf		KEYBUS,KEYBUS_C_IN
	movlw	0
	cpfsgt	LED_COUNT,W
	goto 	IRQ_LED_0
	movlw	1
	cpfsgt	LED_COUNT,W
	goto 	IRQ_LED_1
	movlw	2
	cpfsgt	LED_COUNT,W
	goto 	IRQ_LED_2
	movlw	3
	cpfsgt	LED_COUNT,W
	goto 	IRQ_LED_3
	movlw	4
	cpfsgt	LED_COUNT,W
	goto 	IRQ_LED_4
	movlw	5
	cpfsgt	LED_COUNT,W
	goto 	IRQ_LED_5
	movlw	6
	cpfsgt	LED_COUNT,W
	goto 	IRQ_LED_6
	goto 	IRQ_LED_7

IRQ_LED_0
	clrwdt
	movff	LED_REG_0, LED_TMP
	movlw	b'00000001'
	goto	IRQ_LED_END

IRQ_LED_1
	movff	LED_REG_1, LED_TMP
	movlw	b'00000010'
	goto	IRQ_LED_END

IRQ_LED_2
	movff	LED_REG_2, LED_TMP
	movlw	b'00000100'
	goto	IRQ_LED_END

IRQ_LED_3
	movff	LED_REG_3, LED_TMP
	movlw	b'00001000'
	goto	IRQ_LED_END

IRQ_LED_4
	movff	LED_REG_4, LED_TMP
	movlw	b'00010000'
	goto	IRQ_LED_END

IRQ_LED_5
	movff	LED_REG_5, LED_TMP
	movlw	b'00100000'
	goto	IRQ_LED_END

IRQ_LED_6
	movff	LED_REG_6, LED_TMP
	movlw	b'01000000'
	goto	IRQ_LED_END

IRQ_LED_7
	movff	LED_REG_7, LED_TMP
	movlw	b'10000000'

IRQ_LED_END
	movwf	DATABUS
	comf	LED_TMP
	movff	LED_TMP, LEDBUS
	call	KEY_MPLEX
	incf	LED_COUNT, F
	movlw	0x08
	cpfslt	LED_COUNT
	clrf	LED_COUNT
	return

