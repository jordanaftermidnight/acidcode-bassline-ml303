IRQ
	movwf   IRQ_TMP
	movff   STATUS, STATUS_TMP
	movff   BSR, BSR_TMP

IRQCheck
  	btfsc	PIR1, RCIF 	
  	goto  	IRQ_MIDI_IN

	;# Timer1 IRQ ?
  	btfsc	PIR1, TMR1IF 	
	;# Midi IRQ ?
  	goto  	IRQ_BPM_TICK

	;# Timer2 IRQ ?
  	btfsc	PIR1, TMR2IF 	
  	goto  	IRQ_LED_MPLEX

IRQEnd
  	movff   BSR_TMP, BSR
  	movf    IRQ_TMP, W
  	movff   STATUS_TMP, STATUS
  	retfie

IRQ_INIT
	movlw   (1 << RCIE) | (1 << TMR1IE) | (1 << TMR2IE)
;	movlw   (1 << RCIE) | (1 << TMR2IE)
;	movlw   (1 << RCIE)

 	movwf   PIE1
	bcf		PIE1, TXIE
  	clrf    PIE2                    ; clear all other IRQs

  	;# set baudrate to 31250 baud
	movlw	(1 << TXEN)			
  	movwf	TXSTA
  	movlw	2*0x0a-1
  	movwf	SPBRG

  	;# Configure Receive Status and Control Register
  	movlw	(1 << SPEN) | (1 << CREN)
  	movwf	RCSTA

  	;# make sure that USART Receive Buffer is empty
  	bcf     RCSTA, CREN
  	movf    RCREG, W
  	bsf     RCSTA, CREN
	
  	;# enable maskable IRQs
  	movlw   (1 << GIE) | (1 << PEIE)
  	movwf   INTCON

	return

IRQ_LED_MPLEX
	call	LED_MPLEX
	bcf		PIR1, TMR2IF
	goto	IRQCheck

IRQ_BPM_TICK

	bsf		IRQEVENT_TICK, 0

	decfsz	BPM_BEAT24
	goto	IRQ_BPM_TICK_NOBEAT

	movlw	6
	movwf	BPM_BEAT24

IRQ_BPM_TICK_NOBEAT

retftick

	movlw	0xF8
	movwf	TXREG

	movlw	0xA8	
	movwf	TMR1H
	movlw	0x00
	movwf	TMR1L

	bcf		PIR1, TXIF
	bcf		PIR1, TMR1IF
	goto	IRQCheck



;-------------------------------------------------------------
;# Midi Out
;-------------------------------------------------------------
usart_out
    btfss   PIR1,TXIF      
    bra    	usart_out
    movff  	MIDI_BUF0, TXREG          
	return

;-------------------------------------------------------------
;# Midi In
;-------------------------------------------------------------
IRQ_MIDI_IN
	movff	RCREG, MIDI_BUF1
  	btfss	RCSTA, OERR
  	bra 	IRQ_MIDI_NoOverrunError
  	bcf		RCSTA, CREN	; overrun errors may be handled here
	TABLE_ADDR 	TXT_ERROR_02_1
	call	LCD_TEXT
	call	LCD_DELAY_LONG
  	bsf		RCSTA, CREN
IRQ_MIDI_NoOverrunError	
  	bcf		PIR1, RCIF
  	bra 	IRQCheck

