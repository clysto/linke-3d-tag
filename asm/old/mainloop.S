#include "globals.h"

; 保留寄存器, 不能随意更改
#define R_bitCt         R6
#define R_bits          R5
#define R_dest          R4
#define R_wakeupBits    R10
#define R_scratch0      R15

.global MegaScatter_Start, RxClock, handleRead, HandleSetLed

; 主循环
ResetAndSleep:
    ; 初始化 megascatter
    ; 关闭 abort 开关
    MOV.B   #FALSE, &(RXData.abortFlag)

    ; ===================
    ; SET TO FASTER CLOCK
    ; ===================

    ; 禁止中断
    DINT
    NOP
    ; 设置 Rx 时钟
    CALLA   #RxClock

    ; ===================================
    ; CONFIG, ENABLE The RX State Machine
    ; ===================================

    ; 天线端口配置
    BIC.B 	#PIN_RX, &PRXSEL0
    BIC.B 	#PIN_RX, &PRXSEL1

    ; 配置时钟 A0
    CLR     &TA0CTL				;[] Disable TimerA before config (required)
    CLR     &TA0R				;[] Clear Ctr
    CLR     &(RXData.edge_capture_prev_ccr) ;[] Clear previous value of CCR capture
    MOV     #0xFFFF, &TA0CCR1	;[] Don't let timer0A1 overflow!
    CLR     &TA0CCTL1			;[] Don't do the overflow, yet on T0A1
    CLR		&TA0CCTL0
#define __TMPSYM SCS+CAP+CCIS_1
    MOV #__TMPSYM, &TA0CCTL0	;[] Sync on Cap Src and Cap Mode on Rising Edge(Inverted). don't set all bits until in RX ISR though.
#undef __TMPSYM

    ; Setup rfid_rxSM vars
    MOV     #RESET_BITS_VAL, R_bits  ;[]MOD
    CLR     R_bitCt                  ;[]
    MOV     #(cmd), R_dest           ;[]load the R_dest to the reg!


    ;RX State Machine Config (setup PRX for falling edge interrupt on PRX.PIN_RX)
    BIS.B   #(PIN_RX_EN), &PDIR_RX_EN	;[]@us_change: config I/O here and quit after use
    BIS.B	#PIN_RX_EN, &PRXEOUT	;[] Enable the Receive Comparator

    BIS.B	#PIN_RX,	&PRXIES		;[] Make falling edge for port interrupt to detect start of delimiter
    CLR.B	&PRXIFG					;[] Clear interrupt flag
    MOV.B	#PIN_RX,	&PRXIE		;[] Enable Port2 interrupt

    ; Set up timeout timer
    ; @Jinhao Fan: This is used for error recovery.
    ; e.g. The tag encountered some error receiving data, causing a DEADLOCK.
    MOV     #CCIE,      TA1CCTL0 ; CCR0 interrupt enabled
    MOV     #QUERY_TIMEOUT_PERIOD, TA1CCR0 ; Timeout period
#define __TMPSYM TASSEL_1 | MC_1 | TACLR
    MOV #__TMPSYM, TA1CTL ; ACLK, upmode, divide by 8, clear TAR
#undef __TMPSYM

    NOP
#define __TMPSYM #LPM4_bits+GIE
    BIS     __TMPSYM, SR			;[] sleep! (LPM4 | GIE) It won't wakeup until either 8bits came in, or QR occurs, or timeout occurs.
#undef __TMPSYM
    NOP
    ;MOV.B 	#PIN_TX, &(PTXOUT)




    ; Somehow woke up ...

    ; Check to see if timeout was what (probably) woke us
    TST.B   RXData.abortFlag
    JNZ endDoRFID

; DECODE COMMAND

decodeCmd_lvl1:

    ;calla	#toggleLED2
    MOV.B   &(cmd), R_scratch0  ;[] bring in cmd[0] to parse
    AND.B   #0x0F,  R_scratch0  ;[] just compare the first four bits

    CMP.B   #0x01,  R_scratch0
    ; Right now, it must be SetLed command
    JEQ     callSetLedHandler

    CMP.B	#0x00,	R_scratch0
    JEQ		callReadHandler

    JMP 	endDoRFID

callReadHandler:
    calla 	#handleRead
    JMP		endDoRFID

callSetLedHandler:

    calla 	#handleSetLed

    JMP		endDoRFID

;/************************************************************************************************************************************/
;/                                      DECIDE IF STAYING IN RFID LOOP                                                               *
;/                                                                                                                                   *
;/ If the abort flag has been set during the RFID transaction, return! Otherwise, keep doing RFID.                                   *
;/************************************************************************************************************************************/
endDoRFID:
    ; Disable timeout timer

    MOV #0, TA1CCTL0;
    MOV #0, TA1CTL;

    TST.B   &(RXData.abortFlag)
    JMP      ResetAndSleep

    MOV     #(0), &(TA0CCTL0)
    RETA


    .end
