IRQ
	clrwdt
	movwf   IRQ_TMP
	movff   STATUS, STATUS_TMP
	movff   BSR, BSR_TMP

IRQCheck
	;# Midi IRQ ?
  	btfsc	PIR1, RCIF 	
  	bra    	IRQ_MIDI_IN

	;# Timer IRQ ?
  	btfsc	PIR1, TMR1IF 	
  	bra    	IRQ_TIMER1

IRQEnd
  	movff   BSR_TMP, BSR
  	movf    IRQ_TMP, W
  	movff   STATUS_TMP, STATUS
  	retfie
  
IRQ_MIDI_IN
  	movff	RCREG, MIDI_BYTE
  	
  	;# Statusbyte?
  	btfss	MIDI_BYTE, 7
  	bra		nostatusbyte
  	
  	;# SNDMODE ?
  	btfsc	SNDMODE, 0
  	bra		nocheckmidi
  	
  	;# PEEK SSC ?
  	btfss	CFG, CFG_S_SYNC
  	call	peek_ssc  	

	;# Program-Change (2 Bytes) ?
	movlw	0xC0
	movwf	TMP_I
	movf	MIDI_CHANNEL, w
	addwf	TMP_I, w
  	xorwf 	MIDI_BYTE,W
  	btfsc 	STATUS,Z
	bra		setcmd11

nocheckmidi
	
	;# anderer Befehl (3 Bytes)
	bra		setcmd1
	  	
  	;# Kein Statusbyte
nostatusbyte
  	
  	;# Das 2te Byte?
  	btfsc	MIDI_CMD2,7
	movff	MIDI_BYTE, MIDI_CMD2

  	btfss	MIDI_CMD2,7
	movff	MIDI_BYTE, MIDI_CMD3

  	btfss	MIDI_CMD3,7
 	call	check_midi	
  	
	bra		IRQ_MIDI_End
	
setcmd1
  	movff 	MIDI_BYTE, MIDI_CMD1
  	bsf		MIDI_CMD2,7
  	bsf		MIDI_CMD3,7

	bra		IRQ_MIDI_End	
	
setcmd11
  	movff 	MIDI_BYTE, MIDI_CMD1
  	bcf		MIDI_CMD2,7
  	bsf		MIDI_CMD3,7

	bra		 IRQ_MIDI_End	
	
IRQ_MIDI_End	
  	btfss	RCSTA, OERR
  	bra 	IRQ_MIDI_NoOverrunError
  	bcf		RCSTA, CREN	; overrun errors may be handled here
  	bsf		RCSTA, CREN
IRQ_MIDI_NoOverrunError	
  	bcf		PIR1, RCIF
  	bra 	IRQCheck

;------------------------------------------------------
; TIMER 1
;------------------------------------------------------
IRQ_TIMER1

	btfss	CFG, CFG_S_SYNC
	bra		irqnotick

    ; reload T1
;    movlw   -1-84
;	addwf   TMR1H, F
 ;   movlw   -1-48
  ;  addwf   TMR1L, F

	btfss	PAT_BPM, 7
	call	gettablea

	btfsc	PAT_BPM, 7
	call	gettableb
	
	call	send_tick

irqnotick
  	bcf		PIR1, TMR1IF 	
  	bra 	IRQCheck

gettablea
	movf	PAT_BPM, w
	movwf	WREG
	bcf		STATUS, C
	rlcf	WREG, W
	addlw	BPM_TABLE_A & 0xff
	movwf	TBLPTRL
	clrf	TBLPTRH
	movlw	BPM_TABLE_A >> 8
	addwfc	TBLPTRH, F
	tblrd*+
	movff	TABLAT, TMR1L
	tblrd*+
	movff	TABLAT, TMR1H
	return	
	
gettableb
	movf	PAT_BPM, w
	movwf	WREG
	bcf		STATUS, C
	rlcf	WREG, W
	addlw	BPM_TABLE_B & 0xff
	movwf	TBLPTRL
	clrf	TBLPTRH
	movlw	BPM_TABLE_B >> 8
	addwfc	TBLPTRH, F
	tblrd*+
	movff	TABLAT, TMR1L
	tblrd*+
	movff	TABLAT, TMR1H
	return	
