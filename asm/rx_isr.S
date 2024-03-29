#include <msp430.h>
#include "nopn.asm"


#define R_cycleCt   R9
#define R_currByte  R11
#define R_pulseCt   R12
#define R_dataPtr   R13	
#define R_byteCt    R14	
#define R_loopCt    R15
; 接收天线连接到 P2.3
#define RX_PIN      BIT3
#define RX_IN       P2IN
#define	RX_IFG      P2IFG

.global RX_ISR
      
RX_ISR:
    ; 打开 LED 灯
    BIS.B       #0x01,          &P4OUT

    MOV         #0xFFFF,        R5
WAIT:
    DEC         R5
    JNZ         WAIT

    ; 调用 beforeSend 钩子函数
    CALLA       #COMM_beforeSend

    MOV         #BITSTREAM,     R_dataPtr
    MOV.B       #74,            R_byteCt
    MOV.B       #2,             R_cycleCt
    MOV.B       #30,            R_pulseCt
    CALLA       #TX_FM

    ; 关闭 LED 灯
    BIC.B       #0x01,          &P4OUT

    ; 清除中断标记位
    CLR.B       &RX_IFG
    RETI


.end
