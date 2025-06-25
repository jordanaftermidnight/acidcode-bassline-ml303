mainloop_edtmode_start

mainloop_edtmode
	
  	;# Watchdog-Timer löschen
  	clrwdt
  	
	;# Alle LED`s löschen
	call	clr_leds
	
	;# EDT-LED setzen
	bsf		LED_REG_N4, LED_N4
	
	;# Len-Bits
	btfsc	PAT_LEN, 3
	bsf		LED_REG_DOWN, LED_DOWN
	btfsc	PAT_LEN, 2
	bsf		LED_REG_UP, LED_UP
	btfsc	PAT_LEN, 1
	bsf		LED_REG_ACCENT, LED_ACCENT
	btfsc	PAT_LEN, 0
	bsf		LED_REG_SLIDE, LED_SLIDE
	
	tstfsz	PAT_LEN
	bra		nonzero
	bsf		PAT_LEN, 0
	
nonzero	
	;# LED`s ausgeben
	call	set_leds_edtmode
	
	;# Tastatur einlesen
	call	get_keyboard
	
	;# Keyboard-Event?
	btfss	EVENT, EVENT_KEYPRESS
	bra		ed_noevent
	
	;# Event löschen
	bcf		EVENT, EVENT_KEYPRESS
	
	;# LEN
	movlw	KEYPRESS_DOWN
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	btg		PAT_LEN, 3
	movlw	KEYPRESS_UP
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	btg		PAT_LEN, 2
	movlw	KEYPRESS_ACCENT
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	btg		PAT_LEN, 1
	movlw	KEYPRESS_SLIDE
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	btg		PAT_LEN, 0
	
	;# In den Normalmode wechseln
	movlw	KEYPRESS_FUNC
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	bra		ed_exit
	
	;# TR1UP
	movlw	KEYPRESS_N5
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	bra		TR1UP
	
	;# TR1DN
	movlw	KEYPRESS_N6
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	bra		TR1DN
	
	;# TR6UP
	movlw	KEYPRESS_N8
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	bra		TR6UP
	
	;# TR6DN
	movlw	KEYPRESS_N10
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	bra		TR6DN
	
ed_noevent

  	;# Hauptschleife von vorne beginnen
   	goto mainloop_edtmode

ed_exit
	call	eesavecfg
	goto	mainloop_normalmode_start

TR1UP
	clrf	PAT_POS
	bsf		LED_REG_N5, LED_N5
	call	set_leds_edtmode
tr1uploop
	call	eereadpos_a
	movff	PAT_MEM_A, TMP_W
	bcf		TMP_W, 7
	bcf		TMP_W, 6
	bcf		TMP_W, 5
	bcf		TMP_W, 4
	incf	TMP_W, 1
	bcf		TMP_W, 7
	bcf		TMP_W, 6
	bcf		TMP_W, 5
	bcf		TMP_W, 4
	btfsc	PAT_MEM_A, 7
	bsf		TMP_W, 7
	btfsc	PAT_MEM_A, 6
	bsf		TMP_W, 6
	btfsc	PAT_MEM_A, 5
	bsf		TMP_W, 5
	btfsc	PAT_MEM_A, 4
	bsf		TMP_W, 4
	movff	TMP_W, PAT_MEM_A
	call	eesavepos_a
	incf	PAT_POS, 1
	movlw	0x10
	cpfseq	PAT_POS
	bra		tr1uploop
	bra		ed_noevent
	
TR1DN
	clrf	PAT_POS
	bsf		LED_REG_N6, LED_N6
	call	set_leds_edtmode
tr1dnloop
	call	eereadpos_a
	movff	PAT_MEM_A, TMP_W
	bcf		TMP_W, 7
	bcf		TMP_W, 6
	bcf		TMP_W, 5
	bcf		TMP_W, 4
	decf	TMP_W, 1
	bcf		TMP_W, 7
	bcf		TMP_W, 6
	bcf		TMP_W, 5
	bcf		TMP_W, 4
	btfsc	PAT_MEM_A, 7
	bsf		TMP_W, 7
	btfsc	PAT_MEM_A, 6
	bsf		TMP_W, 6
	btfsc	PAT_MEM_A, 5
	bsf		TMP_W, 5
	btfsc	PAT_MEM_A, 4
	bsf		TMP_W, 4
	movff	TMP_W, PAT_MEM_A
	call	eesavepos_a
	incf	PAT_POS, 1
	movlw	0x10
	cpfseq	PAT_POS
	bra		tr1dnloop
	bra		ed_noevent
	
TR6UP
	clrf	PAT_POS
	bsf		LED_REG_N8, LED_N8
	call	set_leds_edtmode
tr6uploop
	call	eereadpos_a
	movff	PAT_MEM_A, TMP_W
	bcf		TMP_W, 7
	bcf		TMP_W, 6
	bcf		TMP_W, 5
	bcf		TMP_W, 4
	incf	TMP_W, 1
	incf	TMP_W, 1
	incf	TMP_W, 1
	incf	TMP_W, 1
	incf	TMP_W, 1
	incf	TMP_W, 1
	bcf		TMP_W, 7
	bcf		TMP_W, 6
	bcf		TMP_W, 5
	bcf		TMP_W, 4
	btfsc	PAT_MEM_A, 7
	bsf		TMP_W, 7
	btfsc	PAT_MEM_A, 6
	bsf		TMP_W, 6
	btfsc	PAT_MEM_A, 5
	bsf		TMP_W, 5
	btfsc	PAT_MEM_A, 4
	bsf		TMP_W, 4
	movff	TMP_W, PAT_MEM_A
	call	eesavepos_a
	incf	PAT_POS, 1
	movlw	0x10
	cpfseq	PAT_POS
	bra		tr6uploop
	bra		ed_noevent
	
TR6DN
	clrf	PAT_POS
	bsf		LED_REG_N10, LED_N10
	call	set_leds_edtmode
tr6dnloop
	call	eereadpos_a
	movff	PAT_MEM_A, TMP_W
	bcf		TMP_W, 7
	bcf		TMP_W, 6
	bcf		TMP_W, 5
	bcf		TMP_W, 4
	decf	TMP_W, 1
	decf	TMP_W, 1
	decf	TMP_W, 1
	decf	TMP_W, 1
	decf	TMP_W, 1
	decf	TMP_W, 1
	bcf		TMP_W, 7
	bcf		TMP_W, 6
	bcf		TMP_W, 5
	bcf		TMP_W, 4
	btfsc	PAT_MEM_A, 7
	bsf		TMP_W, 7
	btfsc	PAT_MEM_A, 6
	bsf		TMP_W, 6
	btfsc	PAT_MEM_A, 5
	bsf		TMP_W, 5
	btfsc	PAT_MEM_A, 4
	bsf		TMP_W, 4
	movff	TMP_W, PAT_MEM_A
	call	eesavepos_a
	incf	PAT_POS, 1
	movlw	0x10
	cpfseq	PAT_POS
	bra		tr6dnloop
	bra		ed_noevent
	
