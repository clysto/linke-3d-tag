#include <msp430.h>

; 接收天线连接到 P2.3
#define RX_PIN  BIT3
#define RX_IN   P2IN

.global RX_ISR

RX_ISR:
    BIS.B       #0x01,      &P4OUT
    BIT.B       #RX_PIN,    &RX_IN
    JNZ         BAD_DELIM
    BIT.B       #RX_PIN,    &RX_IN
    JNZ         BAD_DELIM
    BIT.B       #RX_PIN,    &RX_IN
    JNZ         BAD_DELIM
    RETI

BAD_DELIM:
    RETI

.end
