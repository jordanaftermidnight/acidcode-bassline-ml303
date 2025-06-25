;###############################################################
;# Pattern Functions
;###############################################################
;---------------------------------------------------------------
; Init
;---------------------------------------------------------------
PAT_INIT

	;# Pattern Modus
	TABLE_ADDR 	TXT_PAT_0
	call	LCD_TEXT
	call	PAT_LOAD

	return

;---------------------------------------------------------------
; Load from Flash
;---------------------------------------------------------------
PAT_LOAD
	
	;# LCD: Loading
	TABLE_ADDR 	TXT_LOD_1
	call	LCD_TEXT

	;# Load Name from Flash
	TABLE_ADDR	DAT_PAT
	LFSR	FSR0, PAT_TXT
	movlw	0x08
	movwf	COUNTER
PAT_LOAD_LOOP1
	clrwdt
	tblrd*+
	movff	TABLAT, POSTINC0
	decfsz	COUNTER, F
	goto	PAT_LOAD_LOOP1

	call	PAT_NAME2LCD
	call	LCD_DELAY_HLP

	return

;---------------------------------------------------------------
; PATTERN - NAME 2 LCD
;---------------------------------------------------------------
PAT_NAME2LCD

	;# LCD: Print Name
	movlw	0x88
	call	LCD_SET_CUR
	LFSR	FSR0, PAT_TXT
	movlw	0x08
	movwf	COUNTER
PAT_NAME2LCD_LOOP1
	clrwdt
	movf	POSTINC0, w	
	call	LCD_SET_CHR
	decfsz	COUNTER, F
	goto	PAT_NAME2LCD_LOOP1

	return

;---------------------------------------------------------------
; PATTERN ENTER NAME
;---------------------------------------------------------------
PAT_ENTER_NAME

	clrf	CHARPOS

;	goto	nohlp

	;# Help Display
	clrf	LED_REG_0
	clrf	LED_REG_1
	clrf	LED_REG_2
	clrf	LED_REG_3
	clrf	LED_REG_4
	clrf	LED_REG_5
	clrf	LED_REG_6
	clrf	LED_REG_7
	TABLE_ADDR 	TXT_HLP_NAME_1
	call	LCD_TEXT
	call	LCD_DELAY_HLP
	call	LCD_DELAY_HLP
	TABLE_ADDR 	TXT_HLP_NAME_2
	call	LCD_TEXT
	call	PAT_NAME_BLINKHLP
	call	LCD_DELAY_HLP
	TABLE_ADDR 	TXT_HLP_NAME_3
	call	LCD_TEXT
	call	LCD_DELAY_HLP
	call	PAT_NAME_BLINKHLP2
	call	LCD_DELAY_HLP
	TABLE_ADDR 	TXT_HLP_NAME_4
	call	LCD_TEXT
	call	LCD_DELAY_HLP
	call	LCD_DELAY_HLP
	TABLE_ADDR 	TXT_HLP_NAME_5
	call	LCD_TEXT
	call	LCD_DELAY_HLP
	call	LCD_DELAY_HLP
	TABLE_ADDR 	TXT_HLP_NAME_6
	call	LCD_TEXT
	call	LCD_DELAY_HLP
	bsf		LED_REG_FUNC, LED_FUNC
	call	LCD_DELAY_LONG2
	bcf		LED_REG_FUNC, LED_FUNC
	call	LCD_DELAY_HLP
	TABLE_ADDR 	TXT_HLP_NAME_1
	call	LCD_TEXT

nohlp

	bsf		LED_REG_N1, LED_N1

	movlw	0x88
	call	LCD_SET_CUR
	
	;# Cursor ON
	movlw	b'00000000'
	call	LCD_DATA_OUT
	movlw	b'11010000'
	call	LCD_DATA_OUT

PAT_ENTER_NAME_LOOP1
	btfss	GL_EVENT, GL_EVENT_KEY
	goto	PAT_ENTER_NAME_LOOP1
	bcf		GL_EVENT, GL_EVENT_KEY

	movlw	KEYPRESS_N1
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
  	goto 	PAT_ENTER_NAME_0
	movlw	KEYPRESS_N3
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
  	goto 	PAT_ENTER_NAME_1
	movlw	KEYPRESS_N5
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
  	goto 	PAT_ENTER_NAME_2
	movlw	KEYPRESS_N6
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
  	goto 	PAT_ENTER_NAME_3
	movlw	KEYPRESS_N8
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
  	goto 	PAT_ENTER_NAME_4
	movlw	KEYPRESS_N10
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
  	goto 	PAT_ENTER_NAME_5
	movlw	KEYPRESS_N12
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
  	goto 	PAT_ENTER_NAME_6
	movlw	KEYPRESS_N13
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
  	goto 	PAT_ENTER_NAME_7
	movlw	KEYPRESS_BACK
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
  	goto 	PAT_ENTER_NAME_INC
	movlw	KEYPRESS_TAP
  	xorwf 	KEYPRESS,W
  	btfsc 	STATUS,Z
  	goto 	PAT_ENTER_NAME_DEC
	goto	PAT_ENTER_NAME_LOOP1

PAT_ENTER_NAME_INC
	movlw	PAT_TXT
	addwf	CHARPOS, 0
	movwf	FSR0L
	clrf	FSR0H
	incf	INDF0, 1
	call	PAT_ENTER_BOUND
	call	PAT_NAME2LCD		
	call	PAT_ENTER_NAME_SC
	goto	PAT_ENTER_NAME_LOOP1

PAT_ENTER_NAME_DEC
	movlw	PAT_TXT
	addwf	CHARPOS, 0
	movwf	FSR0L
	clrf	FSR0H
	decf	INDF0, 1
	call	PAT_ENTER_BOUND	
	call	PAT_NAME2LCD		
	call	PAT_ENTER_NAME_SC
	goto	PAT_ENTER_NAME_LOOP1

PAT_ENTER_BOUND
	movlw	0x60
	cpfslt	INDF0
	goto	PEB2

	movlw	0x1F
	cpfsgt	INDF0
	goto	PEB
	return

PEB
	movlw	0x5F
	movwf	INDF0
	return

PEB2
	movlw	0x20
	movwf	INDF0
	return

PAT_ENTER_NAME_SC
	movlw	0x88
	addwf	CHARPOS, 0
	call	LCD_SET_CUR
	return

PAT_ENTER_NAME_0
	movlw	0
	movwf	CHARPOS
	movlw	0x88
	call	LCD_SET_CUR
	call	PAT_NAME_CLRLED
	bsf		LED_REG_N1, LED_N1
	goto	PAT_ENTER_NAME_LOOP1
PAT_ENTER_NAME_1
	movlw	1
	movwf	CHARPOS
	movlw	0x89
	call	LCD_SET_CUR
	call	PAT_NAME_CLRLED
	bsf		LED_REG_N3, LED_N3
	goto	PAT_ENTER_NAME_LOOP1
PAT_ENTER_NAME_2
	movlw	2
	movwf	CHARPOS
	movlw	0x8A
	call	LCD_SET_CUR
	call	PAT_NAME_CLRLED
	bsf		LED_REG_N5, LED_N5
	goto	PAT_ENTER_NAME_LOOP1
PAT_ENTER_NAME_3
	movlw	3
	movwf	CHARPOS
	movlw	0x8B
	call	LCD_SET_CUR
	call	PAT_NAME_CLRLED
	bsf		LED_REG_N6, LED_N6
	goto	PAT_ENTER_NAME_LOOP1
PAT_ENTER_NAME_4
	movlw	4
	movwf	CHARPOS
	movlw	0x8C
	call	LCD_SET_CUR
	call	PAT_NAME_CLRLED
	bsf		LED_REG_N8, LED_N8
	goto	PAT_ENTER_NAME_LOOP1
PAT_ENTER_NAME_5
	movlw	5
	movwf	CHARPOS
	movlw	0x8D
	call	LCD_SET_CUR
	call	PAT_NAME_CLRLED
	bsf		LED_REG_N10, LED_N10
	goto	PAT_ENTER_NAME_LOOP1
PAT_ENTER_NAME_6
	movlw	6
	movwf	CHARPOS
	movlw	0x8E
	call	LCD_SET_CUR
	call	PAT_NAME_CLRLED
	bsf		LED_REG_N12, LED_N12
	goto	PAT_ENTER_NAME_LOOP1
PAT_ENTER_NAME_7
	movlw	7
	movwf	CHARPOS
	movlw	0x8F
	call	LCD_SET_CUR
	call	PAT_NAME_CLRLED
	bsf		LED_REG_N13, LED_N13
	goto	PAT_ENTER_NAME_LOOP1

PAT_NAME_BLINKHLP
	call	LCD_DELAY_HLP
	bsf		LED_REG_N1, LED_N1
	bsf		LED_REG_N3, LED_N3
	bsf		LED_REG_N5, LED_N5
	bsf		LED_REG_N6, LED_N6
	bsf		LED_REG_N8, LED_N8
	bsf		LED_REG_N10, LED_N10
	bsf		LED_REG_N12, LED_N12
	bsf		LED_REG_N13, LED_N13
	call	LCD_DELAY_HLP
PAT_NAME_CLRLED
	clrf	LED_REG_0
	clrf	LED_REG_1
	clrf	LED_REG_2
	clrf	LED_REG_3
	clrf	LED_REG_4
	clrf	LED_REG_5
	clrf	LED_REG_6
	clrf	LED_REG_7
	return

PAT_NAME_BLINKHLP2
	bsf		LED_REG_N1, LED_N1
	call	PAT_DELAY
	call	PAT_NAME_CLRLED
	bsf		LED_REG_N3, LED_N3
	call	PAT_DELAY
	call	PAT_NAME_CLRLED
	bsf		LED_REG_N5, LED_N5
	call	PAT_DELAY
	call	PAT_NAME_CLRLED
	bsf		LED_REG_N6, LED_N6
	call	PAT_DELAY
	call	PAT_NAME_CLRLED
	bsf		LED_REG_N8, LED_N8
	call	PAT_DELAY
	call	PAT_NAME_CLRLED
	bsf		LED_REG_N10, LED_N10
	call	PAT_DELAY
	call	PAT_NAME_CLRLED
	bsf		LED_REG_N12, LED_N12
	call	PAT_DELAY
	call	PAT_NAME_CLRLED
	bsf		LED_REG_N13, LED_N13
	call	PAT_DELAY
	call	PAT_NAME_CLRLED
	return

PAT_DELAY
	movlw	0
	call	LCD_DELAY_CUSTOM
	movlw	64
	call	LCD_DELAY_CUSTOM
	return

;---------------------------------------------------------------
; CLR - Clear
;---------------------------------------------------------------
PAT_CLR
; 	LFSR	FSR0, PAT_PIT ;# Pitch
PAT_CLR_LOOP1:
;	CLRF	POSTINC0
;	movlw 	PAT_PIT + 0x0F   
;	cpfse 	FSR0   	
;	goto	PAT_CLR_LOOP1

; 	LFSR	FSR0, PAT_TME ;# Time
PAT_CLR_LOOP2:
;	CLRF	POSTINC0
;	movlw 	PAT_TME + 0x0F   
;	cpfse 	FSR0   	
;	goto 	PAT_CLR_LOOP2

  	return

;---------------------------------------------------------------
; SHL - Shift left
;---------------------------------------------------------------
PAT_SHL
  	return

;---------------------------------------------------------------
; SHR - Shift right
;---------------------------------------------------------------
PAT_SHR
  	return

;---------------------------------------------------------------
; REV - Reverse
;---------------------------------------------------------------
PAT_REV
  	return

;---------------------------------------------------------------
; RND - Random
;---------------------------------------------------------------
PAT_RND
  	return

FLASH_BURN
	bsf		EECON1, EEPGD		; point to FLASH program memory
	bcf		EECON1, CFGS		; access FLASH program memory
	bsf		EECON1, WREN		; enable write to memory
	movlw	0x55			; write 55h
	movwf	EECON2
	movlw	0xaa			; write AAh
	movwf	EECON2
	bsf		EECON1, WR		; start program (CPU stall)
FLASH_WriteLoop
	btfsc	EECON1, WR
	goto FLASH_WriteLoop
	bcf		EECON1, WREN		; disable write to memory
	return

FLASH_ERASE
	bsf	EECON1, EEPGD		; point to FLASH program memory
	bcf	EECON1, CFGS		; access FLASH program memory
	bsf	EECON1, WREN		; enable write to memory
	bsf	EECON1, FREE		; enable Row Erase operation
	movlw	0x55			; write 55h
	movwf	EECON2
	movlw	0xaa			; write AAh
	movwf	EECON2
	bsf	EECON1, WR		; start erase (CPU stall)
FLASH_EraseLoop
	btfsc	EECON1, WR
	goto FLASH_EraseLoop
	tblrd*-				; dummy read decrement
	return
