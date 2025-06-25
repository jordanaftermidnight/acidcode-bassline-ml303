mainloop_normalmode_default

  	clrf    PIE2 
  	clrf    PIE1
  	  	
	clrf	MIDI_CHANNEL
	bsf		CFG, CFG_S_SYNC
	bsf		CFG, CFG_S_PGM
	bcf		CFG, CFG_S_MIDI
	
	;# EEPROM formatieren
	clrf	PAT_BANK
mainloop_normalmode_clrloop	
	clrwdt
;	call	clr_leds
	btfsc	PAT_BANK,0
	bsf		LED_REG_N1, LED_N1
	btfsc	PAT_BANK,1
	bsf		LED_REG_N3, LED_N3
	btfsc	PAT_BANK,2
	bsf		LED_REG_N5, LED_N5
	btfsc	PAT_BANK,3
	bsf		LED_REG_N6, LED_N6
	btfsc	PAT_BANK,4
	bsf		LED_REG_N8, LED_N8
	btfsc	PAT_BANK,5
	bsf		LED_REG_N10, LED_N10
	btfsc	PAT_BANK,6
	bsf		LED_REG_N12, LED_N12
	btfsc	PAT_BANK,7
	bsf		LED_REG_N13, LED_N13
;	call	set_leds_edtmode
	call	pat_clear
;	call	lpause
	
	incfsz	PAT_BANK, 1
	bra		mainloop_normalmode_clrloop	
	
	call	pat_clear
	clrf	PAT_BANK

	movlw	0x0F
	movwf	PAT_LEN
	movlw	125
	movwf	PAT_BPM
	call	eesavecfg
	
killloop
	goto killloop

mainloop_normalmode_start

	bcf		SNDMODE, 0
	bcf		RUN, 0
	bcf		LED_REG_RUN, LED_RUN

mainloop_normalmode
	
  	;# Watchdog-Timer löschen
  	clrwdt
  	
	;# Alle LED`s löschen
	call	clr_leds
	
	;# RUN
	btfsc	RUN, 0
	bsf		LED_REG_RUN, LED_RUN
	
	;# FUNC-LED setzen
	bsf		LED_REG_FUNC, LED_FUNC
	
	;# N2-LED setzen (Normal-Mode)
	bsf		LED_REG_N2, LED_N2

	;# Pattern-Bank obere Bits darstellen
	btfsc	PAT_BANK, 7
	bsf		LED_REG_DOWN, LED_DOWN
	btfsc	PAT_BANK, 6
	bsf		LED_REG_UP, LED_UP
	btfsc	PAT_BANK, 5
	bsf		LED_REG_ACCENT, LED_ACCENT
	btfsc	PAT_BANK, 4
	bsf		LED_REG_SLIDE, LED_SLIDE

	;# Pattern 1-8 extrahieren
	movff	PAT_BANK, TMP_W
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
	bsf		LED_REG_N3, LED_N3
	movlw	2
  	xorwf 	TMP_W,W
  	btfsc 	STATUS,Z
	bsf		LED_REG_N5, LED_N5
	movlw	3
  	xorwf 	TMP_W,W
  	btfsc 	STATUS,Z
	bsf		LED_REG_N6, LED_N6
	movlw	4
  	xorwf 	TMP_W,W
  	btfsc 	STATUS,Z
	bsf		LED_REG_N8, LED_N8
	movlw	5
  	xorwf 	TMP_W,W
  	btfsc 	STATUS,Z
	bsf		LED_REG_N10, LED_N10
	movlw	6
  	xorwf 	TMP_W,W
  	btfsc 	STATUS,Z
	bsf		LED_REG_N12, LED_N12
	movlw	7
  	xorwf 	TMP_W,W
  	btfsc 	STATUS,Z
	bsf		LED_REG_N13, LED_N13

	;# LED`s ausgeben
	call	set_leds_normalmode

	;# Tastatur einlesen
	call	get_keyboard
	
	;# Keyboard-Event?
	btfss	EVENT, EVENT_KEYPRESS
	bra		nm_noevent
	
	;# Event löschen
	bcf		EVENT, EVENT_KEYPRESS
	
	;# Pattern-Bank obere Bits abfragen
	movlw	KEYPRESS_DOWN
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	bra		nm_setb_7
	movlw	KEYPRESS_UP
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	bra		nm_setb_6
	movlw	KEYPRESS_ACCENT
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	bra		nm_setb_5
	movlw	KEYPRESS_SLIDE
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	bra		nm_setb_4
	
	;# Pattern-Bank untere Bits abfragen
	movlw	KEYPRESS_N1
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	bra		nm_set_0
	movlw	KEYPRESS_N3
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	bra		nm_set_1
	movlw	KEYPRESS_N5
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	bra		nm_set_2
	movlw	KEYPRESS_N6
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	bra		nm_set_3
	movlw	KEYPRESS_N8
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	bra		nm_set_4
	movlw	KEYPRESS_N10
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	bra		nm_set_5
	movlw	KEYPRESS_N12
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	bra		nm_set_6
	movlw	KEYPRESS_N13
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	bra		nm_set_7
	
	;# RUN
	movlw	KEYPRESS_RUN
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
  	call	gorun

	;# alle anderen Tasten gesperrt wenn RUN
	btfsc	RUN, 0
	bra		nm_noevent
	
	;# CLR ?
	movlw	KEYPRESS_CLR
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	bra		nm_clr

	;# In den Pitchmode wechseln
	movlw	KEYPRESS_PITCH
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	goto	mainloop_pitchmode_start
	
	;# In den Timemode wechseln
	movlw	KEYPRESS_TIME
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	goto	mainloop_timemode_start
	
	;# In den EDT-Mode wechseln
	movlw	KEYPRESS_N4
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	goto	mainloop_edtmode_start
	
	;# In den BPM-Mode wechseln
	movlw	KEYPRESS_N7
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	goto	mainloop_bpmmode_start
	
	;# In den MID-Mode wechseln
	movlw	KEYPRESS_N9
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	goto	mainloop_midmode_start
	
	;# In den SYS-Mode wechseln
	movlw	KEYPRESS_N11
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	goto	mainloop_sysmode_start
	
nm_noevent

  	;# Hauptschleife von vorne beginnen
   	goto mainloop_normalmode

;# Pattern neu setzen
nm_set_0
	movlw	0
	movwf	TMP_W
	bra		nm_set_midiout
nm_set_1
	movlw	1
	movwf	TMP_W
	bra		nm_set_midiout
nm_set_2
	movlw	2
	movwf	TMP_W
	bra		nm_set_midiout
nm_set_3
	movlw	3
	movwf	TMP_W
	bra		nm_set_midiout
nm_set_4
	movlw	4
	movwf	TMP_W
	bra		nm_set_midiout
nm_set_5
	movlw	5
	movwf	TMP_W
	bra		nm_set_midiout
nm_set_6
	movlw	6
	movwf	TMP_W
	bra		nm_set_midiout
nm_set_7
	movlw	7
	movwf	TMP_W
	bra		nm_set_midiout
;# Patch-Change
nm_set_midiout
	btfsc	PAT_BANK, 7
	bsf		TMP_W, 7
	btfsc	PAT_BANK, 6
	bsf		TMP_W, 6
	btfsc	PAT_BANK, 5
	bsf		TMP_W, 5
	btfsc	PAT_BANK, 4
	bsf		TMP_W, 4
	movff	TMP_W, PAT_BANK
	call	midiout_programchange
	bra		nm_noevent

;# Bank-Change
nm_setb_7
	btg		PAT_BANK, 7
	bra		nm_setb_midiout
nm_setb_6
	btg		PAT_BANK, 6
	bra		nm_setb_midiout
nm_setb_5
	btg		PAT_BANK, 5
	bra		nm_setb_midiout
nm_setb_4
	btg		PAT_BANK, 4
	bra		nm_setb_midiout
nm_setb_midiout
	call	midiout_bankchange
	bra		nm_noevent

nm_clr
	
	;# Wenn RUN dann nicht!
	btfsc	LED_REG_RUN, LED_RUN		
	bra		nm_noevent
	
	;# warten ob die Taste lange gedrückt wurde!
	movlw	50
	movwf	TMP_W2
	movlw	10
	movwf	TMP_W3
wait_taplong
	clrwdt	
	decfsz	TMP_W2 ,1
 	bra 	wait_taplong2
	movlw	200
	movwf	TMP_W2
	decfsz	TMP_W3 ,1
 	bra 	wait_taplong2
	movlw	255
	movwf	DATABUS
	clrf	DATABUS_STROBE
	call	lpause
	bsf		DATABUS_STROBE, DATABUS_A_STROBE
	bsf		DATABUS_STROBE, DATABUS_B_STROBE
	bsf		DATABUS_STROBE, DATABUS_C_STROBE
	bsf		DATABUS_STROBE, DATABUS_D_STROBE
 	call	pat_clear
	;# LED`s ausgeben
	call	set_leds_normalmode
	bra		wtex
wait_taplong2	
  	call	get_keyboard
	movlw	KEYPRESS_NONE
 	xorwf 	KEYPRESS ,W
  	btfss 	STATUS,Z
  	bra 	wait_taplong
wtex
	bra		nm_noevent

gorun
	;# RUN darf man nur drücken wenn man im MASTER Modus ist!
	btfss	CFG, CFG_S_SYNC
	bra		nogorun

	;# Start/Stopp erst beim loslassen der Taste RUN
wait_gorun_release	
;  	call	get_keyboard
;	movlw	KEYPRESS_NONE
 ;	xorwf 	KEYPRESS ,W
  ;	btfss 	STATUS,Z
;  	bra 	wait_gorun_release

	clrf	PAT_POS
	clrf	TICK
	btg		RUN, 0
	call	clr_gate
	btfsc	RUN, 0
	call	send_start
	btfss	RUN, 0
	call	send_stop
nogorun
	return
