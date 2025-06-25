MODE_PITCH

	;# LED`s löschen
	call	CLR_LEDS
	bsf		LED_REG_PITCH, LED_PITCH

	;# Noten-Text
	TABLE_ADDR 	TXT_PAT_1
	call	LCD_TEXT

	;# Pattern-Position 1
	clrf	PAT_POS

	;# LCD-Daten ausgeben
	call	MODE_PITCH_LCD

	movlw	0x0F
	movwf	PAT_LEN

MODE_PITCH_LOOP

	call	PLAYER

	btfss	GL_EVENT, GL_EVENT_KEY
	goto	MODE_PITCH_LOOP
	bcf		GL_EVENT, GL_EVENT_KEY

	;# Normal-Mode
	movlw	KEYPRESS_FUNC
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
  	goto 	MODE_NORMAL	

	;# TAP
	movlw	KEYPRESS_TAP
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
  	goto 	MODE_PITCH_TAP

	;# Back
	movlw	KEYPRESS_BACK
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
  	goto 	MODE_PITCH_BACK

	;# Noten
	movlw	KEYPRESS_N1
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
  	goto 	MODE_PITCH_N1
	movlw	KEYPRESS_N2
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
  	goto 	MODE_PITCH_N2
	movlw	KEYPRESS_N3
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
  	goto 	MODE_PITCH_N3
	movlw	KEYPRESS_N4
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
  	goto 	MODE_PITCH_N4
	movlw	KEYPRESS_N5
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
  	goto 	MODE_PITCH_N5
	movlw	KEYPRESS_N6
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
  	goto 	MODE_PITCH_N6
	movlw	KEYPRESS_N7
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
  	goto 	MODE_PITCH_N7
	movlw	KEYPRESS_N8
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
  	goto 	MODE_PITCH_N8
	movlw	KEYPRESS_N9
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
  	goto 	MODE_PITCH_N9
	movlw	KEYPRESS_N10
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
  	goto 	MODE_PITCH_N10
	movlw	KEYPRESS_N11
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
  	goto 	MODE_PITCH_N11
	movlw	KEYPRESS_N12
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
  	goto 	MODE_PITCH_N12
	movlw	KEYPRESS_N13
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
  	goto 	MODE_PITCH_N13

	movlw	KEYPRESS_ACCENT
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
  	goto 	MODE_PITCH_ACCENT

	movlw	KEYPRESS_SLIDE
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
  	goto 	MODE_PITCH_SLIDE

	movlw	KEYPRESS_DOWN
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
  	goto 	MODE_PITCH_DOWN

	movlw	KEYPRESS_UP
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
  	goto 	MODE_PITCH_UP

retmpn

	goto	MODE_PITCH_LOOP

	return

;# Last Position
MODE_PITCH_BACK

	tstfsz	PAT_POS, W
	decf	PAT_POS, 1

	call	MODE_PITCH_LCD
	goto	MODE_PITCH_LOOP

;# Next Position	
MODE_PITCH_TAP

	incf	PAT_POS, 1
	movlw	0x10
	cpfslt	PAT_POS,W
	clrf	PAT_POS
	
	call	MODE_PITCH_LCD
	goto	MODE_PITCH_LOOP

;# LCD-Daten ausgeben
MODE_PITCH_LCD

	;# Graphic Steps
;	TABLE_ADDR 	TXT_STP_1
;	btfss	GL_EVENT, GL_EVENT_KEY
;	call	LCD_TEXT
;	movlw	0x40
;	addwf	PAT_POS, W
;	call	LCD_SET_CUR
;	movlw	0xFF
;	call	LCD_SET_CHR
;	call	LCD_DELAY_LONG
;	call	LCD_DELAY_LONG
;	call	LCD_DELAY_LONG

	;# Pattern-Position
;	TABLE_ADDR 	TXT_PAT_1
;	call	LCD_TEXT

	;# LED`s löschen
	call	CLR_LEDS
	bsf		LED_REG_PITCH, LED_PITCH

	;# LED`s ausgeben
	LFSR	FSR0, PAT_TME
	movf	FSR0L, W
	addwf	PAT_POS, W
	movwf	FSR0L
	movff	INDF0, PAT_TMP

	movlw	0x4F
	call	LCD_SET_CUR

	movlw	" "
	call	LCD_SET_CHR

	movlw	0x4F
	call	LCD_SET_CUR
	movlw	"B"
	btfsc	INDF0, PAT_TME_BL
	call	LCD_SET_CHR

	movlw	0x4F
	call	LCD_SET_CUR
	movlw	"W"
	btfsc	INDF0, PAT_TME_WT
	call	LCD_SET_CHR

	LFSR	FSR0, PAT_PIT
	movf	FSR0L, W
	addwf	PAT_POS, W
	movwf	FSR0L
	movff	INDF0, PAT_TMP
	bcf		PAT_TMP, 7
	bcf		PAT_TMP, 6
	bcf		PAT_TMP, 5
	bcf		PAT_TMP, 4

	btfsc	INDF0, PAT_PIT_AC
	bsf		LED_REG_ACCENT, LED_ACCENT

	btfsc	INDF0, PAT_PIT_SL
	bsf		LED_REG_SLIDE, LED_SLIDE

	btfsc	INDF0, PAT_PIT_DN
	bsf		LED_REG_DOWN, LED_DOWN

	btfsc	INDF0, PAT_PIT_UP
	bsf		LED_REG_UP, LED_UP

	movlw	0x46
	call	LCD_SET_CUR
	
	movlw	"-"
	call	LCD_SET_CHR
	movlw	"-"
	call	LCD_SET_CHR

	movlw	0x46
	call	LCD_SET_CUR

	btfss	INDF0, PAT_PIT_DN
	goto	PM1
	movlw	"D"
	call	LCD_SET_CHR
	movlw	"N"
	call	LCD_SET_CHR
	goto	PM2
PM1
	movlw	0x46
	call	LCD_SET_CUR

	btfss	INDF0, PAT_PIT_UP
	goto	PM2
	movlw	"U"
	call	LCD_SET_CHR
	movlw	"P"
	call	LCD_SET_CHR
PM2

	movlw	0x49
	call	LCD_SET_CUR

	movlw	" "
	call	LCD_SET_CHR
	movlw	" "
	call	LCD_SET_CHR

	movlw	0x49
	call	LCD_SET_CUR

	btfss	INDF0, PAT_PIT_AC
	goto	PM3
	movlw	"A"
	call	LCD_SET_CHR
	movlw	"C"
	call	LCD_SET_CHR
PM3
	
	movlw	0x4C
	call	LCD_SET_CUR

	movlw	" "
	call	LCD_SET_CHR
	movlw	" "
	call	LCD_SET_CHR

	movlw	0x4C
	call	LCD_SET_CUR

	btfss	INDF0, PAT_PIT_SL
	goto	PM4
	movlw	"S"
	call	LCD_SET_CHR
	movlw	"L"
	call	LCD_SET_CHR
PM4

	;# LCD-Pos
	movlw	0x43
	call	LCD_SET_CUR
	movlw	0
  	xorwf 	PAT_TMP,W
  	btfsc 	STATUS,Z
  	goto 	MPL0
	movlw	1
  	xorwf 	PAT_TMP,W
  	btfsc 	STATUS,Z
  	goto 	MPL1
	movlw	2
  	xorwf 	PAT_TMP,W
  	btfsc 	STATUS,Z
  	goto 	MPL2
	movlw	3
  	xorwf 	PAT_TMP,W
  	btfsc 	STATUS,Z
  	goto 	MPL3
	movlw	4
  	xorwf 	PAT_TMP,W
  	btfsc 	STATUS,Z
  	goto 	MPL4
	movlw	5
  	xorwf 	PAT_TMP,W
  	btfsc 	STATUS,Z
  	goto 	MPL5
	movlw	6
  	xorwf 	PAT_TMP,W
  	btfsc 	STATUS,Z
  	goto 	MPL6
	movlw	7
  	xorwf 	PAT_TMP,W
  	btfsc 	STATUS,Z
  	goto 	MPL7
	movlw	8
  	xorwf 	PAT_TMP,W
  	btfsc 	STATUS,Z
  	goto 	MPL8
	movlw	9
  	xorwf 	PAT_TMP,W
  	btfsc 	STATUS,Z
  	goto 	MPL9
	movlw	10
  	xorwf 	PAT_TMP,W
  	btfsc 	STATUS,Z
  	goto 	MPL10
	movlw	11
  	xorwf 	PAT_TMP,W
  	btfsc 	STATUS,Z
  	goto 	MPL11
  	goto 	MPL12

retmpl
	;# LCD
	call	LCD_SET_CHR
	movlw	0x40
	call	LCD_SET_CUR
	
	movf	PAT_POS, w
	call	LCD_TXT_BCD

	return

MPL0
	bsf		LED_REG_N1, LED_N1
	movlw	"C"
	call	LCD_SET_CHR
	movlw	" "
	goto	retmpl
MPL1
	bsf		LED_REG_N2, LED_N2
	movlw	"C"
	call	LCD_SET_CHR
	movlw	"#"
	goto	retmpl
MPL2
	bsf		LED_REG_N3, LED_N3
	movlw	"D"
	call	LCD_SET_CHR
	movlw	" "
	goto	retmpl
MPL3
	bsf		LED_REG_N4, LED_N4
	movlw	"D"
	call	LCD_SET_CHR
	movlw	"#"
	goto	retmpl
MPL4
	bsf		LED_REG_N5, LED_N5
	movlw	"E"
	call	LCD_SET_CHR
	movlw	" "
	goto	retmpl
MPL5
	bsf		LED_REG_N6, LED_N6
	movlw	"F"
	call	LCD_SET_CHR
	movlw	" "
	goto	retmpl
MPL6
	bsf		LED_REG_N7, LED_N7
	movlw	"F"
	call	LCD_SET_CHR
	movlw	"#"
	goto	retmpl
MPL7
	bsf		LED_REG_N8, LED_N8
	movlw	"G"
	call	LCD_SET_CHR
	movlw	" "
	goto	retmpl
MPL8
	bsf		LED_REG_N9, LED_N9
	movlw	"G"
	call	LCD_SET_CHR
	movlw	"#"
	goto	retmpl
MPL9
	bsf		LED_REG_N10, LED_N10
	movlw	"A"
	call	LCD_SET_CHR
	movlw	" "
	goto	retmpl
MPL10
	bsf		LED_REG_N11, LED_N11
	movlw	"A"
	call	LCD_SET_CHR
	movlw	"#"
	goto	retmpl
MPL11
	bsf		LED_REG_N12, LED_N12
	movlw	"B"
	call	LCD_SET_CHR
	movlw	" "
	goto	retmpl
MPL12
	bsf		LED_REG_N13, LED_N13
	movlw	"C"
	call	LCD_SET_CHR
	movlw	"+"
	goto	retmpl

MODE_PITCH_N1
	movlw	0
	goto	MODE_PITCH_SETNEWNOTE
MODE_PITCH_N2
	movlw	1
	goto	MODE_PITCH_SETNEWNOTE
MODE_PITCH_N3
	movlw	2
	goto	MODE_PITCH_SETNEWNOTE
MODE_PITCH_N4
	movlw	3
	goto	MODE_PITCH_SETNEWNOTE
MODE_PITCH_N5
	movlw	4
	goto	MODE_PITCH_SETNEWNOTE
MODE_PITCH_N6
	movlw	5
	goto	MODE_PITCH_SETNEWNOTE
MODE_PITCH_N7
	movlw	6
	goto	MODE_PITCH_SETNEWNOTE
MODE_PITCH_N8
	movlw	7
	goto	MODE_PITCH_SETNEWNOTE
MODE_PITCH_N9
	movlw	8
	goto	MODE_PITCH_SETNEWNOTE
MODE_PITCH_N10
	movlw	9
	goto	MODE_PITCH_SETNEWNOTE
MODE_PITCH_N11
	movlw	10
	goto	MODE_PITCH_SETNEWNOTE
MODE_PITCH_N12
	movlw	11
	goto	MODE_PITCH_SETNEWNOTE
MODE_PITCH_N13
	movlw	12

MODE_PITCH_SETNEWNOTE
	movwf	PAT_TMP
	LFSR	FSR0, PAT_PIT
	movf	FSR0L, W
	addwf	PAT_POS, W
	movwf	FSR0L
	bcf		INDF0, PAT_PIT_0
	bcf		INDF0, PAT_PIT_1
	bcf		INDF0, PAT_PIT_2
	bcf		INDF0, PAT_PIT_3
	btfsc	PAT_TMP,0
	bsf		INDF0, PAT_PIT_0
	btfsc	PAT_TMP,1
	bsf		INDF0, PAT_PIT_1
	btfsc	PAT_TMP,2
	bsf		INDF0, PAT_PIT_2
	btfsc	PAT_TMP,3
	bsf		INDF0, PAT_PIT_3
	call	MODE_PITCH_LCD	
	goto	retmpn

MODE_PITCH_TIME
	LFSR	FSR0, PAT_TME
	movf	FSR0L, W
	addwf	PAT_POS, W
	movwf	FSR0L
	btg		INDF0, PAT_TME_BL
	call	MODE_PITCH_LCD	
	goto	retmpn

MODE_PITCH_ACCENT
	LFSR	FSR0, PAT_PIT
	movf	FSR0L, W
	addwf	PAT_POS, W
	movwf	FSR0L
	btg		INDF0, PAT_PIT_AC
	call	MODE_PITCH_LCD	
	goto	retmpn

MODE_PITCH_SLIDE
	LFSR	FSR0, PAT_PIT
	movf	FSR0L, W
	addwf	PAT_POS, W
	movwf	FSR0L
	btg		INDF0, PAT_PIT_SL
	call	MODE_PITCH_LCD	
	goto	retmpn

MODE_PITCH_DOWN
	LFSR	FSR0, PAT_PIT
	movf	FSR0L, W
	addwf	PAT_POS, W
	movwf	FSR0L
	btg		INDF0, PAT_PIT_DN
	call	MODE_PITCH_LCD	
	goto	retmpn

MODE_PITCH_UP
	LFSR	FSR0, PAT_PIT
	movf	FSR0L, W
	addwf	PAT_POS, W
	movwf	FSR0L
	btg		INDF0, PAT_PIT_UP
	call	MODE_PITCH_LCD	
	goto	retmpn
