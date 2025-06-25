mainloop_sndmode_start

	call	init2

	bsf		SNDMODE, 0
	bcf		CFG, CFG_S_SYNC
	bcf		CFG, CFG_S_MIDI

mainloop_sndmode
	
  	;# Watchdog-Timer löschen
  	clrwdt
  	
	;# Alle LED`s löschen
	call	clr_leds
	
	bsf		LED_REG_RUN, LED_RUN
	
	;# LED`s ausgeben
	call	set_leds_run
	
	call	pause
	call	pause
	call	pause
	call	pause
	call	pause
	call	pause
	call	pause
	call	pause
	call	pause
	call	pause
	call	pause
	call	pause
	call	pause
	call	pause
	call	pause
	call	pause
	
	;# Loop
	bra		mainloop_sndmode
	
	return
