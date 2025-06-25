
TABLE_ADDR MACRO addr
        movlw   ((addr) & 0xff) ; store Lo Byte
        movwf   TBLPTRL
        movlw   ((addr) >> 8)   ; store Hi Byte
        movwf   TBLPTRH
        ENDM

