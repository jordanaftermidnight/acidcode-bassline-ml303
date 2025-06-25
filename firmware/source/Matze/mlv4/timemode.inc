mainloop_timemode_start

	;# Timemode startet bei Position 0
	clrf	PAT_POS
	
	;# Pattern-Position aus dem EEPROM laden
	call	eereadpos_b

mainloop_timemode
	
  	;# Watchdog-Timer löschen
  	clrwdt
  	
	;# Alle LED`s löschen
	call	clr_leds
	
	;# TIME-LED setzen
	bsf		LED_REG_TIME, LED_TIME

	;# Time-Led`s
	bsf		LED_REG_BLACK, LED_PAUSE

	btfsc	PAT_MEM_B, 7
	bsf		LED_REG_BLACK, LED_BLACK
	btfsc	PAT_MEM_B, 6
	bsf		LED_REG_BLACK, LED_WHITE
	
	btfsc	PAT_MEM_B, 7
	bcf		LED_REG_PAUSE, LED_PAUSE
	btfsc	PAT_MEM_B, 6
	bcf		LED_REG_PAUSE, LED_PAUSE
		
	;# LED`s ausgeben
	call	set_leds_timemode

	;# Tastatur einlesen
	call	get_keyboard
	
	;# Keyboard-Event?
	btfss	EVENT, EVENT_KEYPRESS
	bra		tm_noevent
	
	;# Event löschen
	bcf		EVENT, EVENT_KEYPRESS
	
	;# Tap -> zur nächsten Position
	movlw	KEYPRESS_TAP
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	bra		tm_tap
	
	;# Tap-Back -> zurück zur letzten Position
	movlw	KEYPRESS_BACK
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	bra		tm_back
	
	movlw	KEYPRESS_DOWN
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	bra		tm_down
	
	movlw	KEYPRESS_UP
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	bra		tm_up
	
	movlw	KEYPRESS_ACCENT
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	bra		tm_accent
	
	;# In den Normalmode wechseln
	movlw	KEYPRESS_FUNC
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	goto	mainloop_normalmode_start
	
tm_noevent

  	;# Hauptschleife von vorne beginnen
   	goto mainloop_timemode

;# nächste Position aus EEPROM laden	
tm_tap
	incf	PAT_POS, 1
	call	eereadpos_b
	;# Prüfen ob Pattern-Ende erreicht wurde
	incf	PAT_LEN, 1
	movf	PAT_LEN, w
	cpfslt	PAT_POS
	bra		tm_flashleds
	decf	PAT_LEN, 1
	bra		tm_noevent
	
;# letzte Position aus EEPROM laden	
tm_back
	tstfsz	PAT_POS
	decf	PAT_POS, 1
	call	eereadpos_b
	bra		tm_noevent

;# Kurz die LED`s aufflashen lassen und dann zurück in den Normal-Mode
tm_flashleds
	decf	PAT_LEN, 1
	movlw	255
	movwf	LED_REG_A
	movwf	LED_REG_B
	movwf	LED_REG_C
	movwf	LED_REG_D
	call	set_leds_timemode
	call	lpause
	call	lpause
	call	lpause
	call	lpause
	call	lpause
	call	lpause
	goto	mainloop_normalmode_start
	
tm_down
	bsf		PAT_MEM_B, 7
	bcf		PAT_MEM_B, 6
	bcf		PAT_MEM_B, 5
	call	eesavepos_b
	bra		tm_noevent

tm_up
	bcf		PAT_MEM_B, 7
	bsf		PAT_MEM_B, 6
	bcf		PAT_MEM_B, 5
	call	eesavepos_b
	bra		tm_noevent

tm_accent
	bcf		PAT_MEM_B, 7
	bcf		PAT_MEM_B, 6
	bsf		PAT_MEM_B, 5
	call	eesavepos_b
	bra		tm_noevent

tmp2patb
	movwf	TMP_W
	btfsc	PAT_MEM_B,7
	bsf		TMP_W, 7
	btfsc	PAT_MEM_B,6
	bsf		TMP_W, 6
	btfsc	PAT_MEM_B,5
	bsf		TMP_W, 5
	btfsc	PAT_MEM_B,4
	bsf		TMP_W, 4
	movff	TMP_W, PAT_MEM_B
	call	eesavepos_b
	bra		tm_noevent
	
