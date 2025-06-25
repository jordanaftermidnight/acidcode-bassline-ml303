TIMER2_INIT
	;# LED-MPLEX Timer
    movlw	b'01111111'
    movwf   T2CON
    movlw  	100
    movwf  	PR2

	return
