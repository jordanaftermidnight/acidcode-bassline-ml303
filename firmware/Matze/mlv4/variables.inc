;#---------------------------------------------------------------
;# VAR TEMP
;#---------------------------------------------------------------
TMP_W				EQU 0x010
TMP_W2				EQU 0x011
TMP_W3				EQU 0x012
TMP_I				EQU 0x013
TMP_J				EQU 0x014
TMP_X				EQU 0x015
BSR_TMP				EQU 0x016
IRQ_TMP				EQU 0x017
STATUS_TMP			EQU 0x018
LAST_SLIDE			EQU 0x019
LASTSLIDEVCO		EQU 0x01A
LAST_WHITE			EQU 0x01B
GATEBUS_TMP			EQU 0x01C
RUN					EQU 0x01D
SNDMODE				EQU 0x01E

;#---------------------------------------------------------------
;# VAR I2C
;#---------------------------------------------------------------
I2C_BUFFER			EQU 0x01F
I2C_CTR				EQU 0x020

;#---------------------------------------------------------------
;# VAR DATABUS
;#---------------------------------------------------------------
DATABUS				EQU PORTA
DATABUS_TRIS		EQU TRISA

DATABUS_STROBE		EQU PORTC
DATABUS_STROBE_TRIS	EQU PORTC

DATABUS_A_STROBE 	EQU 0
DATABUS_B_STROBE 	EQU 1
DATABUS_C_STROBE 	EQU 2
DATABUS_D_STROBE 	EQU 3
DATABUS_E_STROBE 	EQU 4

;#---------------------------------------------------------------
;# VAR KEYBUS
;#---------------------------------------------------------------
KEYBUS				EQU PORTB
KEYBUS_TRIS			EQU TRISB

KEYBUS_STROBE		EQU PORTD
KEYBUS_STROBE_TRIS	EQU TRISD

KEYBUS_A_STROBE 	EQU 0 
KEYBUS_B_STROBE 	EQU 1 
KEYBUS_C_STROBE 	EQU 2 
KEYBUS_D_STROBE 	EQU 3
KEYBUS_E_STROBE 	EQU 4
KEYBUS_F_STROBE 	EQU 5 
KEYBUS_G_STROBE 	EQU 6 
KEYBUS_H_STROBE 	EQU 7 

;#---------------------------------------------------------------
;# VAR MEMBUS
;#---------------------------------------------------------------
MEMBUS			EQU PORTB
MEMBUS_TRIS		EQU TRISB

MEMBUS_SCL		EQU 4
MEMBUS_SDA		EQU 5

;#---------------------------------------------------------------
;# VAR GATEBUS
;#---------------------------------------------------------------
GATEBUS         	EQU PORTE
GATEBUS_TRIS		EQU TRISE

GATEBUS_SLIDE   	EQU 0
GATEBUS_ACCENT  	EQU 1
GATEBUS_GATE    	EQU 2

;#---------------------------------------------------------------
;# VAR LEDS
;#---------------------------------------------------------------
LED_REG_A			EQU 0x030
LED_REG_RUN			EQU 0x030
LED_REG_PITCH		EQU 0x030
LED_REG_FUNC		EQU 0x030
LED_REG_N1			EQU 0x030
LED_REG_N2			EQU 0x030
LED_REG_N3			EQU 0x030

LED_RUN     		EQU 0
LED_PITCH			EQU 1
LED_FUNC			EQU 2
LED_N1				EQU 3
LED_N2				EQU 4
LED_N3				EQU 5

LED_REG_B			EQU 0x031
LED_REG_N4			EQU 0x031
LED_REG_N5			EQU 0x031
LED_REG_N6			EQU 0x031
LED_REG_N7			EQU 0x031
LED_REG_N8			EQU 0x031
LED_REG_N9			EQU 0x031

LED_N4				EQU 0
LED_N5				EQU 1
LED_N6				EQU 2
LED_N7				EQU 3
LED_N8				EQU 4
LED_N9				EQU 5

LED_REG_C			EQU 0x032
LED_REG_N10			EQU 0x032
LED_REG_N11			EQU 0x032
LED_REG_N12			EQU 0x032
LED_REG_N13			EQU 0x032
LED_REG_DOWN		EQU 0x032
LED_REG_UP			EQU 0x032

LED_N10				EQU 0
LED_N11				EQU 1
LED_N12				EQU 2
LED_N13				EQU 3
LED_DOWN			EQU 4
LED_UP				EQU 5

LED_REG_D			EQU 0x033
LED_REG_ACCENT		EQU 0x033
LED_REG_SLIDE		EQU 0x033
LED_REG_TIME		EQU 0x033
LED_REG_BLACK		EQU 0x033
LED_REG_WHITE		EQU 0x033
LED_REG_PAUSE		EQU 0x033

LED_ACCENT			EQU 0
LED_SLIDE			EQU 1
LED_TIME			EQU 2
LED_BLACK			EQU 3
LED_WHITE			EQU 4
LED_PAUSE			EQU 5

LED_BLINKER			EQU	0x034

;#---------------------------------------------------------------
;# VAR VCO
;#---------------------------------------------------------------
VCO					EQU	0x03A
VCO_OFF				EQU 0x03B

;#---------------------------------------------------------------
;# VAR Keyboard
;#---------------------------------------------------------------
KEYPRESS			EQU 0x040
LAST_KEYPRESS		EQU 0x041

KEYPRESS_NONE		EQU 0

KEYPRESS_CLR		EQU 1
KEYPRESS_PITCH		EQU 2
KEYPRESS_RUN		EQU 3
KEYPRESS_FUNC		EQU 4
KEYPRESS_N1			EQU 5
KEYPRESS_N2			EQU 6
KEYPRESS_N3			EQU 7
KEYPRESS_N4			EQU 8
KEYPRESS_N5			EQU 9
KEYPRESS_N6			EQU 10
KEYPRESS_N7			EQU 11
KEYPRESS_N8			EQU 12
KEYPRESS_N9			EQU 13
KEYPRESS_N10		EQU 14
KEYPRESS_N11		EQU 15
KEYPRESS_N12		EQU 16
KEYPRESS_N13		EQU 17
KEYPRESS_DOWN		EQU 18
KEYPRESS_UP			EQU 19
KEYPRESS_ACCENT		EQU 20
KEYPRESS_SLIDE		EQU 21
KEYPRESS_TIME		EQU 22
KEYPRESS_BACK		EQU 23
KEYPRESS_TAP		EQU 24

;#---------------------------------------------------------------
;# VAR Delay
;#---------------------------------------------------------------
DELAY_H				EQU 0x050
DELAY_L				EQU 0x051

;#---------------------------------------------------------------
;# VAR Pattern
;#---------------------------------------------------------------
PAT_POS				EQU 0x060
PAT_LEN				EQU 0x061
PAT_BANK			EQU 0x062
PAT_MEM_A			EQU 0x063
PAT_MEM_B			EQU 0x064
PAT_TMP_B			EQU 0x065
TMP_B				EQU 0x066
PAT_BPM				EQU 0x067

;#---------------------------------------------------------------
;# VAR EEPROM
;#---------------------------------------------------------------
XEEH				EQU 0x070
XEEL				EQU 0x071
XBYT				EQU 0x072

;#---------------------------------------------------------------
;# VAR EVENT
;#---------------------------------------------------------------
EVENT				EQU 0x080
EVENT_KEYPRESS		EQU 0

;#---------------------------------------------------------------
;# VAR Config
;#---------------------------------------------------------------
CFG					EQU 0x090
CFG_S_PGM			EQU 0
CFG_R_PGM			EQU 1
CFG_S_SYNC			EQU 2
CFG_S_MIDI			EQU 4

;#---------------------------------------------------------------
;# VAR Midi
;#---------------------------------------------------------------
MIDI_CHANNEL		EQU 0x0A0
MIDI_OUTBYTE		EQU 0x0A1
MIDI_BYTE			EQU 0x0A2
MIDI_CMD1			EQU 0x0A3
MIDI_CMD2			EQU 0x0A4
MIDI_CMD3			EQU 0x0A5

;#---------------------------------------------------------------
;# VAR BPM TIMER
;#---------------------------------------------------------------
TICK				EQU 0x0B0
BPMDIV				EQU 0x0B1
