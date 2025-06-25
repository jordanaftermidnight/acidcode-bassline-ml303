BPM_INIT	
	return

BPM_TICK
	movlw	0xF8
	movwf	MIDI_BUF0
	call	usart_out

	return


BPM_TICK1

	;# Note setzen
	bcf		PORT_SLIDE, SLIDE 	;# Strobe = 0

	bcf		PORT_ACCENT, ACCENT	;# Accent setzen

	movlw	32
	movwf	VCO_TMP

	movff	VCO_TMP, VCOBUS		;# Daten zum VCO-Latch
	nop
	nop							;# warten
	nop
	nop
	bsf		PORT_SLIDE, SLIDE	;# Strobe
	nop
	nop							;# warten
	nop
	nop
	bcf		PORT_SLIDE, SLIDE	;# Slide aus
	nop
	nop							;# warten
	nop
	nop
	bsf		PORT_GATE, GATE		;# Gate an

	goto	MNLRETFTICK

BPM_TICK2
	goto	MNLRETFTICK

BPM_TICK3
	bcf		PORT_GATE, GATE		;# Gate aus wenn kein Slide und wenn kein White
	goto	MNLRETFTICK

BPM_TICK4
	goto	MNLRETFTICK

BPM_TICK5
	goto	MNLRETFTICK

BPM_TICK6
	goto	MNLRETFTICK

PLAYER
	btfss	IRQEVENT_TICK, 0
	goto	MNLRETFTICK

	bcf		IRQEVENT_TICK, 0

	movlw	6
  	xorwf 	BPM_BEAT24,W
  	btfsc 	STATUS,Z
  	goto 	BPM_TICK1	
	
	movlw	5
  	xorwf 	BPM_BEAT24,W
  	btfsc 	STATUS,Z
  	goto 	BPM_TICK2
	
	movlw	4
  	xorwf 	BPM_BEAT24,W
  	btfsc 	STATUS,Z
  	goto 	BPM_TICK3
	
	movlw	3
  	xorwf 	BPM_BEAT24,W
  	btfsc 	STATUS,Z
  	goto 	BPM_TICK4
	
	movlw	2
  	xorwf 	BPM_BEAT24,W
  	btfsc 	STATUS,Z
  	goto 	BPM_TICK5
	
	movlw	1
  	xorwf 	BPM_BEAT24,W
  	btfsc 	STATUS,Z
  	goto 	BPM_TICK6

MNLRETFTICK
	return

