set_accent
	movf 	GATEBUS_TMP, w
  	movwf 	TMP_J
  	bsf 	TMP_J, GATEBUS_ACCENT
  	movff 	TMP_J, GATEBUS
  	movff 	TMP_J, GATEBUS_TMP
  	return

clr_accent
	movf 	GATEBUS_TMP, w
	movwf 	TMP_J
  	bcf 	TMP_J, GATEBUS_ACCENT
  	movff 	TMP_J, GATEBUS
  	movff 	TMP_J, GATEBUS_TMP
  	return

set_slide
  	movf	GATEBUS_TMP, w
  	movwf 	TMP_J
  	bsf 	TMP_J, GATEBUS_SLIDE
  	movff 	TMP_J, GATEBUS
  	movff 	TMP_J, GATEBUS_TMP
  	return

clr_slide
	movf	GATEBUS_TMP, w
  	movwf 	TMP_J
  	bcf 	TMP_J, GATEBUS_SLIDE
  	movff 	TMP_J, GATEBUS
  	movff	TMP_J, GATEBUS_TMP
	return

set_gate
  	btfsc	VCO_OFF, 0
  	bra		nogate
  	movf 	GATEBUS_TMP, w
  	movwf 	TMP_J
  	bsf 	TMP_J, GATEBUS_GATE
  	movff 	TMP_J, GATEBUS
  	movff 	TMP_J, GATEBUS_TMP
nogate  
	return

clr_gate
  	movf 	GATEBUS_TMP, w
  	movwf 	TMP_J
  	bcf 	TMP_J, GATEBUS_GATE
  	movff 	TMP_J, GATEBUS
  	movff 	TMP_J, GATEBUS_TMP
  	btfsc 	CFG, CFG_S_MIDI
  	call 	play_midi_out_off
  	return

play_tick

	;# nur wenn RUN
	btfss	RUN, 0
	bra		play_end

    ;# Tick 0
	movlw	0
  	xorwf 	TICK,W
  	btfsc 	STATUS,Z
    bra		play_tick_0

    ;# Tick 2
	movlw	2
  	xorwf 	TICK,W
  	btfsc 	STATUS,Z
    bra		play_tick_2

    ;# Tick 4
	movlw	4
  	xorwf 	TICK,W
  	btfsc 	STATUS,Z
    bra		play_tick_4

next_tick

play_end
	return
	
;-------------------------------------------------	
play_tick_0

	clrwdt

	;# neue Position laden
	incf	PAT_LEN, 1
	movf	PAT_LEN, W
  	xorwf 	PAT_POS,W
  	btfsc 	STATUS,Z
	clrf	PAT_POS
	call	eereadpos_a
	call	eereadpos_b
	decf	PAT_LEN, 1
	incf	PAT_POS, 1

	;# neue Note auf VCO geben
	movff	PAT_MEM_A, TMP_J
	bcf		TMP_J, 7
	bcf		TMP_J, 6
	bcf		TMP_J, 5
	bcf		TMP_J, 4
	movf	TMP_J, w
	call	inc_23
	
	btfsc	PAT_MEM_A, 7
	call	dec_12
	btfsc	PAT_MEM_A, 6
	call	inc_12
	
	movff	TMP_J, VCO

	;# VCO
	clrf	DATABUS_STROBE
	
  	;# Strobe löschen
	call	clr_slide
	
	nop
	nop
	nop
	nop
	nop
	
	;# VCO ausgeben
	movff	VCO, DATABUS

	nop
	nop
	nop
	nop
	nop

	bsf		DATABUS_STROBE, DATABUS_E_STROBE
	
	nop
	nop
	nop
	nop
	nop

	;# Accent an
	btfsc	PAT_MEM_A, 5
	call	set_accent
	btfss	PAT_MEM_A, 5
	call	clr_accent

	;# Slide an, aber nur wenn Black
	btfsc	PAT_MEM_B, 7
	call	set_slide
	
  	;# Slide löschen - nur wenn die letzte Note nicht Slide war
  	btfss	LAST_SLIDE, LED_SLIDE
	call	clr_slide
	
  	;# Slide merken
	bcf		LAST_SLIDE, LED_SLIDE
	btfsc	PAT_MEM_A, 4
	bsf		LAST_SLIDE, LED_SLIDE
	
	clrwdt

	;# Gate an, aber nur wenn Black-Timing oder White-Timing
	btfsc	PAT_MEM_B, 7
	call	set_gate
	btfsc	PAT_MEM_B, 6
	call	set_gate

	;# Midi Out
	btfsc	LAST_WHITE, 0
	bra		play_tick_1_end
	btfsc	PAT_MEM_B, 5
	bra		play_tick_1_end
    btfsc 	CFG, CFG_S_MIDI
    call 	play_midi_out_on

play_tick_1_end
	bra		next_tick	
	
;-------------------------------------------------	
play_tick_2
	clrwdt
	;# White speichern
	bcf		LAST_WHITE, 0
	btfsc	PAT_MEM_B, 6
	bsf		LAST_WHITE, 0

	bra	next_tick	
	
;-------------------------------------------------	
play_tick_4

	clrwdt
	;# Gate aus, aber nur wenn keine Slide-Note und wenn kein Accent und wenn kein White
	btfsc	PAT_MEM_A, 4
	bra		npt4

	btfsc	PAT_MEM_B, 6
	bra		npt4
	
	movff	PAT_POS, TMP_X
	movff	PAT_MEM_B, TMP_B

	incf	PAT_LEN, 1
	movf	PAT_LEN, W
  	xorwf 	PAT_POS,W
  	btfsc 	STATUS,Z
	clrf	PAT_POS
	decf	PAT_LEN, 1
	call	eereadpos_b
	movff	PAT_MEM_B, PAT_TMP_B
	movff	TMP_B, PAT_MEM_B
	movff	TMP_X, PAT_POS
	call	eereadpos_b

	btfsc	PAT_TMP_B, 6
	bra		npt4
	
;	bra	npt3
gateoffs
	call	clr_gate
	
npt4
    btfss 	CFG, CFG_S_MIDI
    bra		npt44
	movf	LASTSLIDEVCO, w
	bnz		play_midi_out_offslide
npt44

	;# Slide-Note speichern	
	btfsc	PAT_MEM_A, 4
	movff	VCO, LASTSLIDEVCO
	
	bra	next_tick	
	
;-------------------------------------------------	
play_midi_out_on

	;# Note On
	movlw	144
	movwf	MIDI_OUTBYTE
	movf	MIDI_CHANNEL, w
	addwf	MIDI_OUTBYTE, w
	movwf	MIDI_OUTBYTE
  	call	usart_out

  	movff	VCO, MIDI_OUTBYTE
  	bcf		MIDI_OUTBYTE, 7
  	bcf		MIDI_OUTBYTE, 6
  	call	usart_out

  	;# Accent?
	movlw	99
	btfsc	PAT_MEM_A, 5
	movlw	127
	movwf	MIDI_OUTBYTE
  	call	usart_out

	return

play_midi_out_off

	;# Note Off
	movlw	144
	movwf	MIDI_OUTBYTE
	movf	MIDI_CHANNEL, w
	addwf	MIDI_OUTBYTE, w
	movwf	MIDI_OUTBYTE
  	call	usart_out
  	
  	movff	VCO, MIDI_OUTBYTE
  	bcf		MIDI_OUTBYTE, 7
  	bcf		MIDI_OUTBYTE, 6
  	call	usart_out

	clrf	MIDI_OUTBYTE
  	call	usart_out

	return

play_midi_out_offslide

	;# Note Off
	movlw	144
	movwf	MIDI_OUTBYTE
	movf	MIDI_CHANNEL, w
	addwf	MIDI_OUTBYTE, w
	movwf	MIDI_OUTBYTE
  	call	usart_out
  	
  	movff	LASTSLIDEVCO, MIDI_OUTBYTE
  	bcf		MIDI_OUTBYTE, 7
  	bcf		MIDI_OUTBYTE, 6
  	call	usart_out

	clrf	MIDI_OUTBYTE
  	call	usart_out
  	clrf	LASTSLIDEVCO

	return

inc_23
	incf TMP_J, 1
	incf TMP_J, 1
	incf TMP_J, 1
	incf TMP_J, 1

	incf TMP_J, 1
	incf TMP_J, 1
	incf TMP_J, 1
	incf TMP_J, 1

	incf TMP_J, 1
	incf TMP_J, 1
	incf TMP_J, 1

inc_12
	incf TMP_J, 1
	incf TMP_J, 1
	incf TMP_J, 1
	incf TMP_J, 1

	incf TMP_J, 1
	incf TMP_J, 1
	incf TMP_J, 1
	incf TMP_J, 1

	incf TMP_J, 1
	incf TMP_J, 1
	incf TMP_J, 1
	incf TMP_J, 1
	return	

dec_12
	decf TMP_J, 1	
	decf TMP_J, 1	
	decf TMP_J, 1	
	decf TMP_J, 1	

	decf TMP_J, 1	
	decf TMP_J, 1	
	decf TMP_J, 1	
	decf TMP_J, 1	

	decf TMP_J, 1	
	decf TMP_J, 1	
	decf TMP_J, 1	
	decf TMP_J, 1	
	return
		
