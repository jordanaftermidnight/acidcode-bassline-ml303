	errorlevel -202

;; ==========================================================================
;;  Assembler & PICstart directives
;; ==========================================================================

	LIST P=PIC18F452, R=DEC
#include <p18f452.inc>

;#---------------------------------------------------------------
;# BEGIN
;#---------------------------------------------------------------
BEGIN

	org 0x0000
	goto start

	org 0x0004
	goto start
	
	org	0x0008 
	goto IRQ

#include <bpm_table.inc>

;#---------------------------------------------------------------
;# Variablen
;#---------------------------------------------------------------
#include <variables.inc>

;#---------------------------------------------------------------
;# IRQ
;#---------------------------------------------------------------
#include <irq.inc>

;#---------------------------------------------------------------
;# Functions
;#---------------------------------------------------------------
#include <functions.inc>

;#---------------------------------------------------------------
;# I2C
;#---------------------------------------------------------------
#include <i2c.inc>

;#---------------------------------------------------------------
;# INIT
;#---------------------------------------------------------------
#include <init.inc>

;#---------------------------------------------------------------
;# START
;#---------------------------------------------------------------
start

	;# Initalisieren
	call	init

	;# Tastatur einlesen
	call	get_keyboard
	
	;# Keyboard-Event?
	btfss	EVENT, EVENT_KEYPRESS
	bra		start_noevent
	
	;# Event löschen
	bcf		EVENT, EVENT_KEYPRESS

	movlw	KEYPRESS_RUN
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	goto	mainloop_sndmode_start

	movlw	KEYPRESS_TIME
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
	goto	mainloop_normalmode_default

start_noevent	
	;# in die Hauptschleife (Normalmode) springen
	call	intro
	call	init2
	goto	mainloop_normalmode_start

;#---------------------------------------------------------------
;# MAINLOOP NORMALMODE
;#---------------------------------------------------------------
#include <normalmode.inc>
#include <pitchmode.inc>
#include <timemode.inc>
#include <midmode.inc>
#include <sysmode.inc>
#include <bpmmode.inc>
#include <edtmode.inc>
#include <sndmode.inc>
#include <play.inc>

	END	
