KEY_INIT	
	clrf	KEYPRESS
	clrf	LAST_KEYPRESS
	bcf		GL_EVENT, GL_EVENT_KEY
	return

KEY_MPLEX
	movlw	0
	cpfsgt	LED_COUNT,W
	goto 	IRQ_KEY_0
	movlw	1
	cpfsgt	LED_COUNT,W
	goto 	IRQ_KEY_1
	movlw	2
	cpfsgt	LED_COUNT,W
	goto 	IRQ_KEY_2
	movlw	3
	cpfsgt	LED_COUNT,W
	goto 	IRQ_KEY_3
	movlw	4
	cpfsgt	LED_COUNT,W
	goto 	IRQ_KEY_4
	movlw	5
	cpfsgt	LED_COUNT,W
	goto 	IRQ_KEY_5
	movlw	6
	cpfsgt	LED_COUNT,W
	goto 	IRQ_KEY_6
	goto 	IRQ_KEY_7

KEY_END
	movlw	0
  	xorwf 	IRQ_KEYPRESS,W
  	btfsc 	STATUS,Z
  	goto 	KEY_CNONEWKEY
		
	;# Gleiche Taste wie beim letzten Durchlauf?
	movf	LAST_KEYPRESS, W
  	xorwf 	IRQ_KEYPRESS,W
  	btfsc 	STATUS,Z
  	goto 	KEY_NONEWKEY

	;# Taste speichern	
	movf	IRQ_KEYPRESS, W
	movwf	LAST_KEYPRESS
	movwf	KEYPRESS

	;# Event setzen
	bsf		GL_EVENT, GL_EVENT_KEY

KEY_END2
	return

KEY_NONEWKEY
	clrf	IRQ_KEYPRESS
	return

KEY_CNONEWKEY
	clrf	LAST_KEYPRESS
	clrf	IRQ_KEYPRESS
	clrf	KEYPRESS
	return

IRQ_KEY_0
	btfsc 	GL_EVENT, GL_EVENT_KEY
	goto	IRQ_NOK_0
	btfsc	KEYBUS,KEYBUS_A_IN
	call	fnKEYPRESS_N4
	btfsc	KEYBUS,KEYBUS_B_IN
	call	fnKEYPRESS_N12
	btfsc	KEYBUS,KEYBUS_C_IN
	call	fnKEYPRESS_TAP
IRQ_NOK_0
	goto	KEY_END2

IRQ_KEY_1
	btfsc 	GL_EVENT, GL_EVENT_KEY
	goto	IRQ_NOK_1
	btfsc	KEYBUS,KEYBUS_A_IN
	call	fnKEYPRESS_N3
	btfsc	KEYBUS,KEYBUS_B_IN
	call	fnKEYPRESS_N11
	btfsc	KEYBUS,KEYBUS_C_IN
	call	fnKEYPRESS_BACK
IRQ_NOK_1
	goto	KEY_END2

IRQ_KEY_2
	btfsc 	GL_EVENT, GL_EVENT_KEY
	goto	IRQ_NOK_2
	btfsc	KEYBUS,KEYBUS_A_IN
	call	fnKEYPRESS_N2
	btfsc	KEYBUS,KEYBUS_B_IN
	call	fnKEYPRESS_N10
	btfsc	KEYBUS,KEYBUS_C_IN
	call	fnKEYPRESS_TIME
IRQ_NOK_2
	goto	KEY_END2

IRQ_KEY_3
	btfsc 	GL_EVENT, GL_EVENT_KEY
	goto	IRQ_NOK_3
	btfsc	KEYBUS,KEYBUS_A_IN
	call	fnKEYPRESS_N1
	btfsc	KEYBUS,KEYBUS_B_IN
	call	fnKEYPRESS_N9
	btfsc	KEYBUS,KEYBUS_C_IN
	call	fnKEYPRESS_SLIDE
IRQ_NOK_3
	goto	KEY_END2

IRQ_KEY_4
	btfsc 	GL_EVENT, GL_EVENT_KEY
	goto	IRQ_NOK_4
	btfsc	KEYBUS,KEYBUS_A_IN
	call	fnKEYPRESS_FUNC
	btfsc	KEYBUS,KEYBUS_B_IN
	call	fnKEYPRESS_N8
	btfsc	KEYBUS,KEYBUS_C_IN
	call	fnKEYPRESS_ACCENT
IRQ_NOK_4
	goto	KEY_END2

IRQ_KEY_5
	btfsc 	GL_EVENT, GL_EVENT_KEY
	goto	IRQ_NOK_5
	btfsc	KEYBUS,KEYBUS_A_IN
	call	fnKEYPRESS_PITCH
	btfsc	KEYBUS,KEYBUS_B_IN
	call	fnKEYPRESS_N7
	btfsc	KEYBUS,KEYBUS_C_IN
	call	fnKEYPRESS_UP
IRQ_NOK_5
	goto	KEY_END2

IRQ_KEY_6
	btfsc 	GL_EVENT, GL_EVENT_KEY
	goto	IRQ_NOK_6
	btfsc	KEYBUS,KEYBUS_A_IN
	call	fnKEYPRESS_RUN
	btfsc	KEYBUS,KEYBUS_B_IN
	call	fnKEYPRESS_N6
	btfsc	KEYBUS,KEYBUS_C_IN
	call	fnKEYPRESS_DOWN
IRQ_NOK_6
	goto	KEY_END2

IRQ_KEY_7
	btfsc 	GL_EVENT, GL_EVENT_KEY
	goto	IRQ_NOK_7
	btfsc	KEYBUS,KEYBUS_A_IN
	call	fnKEYPRESS_CLR
	btfsc	KEYBUS,KEYBUS_B_IN
	call	fnKEYPRESS_N5
	btfsc	KEYBUS,KEYBUS_C_IN
	call	fnKEYPRESS_N13
IRQ_NOK_7
	goto	KEY_END

fnKEYPRESS_CLR	
	movlw KEYPRESS_CLR
	movwf IRQ_KEYPRESS
	return	
fnKEYPRESS_PITCH		
	movlw KEYPRESS_PITCH		
	movwf IRQ_KEYPRESS
	return	
fnKEYPRESS_RUN		
	movlw KEYPRESS_RUN
	movwf IRQ_KEYPRESS
	return	
fnKEYPRESS_FUNC		
	movlw KEYPRESS_FUNC
	movwf IRQ_KEYPRESS
	return	
fnKEYPRESS_N1			
	movlw KEYPRESS_N1
	movwf IRQ_KEYPRESS
	return	
fnKEYPRESS_N2			
	movlw KEYPRESS_N2
	movwf IRQ_KEYPRESS
	return	
fnKEYPRESS_N3			
	movlw KEYPRESS_N3
	movwf IRQ_KEYPRESS
	return	
fnKEYPRESS_N4			
	movlw KEYPRESS_N4
	movwf IRQ_KEYPRESS
	return	
fnKEYPRESS_N5			
	movlw KEYPRESS_N5
	movwf IRQ_KEYPRESS
	return	
fnKEYPRESS_N6			
	movlw KEYPRESS_N6
	movwf IRQ_KEYPRESS
	return	
fnKEYPRESS_N7			
	movlw KEYPRESS_N7
	movwf IRQ_KEYPRESS
	return	
fnKEYPRESS_N8			
	movlw KEYPRESS_N8
	movwf IRQ_KEYPRESS
	return	
fnKEYPRESS_N9			
	movlw KEYPRESS_N9
	movwf IRQ_KEYPRESS
	return	
fnKEYPRESS_N10	
	movlw KEYPRESS_N10
	movwf IRQ_KEYPRESS
	return	
fnKEYPRESS_N11		
	movlw KEYPRESS_N11
	movwf IRQ_KEYPRESS
	return	
fnKEYPRESS_N12		
	movlw KEYPRESS_N12
	movwf IRQ_KEYPRESS
	return	
fnKEYPRESS_N13		
	movlw KEYPRESS_N13
	movwf IRQ_KEYPRESS
	return	
fnKEYPRESS_DOWN		
	movlw KEYPRESS_DOWN
	movwf IRQ_KEYPRESS
	return	
fnKEYPRESS_UP			
	movlw KEYPRESS_UP
	movwf IRQ_KEYPRESS
	return	
fnKEYPRESS_ACCENT		
	movlw KEYPRESS_ACCENT
	movwf IRQ_KEYPRESS
	return	
fnKEYPRESS_SLIDE		
	movlw KEYPRESS_SLIDE
	movwf IRQ_KEYPRESS
	return	
fnKEYPRESS_TIME		
	movlw KEYPRESS_TIME
	movwf IRQ_KEYPRESS
	return	
fnKEYPRESS_BACK		
	movlw KEYPRESS_BACK
	movwf IRQ_KEYPRESS
	return	
fnKEYPRESS_TAP		
	movlw KEYPRESS_TAP
	movwf IRQ_KEYPRESS
	return	
