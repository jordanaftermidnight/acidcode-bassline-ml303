mainloop_sysmode_start

mainloop_sysmode
	
  	;# Watchdog-Timer löschen
  	clrwdt
  	
	;# Alle LED`s löschen
	call	clr_leds
	
	;# SYS-LED setzen
	bsf		LED_REG_N11, LED_N11
	
	;# Version-LED`s setzen
	bcf		LED_REG_N1, LED_N1
	bsf		LED_REG_N3, LED_N3
	bcf		LED_REG_N5, LED_N5
	bcf		LED_REG_N6, LED_N6
	bsf		LED_REG_N8, LED_N8
	bsf		LED_REG_N10, LED_N10
	bcf		LED_REG_N12, LED_N12
	bcf		LED_REG_N13, LED_N13
	
	btfsc	VCO_OFF, 0
	bsf		LED_REG_DOWN, LED_DOWN
	
	;# LED`s ausgeben
	call	set_leds_sysmode

	;# Tastatur einlesen
	call	get_keyboard
	
	;# Keyboard-Event?
	btfss	EVENT, EVENT_KEYPRESS
	bra		sy_noevent
	
	;# Event löschen
	bcf		EVENT, EVENT_KEYPRESS
	
	;# Sound-Off
	movlw	KEYPRESS_DOWN
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	btg		VCO_OFF, 0
	
	;# In den Normalmode wechseln
	movlw	KEYPRESS_FUNC
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	goto	mainloop_normalmode_start
	
	;# Reboot
	movlw	KEYPRESS_TAP
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	reset
	
sy_noevent

  	;# Hauptschleife von vorne beginnen
   	goto mainloop_sysmode

