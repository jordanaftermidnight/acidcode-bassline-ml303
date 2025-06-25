;####################################################################################
;# Init
;####################################################################################
LCD_INIT
	
	;# Clear RS
	bcf		LCD_RS_PORT, LCD_RS

	;# 4-Bit Mode (2x Out)
	movlw	b'00100000'
	call	LCD_DATA_OUT
	call	LCD_DELAY

	;# 2x16 Chars / Font
	movlw	b'00100000'
	call	LCD_DATA_OUT
	movlw	b'10000000'
	call	LCD_DATA_OUT
	call	LCD_DELAY

	;# Display ON
	movlw	b'00000000'
	call	LCD_DATA_OUT
	movlw	b'11000000'
	call	LCD_DATA_OUT
	call	LCD_DELAY

	;# Display Clear
	movlw	b'00000000'
	call	LCD_DATA_OUT
	movlw	b'00010000'
	call	LCD_DATA_OUT
	call	LCD_DELAY

	;# Auto-Increment
	movlw	b'00000000'
	call	LCD_DATA_OUT
	movlw	b'01100000'
	call	LCD_DATA_OUT
	call	LCD_DELAY

	goto	nointr

	;# Revision
	movlw	"R"
	call	LCD_SET_CHR
	movlw	"E"
	call	LCD_SET_CHR
	movlw	"V"
	call	LCD_SET_CHR
	movlw	" "
	call	LCD_SET_CHR
	movlw	cnVER_MAJ
	call	LCD_SET_CHR
	movlw	"."
	call	LCD_SET_CHR
	movlw	cnVER_MIN
	call	LCD_SET_CHR

	;# Pause
	call	LCD_DELAY_LONG

	;# Introtext
	TABLE_ADDR TXT_INTRO_0
	call	LCD_TEXT
	TABLE_ADDR TXT_INTRO_1
	call	LCD_TEXT

	;# Pause
	call	LCD_DELAY_LONG

	;# Introtext
	TABLE_ADDR TXT_COPYRIGHT_0
	call	LCD_TEXT
	TABLE_ADDR TXT_COPYRIGHT_1
	call	LCD_TEXT

	;# Pause
	call	LCD_DELAY_LONG

nointr

	return

;####################################################################################
;# Strobe
;####################################################################################
LCD_STROBE
	bsf		LCD_E_PORT, LCD_E
	call	LCD_DELAY
	bcf		LCD_E_PORT, LCD_E
	nop
	nop
	nop
	nop
	return

;####################################################################################
;# Data Out
;####################################################################################
LCD_DATA_OUT
	movwf	LCD_TMP
LCD_DATA_OUT2
	bcf		LCD_D7_PORT, LCD_D7
	bcf		LCD_D6_PORT, LCD_D6
	bcf		LCD_D5_PORT, LCD_D5
	bcf		LCD_D4_PORT, LCD_D4
	btfsc	LCD_TMP, 7
	bsf		LCD_D7_PORT, LCD_D7
	btfsc	LCD_TMP, 6
	bsf		LCD_D6_PORT, LCD_D6
	btfsc	LCD_TMP, 5
	bsf		LCD_D5_PORT, LCD_D5
	btfsc	LCD_TMP, 4
	bsf		LCD_D4_PORT, LCD_D4
	call	LCD_STROBE
;	call	LCD_DELAY
	return

;####################################################################################
;# Set Cursor Pos
;####################################################################################
LCD_SET_CUR
	iorlw	0x80
	movwf	LCD_TMP
	call	LCD_SET_DAT
	return

;####################################################################################
;# Print Character
;####################################################################################
LCD_SET_CHR
	bsf		LCD_RS_PORT, LCD_RS
	movwf	LCD_TMP
LCD_SET_DAT
	call	LCD_DATA_OUT2
	rlcf	LCD_TMP
	rlcf	LCD_TMP
	rlcf	LCD_TMP
	rlcf	LCD_TMP
	call	LCD_DATA_OUT2
	bcf		LCD_RS_PORT, LCD_RS
	return

;####################################################################################
;# Text
;####################################################################################
LCD_TEXT

LCD_PrintText
	;; get text counter and cursor pos
	tblrd*+
	movf	TABLAT, W
	call	LCD_SET_CUR

	tblrd*+
	movff	TABLAT, LCD_TXT_CTR

LCD_PrintTextConfigured			; (LCD_TEXT_CTR must be preconfigured)
LCD_PrintTextLoop
	tblrd*+						; print out first char
	movf	TABLAT, W
	call	LCD_SET_CHR
	
	decfsz	LCD_TXT_CTR, F		; decrement text counter, leave routine if zero
	goto	LCD_PrintTextLoopNext
	tblrd*+						; dummy read
	return
LCD_PrintTextLoopNext

	tblrd*+						; print out second char
	movf	TABLAT, W
	call	LCD_SET_CHR

	decfsz	LCD_TXT_CTR, F		; decrement text counter, leave routine if zero
	goto	LCD_PrintTextLoop

;	call	LCD_DELAY
;	call	LCD_DELAY
;	call	LCD_DELAY
;	call	LCD_DELAY
	return


;####################################################################################
;# Delay
;####################################################################################
LCD_DELAY
	; Long Delay
	movlw	18
LCD_DELAY_CUSTOM
	movwf	LCD_DELAY_H
	clrf	LCD_DELAY_L
LCD_LDelay_Loop
	clrwdt
	decfsz	LCD_DELAY_L, F
	goto	LCD_LDelay_Loop
	decfsz	LCD_DELAY_H, F
	goto	LCD_LDelay_Loop
	return

LCD_DELAY_LONG
	call	LCD_DELAY_LONG2
	call	LCD_DELAY_LONG2
	call	LCD_DELAY_LONG2
	return

LCD_DELAY_LONG2
	clrf	LCD_DELAY_Z
LCD_LDelay_Long_Loop
	btfss	GL_EVENT, GL_EVENT_KEY
	call	LCD_DELAY
	decfsz	LCD_DELAY_Z, F
	goto	LCD_LDelay_Long_Loop
	return

LCD_DELAY_HLP
	call	LCD_DELAY_LONG2
	return

LCD_TXT_BCD
    movwf   BCD_Temp
	incf	BCD_Temp, F

    CLRF    BCD_R0
    SWAPF   BCD_Temp, W 
    ADDWF   BCD_Temp, W 
    ANDLW   0x0f
	btfsc	STATUS, DC
    ADDLW   0x16 
	btfsc	STATUS, DC
    ADDLW   0x06 
    ADDLW   0x06 
	btfss	STATUS, DC
    ADDLW  -0x06 

    BTFSC   BCD_Temp,4 
    ADDLW   0x16 - 1 + 0x6 
	btfss	STATUS, DC
    ADDLW  -0x06 

    BTFSC   BCD_Temp, 5 
    ADDLW   0x30 

    BTFSC   BCD_Temp, 6 
    ADDLW   0x60 

    BTFSC   BCD_Temp, 7 
    ADDLW   0x20 

    ADDLW   0x60 
    RLCF    BCD_R0, F 
    BTFSS   BCD_R0, 0 
    ADDLW  -0x60 

    MOVWF   BCD_R1
    BTFSC   BCD_Temp,7 
    INCF    BCD_R0, F

	movf	BCD_R1, w
    swapf   BCD_R1, w
	call	LCD_SET_DIGIT

	movf	BCD_R1, w
	call	LCD_SET_DIGIT

	return

LCD_SET_DIGIT
	andlw	0x0f
	addlw	-0x0a
	btfsc	STATUS, C
	addlw	0x07
	addlw	0x3a
	goto	LCD_SET_CHR
