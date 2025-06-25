mainloop_pitchmode_start

	;# Pitchmode startet bei Position 0
	clrf	PAT_POS
	
	;# Pattern-Position aus dem EEPROM laden
	call	eereadpos_a

mainloop_pitchmode
	
  	;# Watchdog-Timer löschen
  	clrwdt
  	
	;# Alle LED`s löschen
	call	clr_leds
	
	;# PITCH-LED setzen
	bsf		LED_REG_PITCH, LED_PITCH
	
	;# Noten-LED`s setzen
	movff	PAT_MEM_A, TMP_W
	bcf		TMP_W, 7
	bcf		TMP_W, 6
	bcf		TMP_W, 5
	bcf		TMP_W, 4
	movlw	0
  	xorwf 	TMP_W,W
  	btfsc 	STATUS,Z
	bsf		LED_REG_N1, LED_N1
	movlw	1
  	xorwf 	TMP_W,W
  	btfsc 	STATUS,Z
	bsf		LED_REG_N2, LED_N2
	movlw	2
  	xorwf 	TMP_W,W
  	btfsc 	STATUS,Z
	bsf		LED_REG_N3, LED_N3
	movlw	3
  	xorwf 	TMP_W,W
  	btfsc 	STATUS,Z
	bsf		LED_REG_N4, LED_N4
	movlw	4
  	xorwf 	TMP_W,W
  	btfsc 	STATUS,Z
	bsf		LED_REG_N5, LED_N5
	movlw	5
  	xorwf 	TMP_W,W
  	btfsc 	STATUS,Z
	bsf		LED_REG_N6, LED_N6
	movlw	6
  	xorwf 	TMP_W,W
  	btfsc 	STATUS,Z
	bsf		LED_REG_N7, LED_N7
	movlw	7
  	xorwf 	TMP_W,W
  	btfsc 	STATUS,Z
	bsf		LED_REG_N8, LED_N8
	movlw	8
  	xorwf 	TMP_W,W
  	btfsc 	STATUS,Z
	bsf		LED_REG_N9, LED_N9
	movlw	9
  	xorwf 	TMP_W,W
  	btfsc 	STATUS,Z
	bsf		LED_REG_N10, LED_N10
	movlw	10
  	xorwf 	TMP_W,W
  	btfsc 	STATUS,Z
	bsf		LED_REG_N11, LED_N11
	movlw	11
  	xorwf 	TMP_W,W
  	btfsc 	STATUS,Z
	bsf		LED_REG_N12, LED_N12
	movlw	12
  	xorwf 	TMP_W,W
  	btfsc 	STATUS,Z
	bsf		LED_REG_N13, LED_N13
	
	bcf		LED_REG_DOWN, LED_DOWN
	bcf		LED_REG_UP, LED_UP
	bcf		LED_REG_ACCENT, LED_ACCENT
	bcf		LED_REG_SLIDE, LED_SLIDE
	
	btfsc	PAT_MEM_A, 7
	bsf		LED_REG_DOWN, LED_DOWN
	btfsc	PAT_MEM_A, 6
	bsf		LED_REG_UP, LED_UP
	btfsc	PAT_MEM_A, 5
	bsf		LED_REG_ACCENT, LED_ACCENT
	btfsc	PAT_MEM_A, 4
	bsf		LED_REG_SLIDE, LED_SLIDE
	
	;# LED`s ausgeben
	call	set_leds_pitchmode

	;# Tastatur einlesen
	call	get_keyboard
	
	;# Keyboard-Event?
	btfss	EVENT, EVENT_KEYPRESS
	bra		pm_noevent
	
	;# Event löschen
	bcf		EVENT, EVENT_KEYPRESS
	
	;# CLR -> zur Position 0
	movlw	KEYPRESS_CLR
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	bra		pm_pos0
	
	;# Tap -> zur nächsten Position
	movlw	KEYPRESS_TAP
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	bra		pm_tap
	
	;# Tap-Back -> zurück zur letzten Position
	movlw	KEYPRESS_BACK
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	bra		pm_back
	
	;# Noten-Keys
	movlw	KEYPRESS_N1
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	bra		pm_n1
	movlw	KEYPRESS_N2
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	bra		pm_n2
	movlw	KEYPRESS_N3
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	bra		pm_n3
	movlw	KEYPRESS_N4
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	bra		pm_n4
	movlw	KEYPRESS_N5
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	bra		pm_n5
	movlw	KEYPRESS_N6
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	bra		pm_n6
	movlw	KEYPRESS_N7
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	bra		pm_n7
	movlw	KEYPRESS_N8
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	bra		pm_n8
	movlw	KEYPRESS_N9
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	bra		pm_n9
	movlw	KEYPRESS_N10
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	bra		pm_n10
	movlw	KEYPRESS_N11
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	bra		pm_n11
	movlw	KEYPRESS_N12
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	bra		pm_n12
	movlw	KEYPRESS_N13
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	bra		pm_n13
	
	movlw	KEYPRESS_DOWN
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	bra		pm_down
	
	movlw	KEYPRESS_UP
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	bra		pm_up
	
	movlw	KEYPRESS_ACCENT
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	bra		pm_accent
	
	movlw	KEYPRESS_SLIDE
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	bra		pm_slide
	
	;# In den Normalmode wechseln
	movlw	KEYPRESS_FUNC
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	goto	mainloop_normalmode_start
	
pm_noevent

  	;# Hauptschleife von vorne beginnen
   	goto mainloop_pitchmode

;# nächste Position aus EEPROM laden	
pm_tap
	;# Note ausgeben
	call	play_tick_single

	bsf		LED_REG_TIME, LED_TIME
	call	set_leds_pitchmode
	call	lpause
	call	lpause
	call	lpause
	call	lpause

	incf	PAT_POS, 1
	call	eereadpos_a

	call	play_tick_single_off

	;# Prüfen ob Pattern-Ende erreicht wurde
	incf	PAT_LEN, 1
	movf	PAT_LEN, w
	cpfslt	PAT_POS
;	clrf	PAT_POS
	bra		pm_flashleds
	decf	PAT_LEN, 1
	bra		pm_noevent
	
;# Position 0 EEPROM laden	
pm_pos0
	bsf		LED_REG_TIME, LED_TIME
	call	set_leds_pitchmode
	call	lpause
	call	lpause
	call	lpause
	call	lpause

	clrf	PAT_POS
	call	eereadpos_a

	bra		pm_noevent
	
;# letzte Position aus EEPROM laden	
pm_back
	tstfsz	PAT_POS
	decf	PAT_POS, 1
	bsf		LED_REG_TIME, LED_TIME
	call	set_leds_pitchmode
	call	lpause
	call	lpause
	call	lpause
	call	lpause

	call	eereadpos_a

	bra		pm_noevent

;# Kurz die LED`s aufflashen lassen und dann zurück in den Normal-Mode
pm_flashleds
	decf	PAT_LEN, 1
	movlw	255
	movwf	LED_REG_A
	movwf	LED_REG_B
	movwf	LED_REG_C
	movwf	LED_REG_D
	call	set_leds_pitchmode
	call	lpause
	call	lpause
	call	lpause
	call	lpause
	call	lpause
	call	lpause
	goto	mainloop_normalmode_start
	
;# Noten-Keys
pm_n1	
	movlw	0
	bra		tmp2pata
pm_n2
	movlw	1
	bra		tmp2pata
pm_n3	
	movlw	2
	bra		tmp2pata
pm_n4	
	movlw	3
	bra		tmp2pata
pm_n5	
	movlw	4
	bra		tmp2pata
pm_n6	
	movlw	5
	bra		tmp2pata
pm_n7	
	movlw	6
	bra		tmp2pata
pm_n8	
	movlw	7
	bra		tmp2pata
pm_n9	
	movlw	8
	bra		tmp2pata
pm_n10	
	movlw	9
	bra		tmp2pata
pm_n11	
	movlw	10
	bra		tmp2pata
pm_n12	
	movlw	11
	bra		tmp2pata
pm_n13	
	movlw	12
	bra		tmp2pata

pm_down
	btg		PAT_MEM_A, 7
	call	eesavepos_a
	bra		pm_noevent

pm_up
	btg		PAT_MEM_A, 6
	call	eesavepos_a
	bra		pm_noevent

pm_accent
	btg		PAT_MEM_A, 5
	call	eesavepos_a
	bra		pm_noevent

pm_slide
	btg		PAT_MEM_A, 4
	call	eesavepos_a
	bra		pm_noevent

tmp2pata
	movwf	TMP_W
	btfsc	PAT_MEM_A,7
	bsf		TMP_W, 7
	btfsc	PAT_MEM_A,6
	bsf		TMP_W, 6
	btfsc	PAT_MEM_A,5
	bsf		TMP_W, 5
	btfsc	PAT_MEM_A,4
	bsf		TMP_W, 4
	movff	TMP_W, PAT_MEM_A
	call	eesavepos_a
	bra		pm_noevent
	
play_tick_single
	;# neue Note auf VCO geben
	movff	PAT_MEM_A, TMP_J
	bcf		TMP_J, 7
	bcf		TMP_J, 6
	bcf		TMP_J, 5
	bcf		TMP_J, 4
	movf	TMP_J, w
	call	inc_23
	
	btfsc	PAT_MEM_A, 6
	call	dec_12
	btfsc	PAT_MEM_A, 7
	call	inc_12
	
	movff	TMP_J, VCO

	;# VCO
	clrf	DATABUS_STROBE
	
  	;# Strobe löschen
	call	clr_slide
	call	clr_accent
	
	;# VCO ausgeben
	movff	VCO, DATABUS
	bsf		DATABUS_STROBE, DATABUS_E_STROBE
	
    ;# Accent an
	btfsc	PAT_MEM_A, 5
	call	set_accent

	call	set_slide
	
	nop
	nop
	nop
	nop
	nop
	nop

	call	clr_slide
	call	set_gate
	return

play_tick_single_off
	call	clr_gate
	return
	
