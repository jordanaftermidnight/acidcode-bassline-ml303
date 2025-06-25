	errorlevel -202, -207, -205

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
	goto 	start

	org 0x0004
	goto 	start
	
	org	0x0008 
	goto 	IRQ

start
	call	INIT
;	call	PAT_ENTER_NAME

start2
	goto	MODE_NORMAL
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
#include <macros.h>
#include <global.h>
#include <eeprom.inc>
#include <init.inc>
#include <timer1.inc>
#include <timer2.inc>
#include <bpm.inc>
#include <led.inc>
#include <key.inc>
#include <irq.inc>
#include <ports.inc>
#include <lcd.inc>
#include <pattern.inc>
#include <modenormal.inc>
#include <modepitch.inc>
#include <data.inc>

	END	
