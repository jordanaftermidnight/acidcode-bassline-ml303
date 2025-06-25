PORTS_INIT

	;----------------------------------------------------------------------------------
	; PortA and E: Digital Pins  
	;----------------------------------------------------------------------------------
	movlw	0x07
  	movwf	ADCON1

	;----------------------------------------------------------------------------------
  	;# Pullups deaktivieren
	;----------------------------------------------------------------------------------
	bsf		INTCON2, NOT_RBPU

	;# PortA = 3 Key Input / 4 Output
	movlw	b'00000111'
	movwf	TRISA
	clrf	PORTA

	;# PortB = Output
	clrf	TRISB
	clrf	PORTB
	
	;# PortC = Midi Input / Output
	movlw	b'10000000'
	movwf	TRISC
	clrf	TRISC

	;# PortD = Output
	clrf	TRISD
	clrf	PORTD

	;# PortE = Output
	clrf	TRISE
	clrf	PORTE
	clrf	LATE

	return

