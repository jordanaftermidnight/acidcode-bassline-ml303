INIT

	;# Beat 24 Divider
	movlw	23
	movwf	BPM_BEAT24

	;# Ports Init
	call PORTS_INIT

	;# LED Init
	call LED_INIT

	;# KEY Init
	call KEY_INIT

	;# LCD Init
	call LCD_INIT

	;# BPM Init
	call BPM_INIT

	;# EEPROM Init
	call EE_INIT

	;# Timer0 Init
	;call TIMER0_INIT

	;# Timer1 Init
	call TIMER1_INIT

	;# Timer2 Init
	call TIMER2_INIT

	;# IRQ Init
	call IRQ_INIT

	;# Pattern Init
	call PAT_INIT

	return
