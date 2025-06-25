MODE_NORMAL

	call	CLR_LEDS
	bsf		LED_REG_FUNC, LED_FUNC

	;# Noten-Text
	TABLE_ADDR 	TXT_FNC_1
	call	LCD_TEXT
	movlw	0x47
	call	LCD_SET_CUR
	movlw	b'01111110'
	call	LCD_SET_CHR

MODE_NORMAL_LOOP

	call	PLAYER

	btfss	GL_EVENT, GL_EVENT_KEY
	goto	MODE_NORMAL_LOOP
	bcf		GL_EVENT, GL_EVENT_KEY

	;# Pitch-Mode
	movlw	KEYPRESS_PITCH
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
  	goto 	MODE_PITCH	

	goto	MODE_NORMAL_LOOP

	return
