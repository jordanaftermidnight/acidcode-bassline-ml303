;-------------------------------------------------------------
;# Pattern löschen
;-------------------------------------------------------------
pat_clear
	clrf	PAT_MEM_A
	clrf	PAT_MEM_B
	clrf	PAT_POS
pat_clear_loop	
	clrwdt
	btg		LED_REG_N2, LED_N2
	btg		LED_REG_N4, LED_N4
	btg		LED_REG_N7, LED_N7
	btg		LED_REG_N9, LED_N9
	btg		LED_REG_N11, LED_N11
	call	set_leds_edtmode

	call	eesavepos_a
	call	eesavepos_b
	incf	PAT_POS, 1
	;# Prüfen ob Pattern-Ende erreicht wurde
	movlw	16
	cpfseq	PAT_POS
	bra 	pat_clear_loop
	clrf	PAT_POS
	return	

;-------------------------------------------------------------
;# EEREADCFG - Config aus EEPROM lesen
;-------------------------------------------------------------

eereadcfg
	movlw	0x8C
	movwf	XEEL
	clrf	XEEH
	call	internaleeprom_load
	movff	XBYT, PAT_LEN
	bcf		PAT_LEN, 4
	bcf		PAT_LEN, 5
	bcf		PAT_LEN, 6
	bcf		PAT_LEN, 7
	movlw	0x8D
	movwf	XEEL
	clrf	XEEH
	call	internaleeprom_load
	movff	XBYT, PAT_BPM
	movlw	0x8E
	movwf	XEEL
	clrf	XEEH
	call	internaleeprom_load
	movff	XBYT, CFG
	movlw	0x8F
	movwf	XEEL
	clrf	XEEH
	call	internaleeprom_load
	movff	XBYT, MIDI_CHANNEL
	bcf		MIDI_CHANNEL, 7
	bcf		MIDI_CHANNEL, 6
	bcf		MIDI_CHANNEL, 5
	bcf		MIDI_CHANNEL, 4
	return

;-------------------------------------------------------------
;# EESAVECFG - Config in EEPROM schreiben
;-------------------------------------------------------------

eesavecfg
	movlw	0x8C
	movwf	XEEL
	clrf	XEEH
	bcf		PAT_LEN, 4
	bcf		PAT_LEN, 5
	bcf		PAT_LEN, 6
	bcf		PAT_LEN, 7
	movff	PAT_LEN, XBYT
	call	internaleeprom_save
	movlw	0x8D
	movwf	XEEL
	clrf	XEEH
	movff	PAT_BPM, XBYT
	call	internaleeprom_save
	movlw	0x8E
	movwf	XEEL
	clrf	XEEH
	movff	CFG, XBYT
	call	internaleeprom_save
	movlw	0x8F
	movwf	XEEL
	clrf	XEEH
	movff	MIDI_CHANNEL, XBYT
	call	internaleeprom_save
	return

internaleeprom_save
	movf	XEEL, w
	movwf	EEADR
	movf	XBYT, w
	movwf	EEDATA
	bcf		EECON1, EEPGD
	bcf		EECON1, CFGS
	bsf		EECON1, WREN
	bcf		INTCON, GIE
	movlw	0x55
	movwf	EECON2
	movlw	0xaa
	movwf	EECON2
	bsf		EECON1, WR
saveloop
	clrwdt
	btfsc	EECON1, WR
	bra		saveloop	
	bsf		INTCON, GIE
	bcf		EECON1, WREN
	return

internaleeprom_load
	movf	XEEL, w
	movwf	EEADR
	bcf		EECON1, EEPGD
	bcf		EECON1, CFGS
	bsf		EECON1, RD
	movf	EEDATA, w
	movwf	XBYT
	return

;-------------------------------------------------------------
;# EEREADPOS - Patternposition aus EEPROM lesen
;-------------------------------------------------------------

eereadpos_a
	;-- A --
	movf	PAT_POS, w
	movwf	XEEH
	movf	PAT_BANK, w
	movwf	XEEL
	call	eeprom_load
	movff	XBYT, PAT_MEM_A
	return

eereadpos_b
	;-- B --
	movf	PAT_POS, w
	addlw	0x10
	movwf	XEEH
	movf	PAT_BANK, w
	movwf	XEEL
	call	eeprom_load
	movff	XBYT, PAT_MEM_B
	return

;-------------------------------------------------------------
;# EESAVEPOS - Patternposition in EEPROM schreiben
;-------------------------------------------------------------

eesavepos_a
	;-- A --
	movf	PAT_POS, w
	movwf	XEEH
	movf	PAT_BANK, w
	movwf	XEEL
	movff	PAT_MEM_A, XBYT
	call	eeprom_save
	return

eesavepos_b
	;-- B --
	movf	PAT_POS, w
	addlw	0x10
	movwf	XEEH
	movf	PAT_BANK, w
	movwf	XEEL
	movff	PAT_MEM_B, XBYT
	call	eeprom_save
	return

;-------------------------------------------------------------
;# Pause
;-------------------------------------------------------------
pause
	clrf	DELAY_L

LDelay_Loop1
	clrwdt
	decfsz	DELAY_L, F
	bra		LDelay_Loop1
	return
	
lpause
	clrf	DELAY_L
	clrf	DELAY_H

LLDelay_Loop1
	clrwdt
	decfsz	DELAY_L, F
	bra		LLDelay_Loop1
	decfsz	DELAY_H, F
	bra		LLDelay_Loop1
	return
	
;-------------------------------------------------------------
;# LED`s löschen
;-------------------------------------------------------------
clr_leds
	clrf	LED_REG_A
	clrf	LED_REG_B
	clrf	LED_REG_C
	clrf	LED_REG_D
	return

;-------------------------------------------------------------
;# LED`s ausgeben
;-------------------------------------------------------------
set_leds_edtmode
set_leds_bpmmode
set_leds_sysmode
set_leds_pitchmode
	clrf	DATABUS_STROBE
	movff	LED_REG_A, DATABUS
	bsf		DATABUS_STROBE, DATABUS_A_STROBE
	clrf	DATABUS_STROBE
	movff	LED_REG_B, DATABUS
	bsf		DATABUS_STROBE, DATABUS_B_STROBE
	clrf	DATABUS_STROBE
	movff	LED_REG_C, DATABUS
	bsf		DATABUS_STROBE, DATABUS_C_STROBE
	clrf	DATABUS_STROBE
	movff	LED_REG_D, DATABUS
	bsf		DATABUS_STROBE, DATABUS_D_STROBE
	return

set_leds_timemode
	clrf	DATABUS_STROBE
	movff	LED_REG_A, DATABUS
	bsf		DATABUS_STROBE, DATABUS_A_STROBE
	clrf	DATABUS_STROBE
	movff	LED_REG_B, DATABUS
	bsf		DATABUS_STROBE, DATABUS_B_STROBE
	clrf	DATABUS_STROBE
	movff	LED_REG_C, DATABUS
	bcf		DATABUS, LED_DOWN
	bcf		DATABUS, LED_UP
	btfsc	LED_REG_BLACK, LED_BLACK
	bsf		DATABUS, LED_DOWN
	btfsc	LED_REG_WHITE, LED_WHITE
	bsf		DATABUS, LED_UP
	bsf		DATABUS_STROBE, DATABUS_C_STROBE
	clrf	DATABUS_STROBE
	movff	LED_REG_D, DATABUS
	bcf		DATABUS, LED_ACCENT
	btfsc	LED_REG_PAUSE, LED_PAUSE
	bsf		DATABUS, LED_ACCENT
	bsf		DATABUS_STROBE, DATABUS_D_STROBE
	return

set_leds_normalmode
	incf	LED_BLINKER, 1
	clrf	DATABUS_STROBE
	movff	LED_REG_A, DATABUS
	btfsc	LED_BLINKER, 7 
	call	blinker_a
	bsf		DATABUS_STROBE, DATABUS_A_STROBE
	clrf	DATABUS_STROBE
	movff	LED_REG_B, DATABUS
	btfsc	LED_BLINKER, 7 
	call	blinker_b
	bsf		DATABUS_STROBE, DATABUS_B_STROBE
	clrf	DATABUS_STROBE
	movff	LED_REG_C, DATABUS
	btfsc	LED_BLINKER, 7 
	call	blinker_c
	bsf		DATABUS_STROBE, DATABUS_C_STROBE
	clrf	DATABUS_STROBE
	movff	LED_REG_D, DATABUS
	bsf		DATABUS_STROBE, DATABUS_D_STROBE
	return

blinker_a
	bcf		DATABUS, LED_N1
	bcf		DATABUS, LED_N3
	return
	
blinker_b
	bcf		DATABUS, LED_N5
	bcf		DATABUS, LED_N6
	bcf		DATABUS, LED_N8
	return
	
blinker_c
	bcf		DATABUS, LED_N10
	bcf		DATABUS, LED_N12
	bcf		DATABUS, LED_N13
	return
	
set_leds_run
	incf	LED_BLINKER, 1
	clrf	DATABUS_STROBE
	movff	LED_REG_A, DATABUS
	btfsc	LED_BLINKER, 7 
	call	blinker_aa
	bsf		DATABUS_STROBE, DATABUS_A_STROBE
	clrf	DATABUS_STROBE
	movff	LED_REG_B, DATABUS
	bsf		DATABUS_STROBE, DATABUS_B_STROBE
	clrf	DATABUS_STROBE
	movff	LED_REG_C, DATABUS
	bsf		DATABUS_STROBE, DATABUS_C_STROBE
	clrf	DATABUS_STROBE
	movff	LED_REG_D, DATABUS
	bsf		DATABUS_STROBE, DATABUS_D_STROBE
	return

blinker_aa
	bcf		DATABUS, LED_RUN
	return
	
;-------------------------------------------------------------
;# Tastatur lesen
;-------------------------------------------------------------
get_keyboard

	;# Tastatur einlesen
	call 	get_keybus
	
	;# Gleiche Taste wie beim letzten Durchlauf?
	movf	LAST_KEYPRESS, W
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
  	goto end_prc_keyboard
		
	;# Taste speichern	
	movf	KEYPRESS, W
	movwf	LAST_KEYPRESS
	
	;# Event setzen
	bsf		EVENT, EVENT_KEYPRESS
  	
end_prc_keyboard
	return

get_keybus
	clrwdt
	
	movlw	KEYPRESS_NONE

	clrf	KEYBUS_STROBE
	bsf		KEYBUS_STROBE, KEYBUS_A_STROBE
	call	get_keyboard_scandelay
	btfsc	KEYBUS, 0
	movlw	KEYPRESS_N4
	btfsc	KEYBUS, 1
	movlw	KEYPRESS_N12
	btfsc	KEYBUS, 2
	movlw	KEYPRESS_TAP

	clrf	KEYBUS_STROBE
	bsf		KEYBUS_STROBE, KEYBUS_B_STROBE
	call	get_keyboard_scandelay
	btfsc	KEYBUS, 0
	movlw	KEYPRESS_N3
	btfsc	KEYBUS, 1
	movlw	KEYPRESS_N11
	btfsc	KEYBUS, 2
	movlw	KEYPRESS_BACK

	clrf	KEYBUS_STROBE
	bsf		KEYBUS_STROBE, KEYBUS_C_STROBE
	call	get_keyboard_scandelay
	btfsc	KEYBUS, 0
	movlw	KEYPRESS_N2
	btfsc	KEYBUS, 1
	movlw	KEYPRESS_N10
	btfsc	KEYBUS, 2
	movlw	KEYPRESS_TIME

	clrf	KEYBUS_STROBE
	bsf		KEYBUS_STROBE, KEYBUS_D_STROBE
	call	get_keyboard_scandelay
	btfsc	KEYBUS, 0
	movlw	KEYPRESS_N1
	btfsc	KEYBUS, 1
	movlw	KEYPRESS_N9
	btfsc	KEYBUS, 2
	movlw	KEYPRESS_SLIDE

	clrf	KEYBUS_STROBE
	bsf		KEYBUS_STROBE, KEYBUS_E_STROBE
	call	get_keyboard_scandelay
	btfsc	KEYBUS, 0
	movlw	KEYPRESS_FUNC
	btfsc	KEYBUS, 1
	movlw	KEYPRESS_N8
	btfsc	KEYBUS, 2
	movlw	KEYPRESS_ACCENT

	clrf	KEYBUS_STROBE
	bsf		KEYBUS_STROBE, KEYBUS_F_STROBE
	call	get_keyboard_scandelay
	btfsc	KEYBUS, 0
	movlw	KEYPRESS_PITCH
	btfsc	KEYBUS, 1
	movlw	KEYPRESS_N7
	btfsc	KEYBUS, 2
	movlw	KEYPRESS_UP

	clrf	KEYBUS_STROBE
	bsf		KEYBUS_STROBE, KEYBUS_G_STROBE
	call	get_keyboard_scandelay
	btfsc	KEYBUS, 0
	movlw	KEYPRESS_RUN
	btfsc	KEYBUS, 1
	movlw	KEYPRESS_N6
	btfsc	KEYBUS, 2
	movlw	KEYPRESS_DOWN

	clrf	KEYBUS_STROBE
	bsf		KEYBUS_STROBE, KEYBUS_H_STROBE
	call	get_keyboard_scandelay
	btfsc	KEYBUS, 0
	movlw	KEYPRESS_CLR
	btfsc	KEYBUS, 1
	movlw	KEYPRESS_N5
	btfsc	KEYBUS, 2
	movlw	KEYPRESS_N13
	
	movwf	KEYPRESS
	
	return

get_keyboard_scandelay
	call pause
	return
	
;-------------------------------------------------------------
;# Midi Out
;-------------------------------------------------------------
usart_out
	clrwdt
    btfss   PIR1,TXIF      
    bra    	usart_out
    movff  	MIDI_OUTBYTE, TXREG          
	return
	
;-------------------------------------------------------------
;# Midi Program Change
;-------------------------------------------------------------
midiout_programchange
	btfss	CFG, CFG_S_PGM
	bra		nmp
	movlw	192
	movwf	MIDI_OUTBYTE
	movf	MIDI_CHANNEL, w
	addwf	MIDI_OUTBYTE, w
	movwf	MIDI_OUTBYTE
	call	usart_out
	movff	PAT_BANK, MIDI_OUTBYTE
	bcf		MIDI_OUTBYTE, 7
	bcf		MIDI_OUTBYTE, 6
	bcf		MIDI_OUTBYTE, 5
	bcf		MIDI_OUTBYTE, 4
	call	usart_out
nmp	
	return	


;-------------------------------------------------------------
;# Midi Bank Change
;-------------------------------------------------------------
midiout_bankchange
	btfss	CFG, CFG_S_PGM
	bra		nmb
	; Controller Change
	movlw	176
	movwf	MIDI_OUTBYTE
	movf	MIDI_CHANNEL, w
	addwf	MIDI_OUTBYTE, w
	movwf	MIDI_OUTBYTE
	call	usart_out
	movlw	0x20
	movwf	MIDI_OUTBYTE
	call	usart_out
	clrf	MIDI_OUTBYTE
	btfsc	PAT_BANK, 4
	bsf 	MIDI_OUTBYTE,0
	btfsc	PAT_BANK, 5
	bsf 	MIDI_OUTBYTE,1
	btfsc	PAT_BANK, 6
	bsf 	MIDI_OUTBYTE,2
	btfsc	PAT_BANK, 7
	bsf 	MIDI_OUTBYTE,3
	call	usart_out
nmb
	return

;-------------------------------------------------------------
;# Midi
;-------------------------------------------------------------
check_midi

	call	check_sndmode

	;# Wenn nicht im FUNC-Mode dann keinen Empfang zulassen
	btfss	LED_REG_FUNC, LED_FUNC
	bra		nmcm

	;# Program Change ?
	movlw	0xC0
	movwf	TMP_I
	movf	MIDI_CHANNEL, w
	addwf	TMP_I, w
  	xorwf 	MIDI_CMD1,W
  	btfsc 	STATUS,Z
	bra		mid_pgm_chg

	;# Controller Change ?
	movlw	0xB0
	movwf	TMP_I
	movf	MIDI_CHANNEL, w
	addwf	TMP_I, w
  	xorwf 	MIDI_CMD1,W
  	btfsc 	STATUS,Z
	bra		mid_ctrl_chg

nmcm
	return

;# Controller Change
mid_ctrl_chg
		
	;# Bank Change Controller		
	movlw	0x20
  	xorwf 	MIDI_CMD2,W
  	btfsc 	STATUS,Z
	bra		mid_bnk_chg
	return

;# Programm Change empfangen	
mid_pgm_chg

	btfss	CFG, CFG_R_PGM
	bra		nmpc
	
	movff	MIDI_CMD3, TMP_I
	bcf		TMP_I, 7
	bcf		TMP_I, 6
	bcf		TMP_I, 5
	bcf		TMP_I, 4

	btfsc	PAT_BANK, 7
	bsf		TMP_I, 7
	btfsc	PAT_BANK, 6
	bsf		TMP_I, 6
	btfsc	PAT_BANK, 5
	bsf		TMP_I, 5
	btfsc	PAT_BANK, 4
	bsf		TMP_I, 4
	movff	TMP_I, PAT_BANK
nmpc
	return	
	
;# Bank Change empfangen	
mid_bnk_chg

	btfss	CFG, CFG_R_PGM
	bra		nmbc

	bcf		PAT_BANK, 7
	bcf		PAT_BANK, 6
	bcf		PAT_BANK, 5
	bcf		PAT_BANK, 4

	btfsc	MIDI_CMD3, 0
	bsf		PAT_BANK, 4
	
	btfsc	MIDI_CMD3, 1
	bsf		PAT_BANK, 5
	
	btfsc	MIDI_CMD3, 2
	bsf		PAT_BANK, 6
	
	btfsc	MIDI_CMD3, 3
	bsf		PAT_BANK, 7
nmbc
	return	
	
	
;-------------------------------------------------------------
;# Midi Out "TICK"
;-------------------------------------------------------------
send_tick

	btfss 	CFG, CFG_S_SYNC
	bra		notick

	;# Tick
	movlw	248
	movwf	MIDI_OUTBYTE
  	call	usart_out

	call	inctick

	call	play_tick
	
notick	
	return
	
inctick
  	incf	TICK, 1
  	
	movlw	0x06
  	xorwf 	TICK,W
  	btfsc 	STATUS,Z
	call	resettick
	return
		
resettick
	clrf	TICK
	return	

;-------------------------------------------------------------
;# Midi Out "START"
;-------------------------------------------------------------
send_start

	btfss 	CFG, CFG_S_SYNC
	bra		nostart

	;# Start
	movlw	250
	movwf	MIDI_OUTBYTE
  	call	usart_out
nostart	
	return

;-------------------------------------------------------------
;# Midi Out "STOP"
;-------------------------------------------------------------
send_stop

	btfss 	CFG, CFG_S_SYNC
	bra		nostop
	;# Stop
	movlw	252
	movwf	MIDI_OUTBYTE
  	call	usart_out
nostop	
	return

;#---------------------------------------------------------------
;# Midi SSC verarbeiten
;#---------------------------------------------------------------
peek_ssc

	;# Tick
	movlw	248
  	xorwf 	MIDI_BYTE,W
  	btfsc 	STATUS,Z
	bra		midi_tick

	;# Start
	movlw	250
  	xorwf 	MIDI_BYTE,W
  	btfsc 	STATUS,Z
	bra		midi_start

	;# Continue
	movlw	251
  	xorwf 	MIDI_BYTE,W
  	btfsc 	STATUS,Z
	bra		midi_cont

	;# Stop
	movlw	252
  	xorwf 	MIDI_BYTE,W
  	btfsc 	STATUS,Z
	bra		midi_stop

midi_goback	
	return
	
midi_tick
	call	inctick
	call	play_tick
	bra		midi_goback	

midi_start
	clrf	PAT_POS
	clrf	TICK
	bsf		RUN, 0
	bra		midi_goback	

midi_cont
	clrf	TICK
	bsf		RUN, 0
	bra		midi_goback	

midi_stop
	clrf	PAT_POS
	clrf	TICK
	bcf		RUN, 0
	call	clr_gate
	bra		midi_goback	

;-------------------------------------------------------------
;# SNDMODE
;-------------------------------------------------------------
check_sndmode

	;# Wenn nicht im SND-Mode dann keinen Empfang zulassen
	btfss	SNDMODE, 0
	bra		nomidi

	;# Note On?
	movlw	0x90
	movwf	TMP_W3
	movf	MIDI_CHANNEL, w
	addwf	TMP_W3, w
  	xorwf 	MIDI_CMD1,W
  	btfsc 	STATUS,Z
	call	play_midi 
	
	;# Note Off?
	movlw	0x80
	movwf	TMP_W3
	movf	MIDI_CHANNEL, w
	addwf	TMP_W3, w
  	xorwf 	MIDI_CMD1,W
  	btfsc 	STATUS,Z
	call	play_midi_off 
	
	;# Event löschen
  	bsf		MIDI_CMD3,7

nomidi
	return

play_midi

	;# Velocity > 0 -> Note On
	movlw	0x00
  	xorwf 	MIDI_CMD3,W
  	btfss 	STATUS,Z
	call	play_midi_on 

	;# Velocity = 0 -> Note Off
	movlw	0x00
  	xorwf 	MIDI_CMD3,W
  	btfsc 	STATUS,Z
	call	play_midi_off 
	return

play_midi_on

  	clrf	DATABUS_STROBE

  	;# Accent?
	movf 	MIDI_CMD3,W
	bcf 	STATUS,C
	sublw 	b'01100100'
	btfss 	STATUS,C
	goto 	seta
	call	clr_accent

rseta
  	;# Strobe löschen
	call	clr_slide
	
	;# VCO ausgeben
	bcf		DATABUS_STROBE, DATABUS_E_STROBE
	movff	MIDI_CMD2, TMP_W
	call	inc_23
	movff	TMP_W, DATABUS
	bsf		DATABUS_STROBE, DATABUS_E_STROBE
	;# Noten-LED`s setzen
 ;	call	clr_leds
 ;	movff	MIDI_CMD2, TMP_W
 ;	bcf		TMP_W, 7
 ;	bcf		TMP_W, 6
 ;	bcf		TMP_W, 5
 ;	bcf		TMP_W, 4

;	movlw	0
 ; 	xorwf 	TMP_W,W
;  	btfsc 	STATUS,Z
;	bsf		LED_REG_N1, LED_N1
;	movlw	1
 ; 	xorwf 	TMP_W,W
  ;	btfsc 	STATUS,Z
;	bsf		LED_REG_N2, LED_N2
;	movlw	2
 ; 	xorwf 	TMP_W,W
  ;	btfsc 	STATUS,Z
;	bsf		LED_REG_N3, LED_N3
;	movlw	3
 ; 	xorwf 	TMP_W,W
  ;	btfsc 	STATUS,Z
;	bsf		LED_REG_N4, LED_N4
;	movlw	4
 ; 	xorwf 	TMP_W,W
 ; 	btfsc 	STATUS,Z
 ;	bsf		LED_REG_N5, LED_N5
 ;	movlw	5
 ;	xorwf 	TMP_W,W
   ;	btfsc 	STATUS,Z
 ;	bsf		LED_REG_N6, LED_N6
 ;	movlw	6
 ;  	xorwf 	TMP_W,W
 ;  	btfsc 	STATUS,Z
 ;	bsf		LED_REG_N7, LED_N7
 ;	movlw	7
 ;  	xorwf 	TMP_W,W
 ;  	btfsc 	STATUS,Z
 ;	bsf		LED_REG_N8, LED_N8
 ;	movlw	8
 ;  	xorwf 	TMP_W,W
 ;  	btfsc 	STATUS,Z
 ;	bsf		LED_REG_N9, LED_N9
 ;	movlw	9
 ;  	xorwf 	TMP_W,W
 ;  	btfsc 	STATUS,Z
 ;	bsf		LED_REG_N10, LED_N10
 ;	movlw	10
 ;  	xorwf 	TMP_W,W
 ;  	btfsc 	STATUS,Z
 ;	bsf		LED_REG_N11, LED_N11
 ;	movlw	11
 ;  	xorwf 	TMP_W,W
 ;  	btfsc 	STATUS,Z
 ;	bsf		LED_REG_N12, LED_N12
 ;	movlw	12
 ;  	xorwf 	TMP_W,W
 ;  	btfsc 	STATUS,Z
 ;	bsf		LED_REG_N13, LED_N13
	
	call	set_slide
	
	;# Slide nur dann löschen wenn Gate aus ist
	btfss	GATEBUS_TMP, GATEBUS_GATE
	call	clr_slide

	;# Accent löschen	
	call	clr_accent

  	;# Note auf VCO ausgeben, wenn im Bereich
  	btfsc	MIDI_CMD2, 7
  	bra		nonoteplay
  	btfsc	MIDI_CMD2, 6
  	bra		nonoteplay
	call	set_gate

nonoteplay
	return

play_midi_off
  	;# Note Off
	call	clr_gate
	return

seta
	call	set_accent
	goto rseta

intro
	call	clr_leds
	bsf		LED_REG_RUN, LED_RUN
	call 	set_leds_edtmode
	call	intropause
	bsf		LED_REG_FUNC, LED_FUNC
	call 	set_leds_edtmode
	call	intropause
	bsf		LED_REG_PITCH, LED_PITCH
	call 	set_leds_edtmode
	call	intropause
	bsf		LED_REG_N1, LED_N1
	call 	set_leds_edtmode
	call	intropause
	bsf		LED_REG_N2, LED_N2
	call 	set_leds_edtmode
	call	intropause
	bsf		LED_REG_N3, LED_N3
	call 	set_leds_edtmode
	call	intropause
	bsf		LED_REG_N4, LED_N4
	call 	set_leds_edtmode
	call	intropause
	bsf		LED_REG_N5, LED_N5
	call 	set_leds_edtmode
	call	intropause
	bsf		LED_REG_N6, LED_N6
	call 	set_leds_edtmode
	call	intropause
	bsf		LED_REG_N7, LED_N7
	call 	set_leds_edtmode
	call	intropause
	bsf		LED_REG_N8, LED_N8
	call 	set_leds_edtmode
	call	intropause
	bsf		LED_REG_N9, LED_N9
	call 	set_leds_edtmode
	call	intropause
	bsf		LED_REG_N10, LED_N10
	call 	set_leds_edtmode
	call	intropause
	bsf		LED_REG_N11, LED_N11
	call 	set_leds_edtmode
	call	intropause
	bsf		LED_REG_N12, LED_N12
	call 	set_leds_edtmode
	call	intropause
	bsf		LED_REG_N13, LED_N13
	call 	set_leds_edtmode
	call	intropause
	bsf		LED_REG_DOWN, LED_DOWN
	call 	set_leds_edtmode
	call	intropause
	bsf		LED_REG_UP, LED_UP
	call 	set_leds_edtmode
	call	intropause
	bsf		LED_REG_ACCENT, LED_ACCENT
	call 	set_leds_edtmode
	call	intropause
	bsf		LED_REG_SLIDE, LED_SLIDE
	call 	set_leds_edtmode
	call	intropause
	bsf		LED_REG_TIME, LED_TIME
	call 	set_leds_edtmode
	call	intropause
	bsf		LED_REG_SLIDE, LED_SLIDE
	call 	set_leds_edtmode
	call	intropause
	bsf		LED_REG_ACCENT, LED_ACCENT
	call 	set_leds_edtmode
	call	intropause
	bsf		LED_REG_UP, LED_UP
	call 	set_leds_edtmode
	call	intropause
	bsf		LED_REG_DOWN, LED_DOWN
	call 	set_leds_edtmode
	call	intropause
	bsf		LED_REG_N13, LED_N13
	call 	set_leds_edtmode
	call	intropause
	bsf		LED_REG_N12, LED_N12
	call 	set_leds_edtmode
	call	intropause
	bsf		LED_REG_N11, LED_N11
	call 	set_leds_edtmode
	call	intropause
	bsf		LED_REG_N10, LED_N10
	call 	set_leds_edtmode
	call	intropause
	bsf		LED_REG_N9, LED_N9
	call 	set_leds_edtmode
	call	intropause
	bsf		LED_REG_N8, LED_N8
	call 	set_leds_edtmode
	call	intropause
	bsf		LED_REG_N7, LED_N7
	call 	set_leds_edtmode
	call	intropause
	bsf		LED_REG_N6, LED_N6
	call 	set_leds_edtmode
	call	intropause
	bsf		LED_REG_N5, LED_N5
	call 	set_leds_edtmode
	call	intropause
	bsf		LED_REG_N4, LED_N4
	call 	set_leds_edtmode
	call	intropause
	bsf		LED_REG_N3, LED_N3
	call 	set_leds_edtmode
	call	intropause
	bsf		LED_REG_N2, LED_N2
	call 	set_leds_edtmode
	call	intropause
	bsf		LED_REG_N1, LED_N1
	call 	set_leds_edtmode
	call	intropause
	bsf		LED_REG_PITCH, LED_PITCH
	call 	set_leds_edtmode
	call	intropause
	bsf		LED_REG_FUNC, LED_FUNC
	call 	set_leds_edtmode
	call	intropause
	bsf		LED_REG_RUN, LED_RUN
	call 	set_leds_edtmode
	call	intropause
	call	clr_leds
	call 	set_leds_edtmode
	return
	
intropause
	call	clr_leds
	call	lpause	
	return
