;###############################################################
;# CONST Version
;###############################################################
;---------------------------------------------------------------
w	EQU W

#define cnVER_MAJ 	"5"
#define cnVER_MIN 	"0"	 ;# 5.0

;###############################################################
;# CONST Global
;###############################################################
;---------------------------------------------------------------
#define cnOFF		0
#define cnON		1	 
;---------------------------------------------------------------
#define cnFUNC		0 
#define cnPITCH		1 
#define cnTIME		2 
#define cnSONG		3
;---------------------------------------------------------------
#define cnMASTER	0
#define cnSLAVE		1
#define cnKIN		2
#define cnKOUT		3
#define cnSILENT	4
;---------------------------------------------------------------

;###############################################################
;# CONST Board
;###############################################################
;---------------------------------------------------------------
#define cnPCB		1 ;# 0 = V4
			  		  ;# 1 = V5
;---------------------------------------------------------------

;###############################################################
;# VAR Global
;###############################################################
;---------------------------------------------------------------
GL_INI		EQU 0x00 ;# Init Array (00..02)
			 ;# 00 = A
			 ;# 01 = C
			 ;# 02 = D
;---------------------------------------------------------------
GL_VER		EQU 0x03 ;# Version (00..02)
			 ;# 00 = MAJ
			 ;# 01 = MIN
			 ;# 02 = REV
;---------------------------------------------------------------
GL_LCD		EQU 0x07 ;# LCD 
			 ;# 0 = Off
			 ;# 1 = On
;---------------------------------------------------------------
GL_MODE		EQU 0x08 ;# Mode
			 ;# 0 = Func
			 ;# 1 = Pitch
			 ;# 2 = Time
			 ;# 3 = Song
;---------------------------------------------------------------
GL_EVENT		EQU 0x09 ;# Event
GL_EVENT_KEY	EQU 0	 ;# Keypress
GL_EVENT_MIDI	EQU 1	 ;# Midi
GL_EVENT_TICK	EQU 2	 ;# 24 ppqn Tick
;---------------------------------------------------------------

;###############################################################
;# VAR Pattern
;###############################################################
;---------------------------------------------------------------
PAT_TXT		EQU 0x10 ;# Text 00..07
;---------------------------------------------------------------
PAT_NUM		EQU 0x18 ;# Number 0..127
;---------------------------------------------------------------
PAT_LEN		EQU 0x19 ;# Length 1..16
;---------------------------------------------------------------
PAT_BPM_H	EQU 0x1A ;# BPM H
PAT_BPM_L	EQU 0x1B ;# BPM L
;---------------------------------------------------------------
PAT_POS		EQU 0x1C ;# Pos 1..16
PAT_PLAYPOS	EQU 0x1D ;# Pos 1..16
PAT_TMP		EQU 0x1E
;---------------------------------------------------------------
PAT_PIT		EQU 0x20 ;# Pitch Array (00..0F)
PAT_PIT_0	EQU 0	 ;# Pitch Bit 0
PAT_PIT_1	EQU 1	 ;# Pitch Bit 1
PAT_PIT_2	EQU 2 	 ;# Pitch Bit 2
PAT_PIT_3	EQU 3 	 ;# Pitch Bit 3
PAT_PIT_DN	EQU 4	 ;# Down
PAT_PIT_UP	EQU 5    ;# Up
PAT_PIT_AC	EQU 6    ;# Accent
PAT_PIT_SL	EQU 7    ;# Slide
;---------------------------------------------------------------
PAT_TME		EQU 0x30 ;# Time Array (00..0F)
PAT_TME_BL	EQU 0	 ;# Black
PAT_TME_WT	EQU 1	 ;# White
;---------------------------------------------------------------

;###############################################################
;# VAR Song
;###############################################################
;---------------------------------------------------------------
SNG_TXT		EQU 0x40 ;# Text Array (00..07)
;---------------------------------------------------------------
SNG_NUM		EQU 0x48 ;# Number 0..127
;---------------------------------------------------------------
SNG_LEN		EQU 0x49 ;# Length 1..64
;---------------------------------------------------------------
SNG_BPM_H	EQU 0x4A ;# BPM H
SNG_BPM_L	EQU 0x4B ;# BPM L
;---------------------------------------------------------------
SNG_POS		EQU 0x4C ;# Pos 1..64
;---------------------------------------------------------------
SNG_PAT		EQU 0x50 ;# Pattern Array (00..0F)
;---------------------------------------------------------------

;###############################################################
;# VAR Midi
;###############################################################
;---------------------------------------------------------------
MIDI_CHN	EQU 0x60 ;# Channel
;---------------------------------------------------------------
MIDI_MODE	EQU 0x62 ;# Midi Mode
			 ;# 0 = MASTER-SEQ
			 ;# 1 = SLAVE-SEQ
			 ;# 2 = KEY-IN
			 ;# 3 = KEY-OUT
			 ;# 4 = KEY-OUT+SILENT
;---------------------------------------------------------------
MIDI_BUF0	EQU 0x63
MIDI_BUF1	EQU 0x64 
MIDI_BUF2	EQU 0x65 ;# Midi Buffer
MIDI_BUF3	EQU 0x66
;---------------------------------------------------------------

;###############################################################
;# VAR Key Controller
;###############################################################
;---------------------------------------------------------------
DATABUS			EQU PORTD
;---------------------------------------------------------------

;###############################################################
;# VAR LED Controller
;###############################################################
;---------------------------------------------------------------
LEDBUS			EQU PORTE
LEDBUS_A_OUT 	EQU 0 
LEDBUS_B_OUT 	EQU 1 
LEDBUS_C_OUT 	EQU 2 
;---------------------------------------------------------------
LED_REG_0		EQU 0x070
LED_REG_N4		EQU 0x070
LED_REG_N12		EQU 0x070
LED_N4			EQU 0
LED_N12			EQU 1

LED_REG_1		EQU 0x071
LED_REG_N3		EQU 0x071
LED_REG_N11		EQU 0x071
LED_N3			EQU 0
LED_N11			EQU 1

LED_REG_2		EQU 0x072
LED_REG_N2		EQU 0x072
LED_REG_N10		EQU 0x072
LED_REG_TIME	EQU 0x072
LED_N2			EQU 0
LED_N10			EQU 1
LED_TIME		EQU 2

LED_REG_3		EQU 0x073
LED_REG_N1		EQU 0x073
LED_REG_N9		EQU 0x073
LED_REG_SLIDE	EQU 0x073
LED_N1			EQU 0
LED_N9			EQU 1
LED_SLIDE		EQU 2

LED_REG_4		EQU 0x074
LED_REG_FUNC	EQU 0x074
LED_REG_N8		EQU 0x074
LED_REG_ACCENT	EQU 0x074
LED_FUNC		EQU 0
LED_N8			EQU 1
LED_ACCENT		EQU 2

LED_REG_5		EQU 0x075
LED_REG_PITCH	EQU 0x075
LED_REG_N7		EQU 0x075
LED_REG_UP		EQU 0x075
LED_PITCH		EQU 0
LED_N7			EQU 1
LED_UP			EQU 2

LED_REG_6		EQU 0x076
LED_REG_RUN		EQU 0x076
LED_REG_N6		EQU 0x076
LED_REG_DOWN	EQU 0x076
LED_RUN			EQU 0
LED_N6			EQU 1
LED_DOWN		EQU 2

LED_REG_7		EQU 0x077
LED_REG_N5		EQU 0x077
LED_REG_N13		EQU 0x077
LED_N5			EQU 1
LED_N13			EQU 2

LED_REG_BLACK	EQU 0x078
LED_REG_WHITE	EQU 0x078
LED_REG_PAUSE	EQU 0x078

LED_BLACK		EQU 0
LED_WHITE		EQU 1
LED_PAUSE		EQU 2

LED_COUNT		EQU 0x079
LED_TMP			EQU 0x07A
;---------------------------------------------------------------

;###############################################################
;# VAR VCO
;###############################################################
VCOBUS        	EQU PORTB

PORT_SLIDE		EQU PORTB
PORT_ACCENT		EQU PORTB

SLIDE	 		EQU 7
ACCENT 			EQU 6

PORT_GATE		EQU PORTA
GATE   			EQU 5

;###############################################################
;# VAR LCD
;###############################################################
;---------------------------------------------------------------
LCD_D4_PORT	EQU PORTB
LCD_D4		EQU	0
LCD_D5_PORT	EQU PORTB
LCD_D5		EQU 1
LCD_D6_PORT	EQU PORTB
LCD_D6		EQU 2
LCD_D7_PORT	EQU PORTB
LCD_D7		EQU 3
;---------------------------------------------------------------
LCD_RS_PORT	EQU PORTB
LCD_RS		EQU 4
;---------------------------------------------------------------
LCD_E_PORT	EQU PORTA
LCD_E		EQU 3 
;---------------------------------------------------------------
LCD_DELAY_L	EQU 0x80
LCD_DELAY_H	EQU 0x81
LCD_DELAY_Z	EQU 0x82
;---------------------------------------------------------------
LCD_TMP		EQU 0x83
;---------------------------------------------------------------
LCD_TXT_CTR EQU 0x84
;---------------------------------------------------------------

;###############################################################
;# VAR LCD
;###############################################################
KEYBUS				EQU PORTA
KEYBUS_A_IN 		EQU 0 
KEYBUS_B_IN 		EQU 1 
KEYBUS_C_IN	 		EQU 2 

KEYPRESS			EQU 0x090
LAST_KEYPRESS		EQU 0x091
IRQ_KEYPRESS		EQU 0x092
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

;###############################################################
;# VAR TEMP / DIV
;###############################################################
COUNTER		EQU 0xA0
IRQ_TMP		EQU 0xA1
STATUS_TMP	EQU 0xA2
BSR_TMP		EQU 0xA3
TMP			EQU 0xA4
BPM_COUNT_H EQU 0xA5
BPM_COUNT_L EQU 0xA6
CHARPOS		EQU 0xA7
BPM_DIVIDER EQU 0xA8
BPM_BEAT24	EQU 0xA9
BCD_Count	EQU 0xAA
BCD_Temp	EQU 0xAB
BCD_R0		EQU 0xAC
BCD_R1		EQU 0xAD
VCO_TMP		EQU 0xAE
IRQEVENT_TICK EQU 0xAF
