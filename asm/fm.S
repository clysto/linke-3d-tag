#include <msp430.h>
#include "nopn.asm"


#define R_tsIdx     R7
#define R_inloopCt  R8
#define R_cycleCt   R9
#define R_zero      R10
#define R_currByte  R11
#define R_pulseCt   R12
#define R_dataPtr   R13
#define R_byteCt    R14
#define R_loopCt    R15
; 发射天线连接到 P2.7
#define TX_PIN      BIT7
#define TX_OUT      P2OUT

.global TX_FM

;==============================================================================
;
;   725khz 频移
;
;==============================================================================

TX_FM:
    MOV.B       #0x00,          R_zero
    MOV.B       #0x02,          R_tsIdx
    MOV.B       R_zero,         R_currByte

    ; 循环发送字节 (MSB对齐)
SEND_BYTE:
    MOV.B       @R_dataPtr+,    R_currByte

;==============================================================================
;   发送 BIT0
;==============================================================================
    MOV.B       R_pulseCt,      R_loopCt
B0_LOOP:
    MOV.B       R_currByte,     &TX_OUT
    NOPN        7
    MOV.B       R_zero,         &TX_OUT    
    NOPN        3
    DEC.B       R_loopCt
    JNZ         B0_LOOP

;==============================================================================
;   发送 BIT1
;==============================================================================
    RLA.B       R_currByte
    MOV.B       R_pulseCt,      R_loopCt
B1_LOOP:
    MOV.B       R_currByte,     &TX_OUT
    NOPN        7
    MOV.B       R_zero,         &TX_OUT
    NOPN        3
    DEC.B       R_loopCt
    JNZ         B1_LOOP

;==============================================================================
;   发送 BIT2
;==============================================================================
    RLA.B       R_currByte
    MOV.B       R_pulseCt,      R_loopCt
B2_LOOP:
    MOV.B       R_currByte,     &TX_OUT
    NOPN        7
    MOV.B       R_zero,         &TX_OUT
    NOPN        3
    DEC.B       R_loopCt
    JNZ         B2_LOOP

;==============================================================================
;   发送 BIT3
;==============================================================================
    RLA.B       R_currByte
    MOV.B       R_pulseCt,      R_loopCt
B3_LOOP:
    MOV.B       R_currByte,     &TX_OUT
    NOPN        7
    MOV.B       R_zero,         &TX_OUT
    NOPN        3
    DEC.B       R_loopCt
    JNZ         B3_LOOP

;==============================================================================
;   发送 BIT4
;==============================================================================
    RLA.B       R_currByte
    MOV.B       R_pulseCt,      R_loopCt
B4_LOOP:
    MOV.B       R_currByte,     &TX_OUT
    NOPN        7
    MOV.B       R_zero,         &TX_OUT
    NOPN        3
    DEC.B       R_loopCt

    JNZ         B4_LOOP

;==============================================================================
;   发送 BIT5
;==============================================================================
    RLA.B       R_currByte
    MOV.B       R_pulseCt,      R_loopCt
B5_LOOP:
    MOV.B       R_currByte,     &TX_OUT
    NOPN        7
    MOV.B       R_zero,         &TX_OUT
    NOPN        3
    DEC.B       R_loopCt
    JNZ         B5_LOOP

;==============================================================================
;   发送 BIT6
;==============================================================================
    RLA.B       R_currByte
    MOV.B       R_pulseCt,      R_loopCt
B6_LOOP:
    MOV.B       R_currByte,     &TX_OUT
    NOPN        7
    MOV.B       R_zero,         &TX_OUT
    NOPN        3
    DEC.B       R_loopCt
    JNZ         B6_LOOP

;==============================================================================
;   发送 BIT7
;==============================================================================
    RLA.B       R_currByte
    MOV.B       R_pulseCt,      R_loopCt
B7_LOOP:
    MOV.B       R_currByte,     &TX_OUT
    NOPN        7
    MOV.B       R_zero,         &TX_OUT
    NOPN        3
    DEC.B       R_loopCt
    JNZ         B7_LOOP

B7_T:
    DEC.B       R_byteCt
    ; 如果没有发送完成继续发送下一个字节
    JNZ         SEND_BYTE
    MOV.B       R_zero,         &TX_OUT
    RETA

.end
