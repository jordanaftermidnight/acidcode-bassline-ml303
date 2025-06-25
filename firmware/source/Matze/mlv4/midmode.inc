mainloop_midmode_start

mainloop_midmode
	
  	;# Watchdog-Timer löschen
  	clrwdt
  	
	;# Alle LED`s löschen
	call	clr_leds
	
	;# MID-LED setzen
	bsf		LED_REG_N9, LED_N9
	
	;# Config-Bits
	btfsc	CFG, CFG_S_PGM
	bsf		LED_REG_N1, LED_N1
	btfsc	CFG, CFG_R_PGM
	bsf		LED_REG_N3, LED_N3
	btfsc	CFG, CFG_S_SYNC
	bsf		LED_REG_N5, LED_N5
	btfss	CFG, CFG_S_SYNC
	bsf		LED_REG_N6, LED_N6
	btfsc	CFG, CFG_S_MIDI
	bsf		LED_REG_N8, LED_N8
	
	;# Midi-Channel Bits
	btfsc	MIDI_CHANNEL, 3
	bsf		LED_REG_DOWN, LED_DOWN
	btfsc	MIDI_CHANNEL, 2
	bsf		LED_REG_UP, LED_UP
	btfsc	MIDI_CHANNEL, 1
	bsf		LED_REG_ACCENT, LED_ACCENT
	btfsc	MIDI_CHANNEL, 0
	bsf		LED_REG_SLIDE, LED_SLIDE
	
	;# LED`s ausgeben
	call	set_leds_sysmode
	
	;# Tastatur einlesen
	call	get_keyboard
	
	;# Keyboard-Event?
	btfss	EVENT, EVENT_KEYPRESS
	bra		mi_noevent
	
	;# Event löschen
	bcf		EVENT, EVENT_KEYPRESS
	
	;# Config
	movlw	KEYPRESS_N1
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	btg		CFG, CFG_S_PGM
	movlw	KEYPRESS_N3
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	btg		CFG, CFG_R_PGM
	movlw	KEYPRESS_N5
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
  	call	togglemode1
	movlw	KEYPRESS_N6
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	call	togglemode2
	movlw	KEYPRESS_N8
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	btg		CFG, CFG_S_MIDI
	
	;# Midi-Channel
	movlw	KEYPRESS_DOWN
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	btg		MIDI_CHANNEL, 3
	movlw	KEYPRESS_UP
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	btg		MIDI_CHANNEL, 2
	movlw	KEYPRESS_ACCENT
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	btg		MIDI_CHANNEL, 1
	movlw	KEYPRESS_SLIDE
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	btg		MIDI_CHANNEL, 0
	
	;# In den Normalmode wechseln
	movlw	KEYPRESS_FUNC
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	goto	mi_exit
	
mi_noevent

  	;# Hauptschleife von vorne beginnen
   	goto mainloop_midmode

mi_exit
	call	eesavecfg
	goto	mainloop_normalmode_start
	
togglemode1
	bsf		CFG, CFG_S_SYNC
	return	

togglemode2
	bcf		CFG, CFG_S_SYNC
	return	
