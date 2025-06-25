mainloop_bpmmode_start

mainloop_bpmmode
	
  	;# Watchdog-Timer löschen
  	clrwdt
  	
	;# Alle LED`s löschen
	call	clr_leds
	
	;# MID-LED setzen
	bsf		LED_REG_N7, LED_N7
	
	;# BPM-Bits
	btfsc	PAT_BPM, 7
	bsf		LED_REG_N1, LED_N1
	btfsc	PAT_BPM, 6
	bsf		LED_REG_N3, LED_N3
	btfsc	PAT_BPM, 5
	bsf		LED_REG_N5, LED_N5
	btfsc	PAT_BPM, 4
	bsf		LED_REG_N6, LED_N6
	btfsc	PAT_BPM, 3
	bsf		LED_REG_N8, LED_N8
	btfsc	PAT_BPM, 2
	bsf		LED_REG_N10, LED_N10
	btfsc	PAT_BPM, 1
	bsf		LED_REG_N12, LED_N12
	btfsc	PAT_BPM, 0
	bsf		LED_REG_N13, LED_N13
	
	;# LED`s ausgeben
	call	set_leds_bpmmode
	
	;# Tastatur einlesen
	call	get_keyboard
	
	;# Keyboard-Event?
	btfss	EVENT, EVENT_KEYPRESS
	bra		bp_noevent
	
	;# Event löschen
	bcf		EVENT, EVENT_KEYPRESS
	
	;# BPM
	movlw	KEYPRESS_N1
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	btg		PAT_BPM, 7
	movlw	KEYPRESS_N3
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	btg		PAT_BPM, 6
	movlw	KEYPRESS_N5
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	btg		PAT_BPM, 5
	movlw	KEYPRESS_N6
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	btg		PAT_BPM, 4
	movlw	KEYPRESS_N8
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	btg		PAT_BPM, 3
	movlw	KEYPRESS_N10
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	btg		PAT_BPM, 2
	movlw	KEYPRESS_N12
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	btg		PAT_BPM, 1
	movlw	KEYPRESS_N13
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	btg		PAT_BPM, 0
	
	;# In den Normalmode wechseln
	movlw	KEYPRESS_FUNC
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	bra		bp_exit
	
bp_noevent

  	;# Hauptschleife von vorne beginnen
   	goto mainloop_bpmmode

bp_exit
	call	eesavecfg
	goto	mainloop_normalmode_start
