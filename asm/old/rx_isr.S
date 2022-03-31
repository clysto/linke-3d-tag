;/************************************************************************************************************************************
;*                                           PORT 1 ISR (Starting a Command Receive)
;*   Here starts the hard real time stuff.
;*   MCLK is 16 MHz (See Clocking.asm) -> 0.0625 us per cycle
;*   Entering ISR takes 6 cycles (4.5.1.5.1) + Time needed to wake up from LPM1 (~4 us)
;*   Each BIT.B takes 5-1 cycles (4.5.1.5.4)
;*   Each JNZ or JZ takes 2 cycles regardless whether it is taken or not (4.5.1.5.3)
;*   Start this ISR at t = 0.375 us + wake up time (~1.5 us?) TODO: Find out  this exact wakeup time or why we have this gap.
;*   Listed instruction cycles are taken from MSP430FR5969 User Guide (SLAU367F).
;*
;*   Purpose:
;*   This ISR kicks in on a falling edge and tries to find the rising edge marking the end of the delimiter of a PREAMBLE/FRAME-SYNC.
;*   After that, we disable PORT1 interrupts and setup Timer0A0.
;*   In the worst case (readers with 6.25 Tari), we only have 0.475*6.25 us = 47 clock cycles) before the falling edge of data-0.
;*   Then we quickly return from this interrupt and wait for Timer0A0 to wake us up on the data-0 falling edge.
;*   An ASCII drawing of the situation can be found below:
;*
;*   |   data-0  |           RTCAL             |
;*   /-----\_____/------------------------\____/   - Wave form
;*
;*************************************************************************************************************************************

#include "globals.h"
#include "LedUtils.asm"

RX_ISR:
    BIT.B	    #PIN_RX,	&PRXIN		;[4]
    JNZ         badDelim				;[2]
    BIT.B	    #PIN_RX,	&PRXIN		;[4]
    JNZ         badDelim				;[2]
    BIT.B       #PIN_RX,	&PRXIN		;[4]
    JNZ         badDelim				;[2]

	;*********************************************************************************************************************************
	; JUST RIGHT (Around 10 us)
	;*********************************************************************************************************************************
	BIT.B	#PIN_RX,	&PRXIN		;[4]
	JNZ		goodDelim				;[2]
	BIT.B	#PIN_RX,	&PRXIN		;[4]
	JNZ		goodDelim				;[2]
	BIT.B	#PIN_RX,	&PRXIN		;[4]
	JNZ		goodDelim				;[2]
	BIT.B	#PIN_RX,	&PRXIN		;[4]
	JNZ		goodDelim				;[2]
	BIT.B	#PIN_RX,	&PRXIN		;[4]
	JNZ		goodDelim
	BIT.B	#PIN_RX,	&PRXIN		;[4]
	JNZ		goodDelim
	BIT.B	#PIN_RX,	&PRXIN		;[4]
	JNZ		goodDelim
	BIT.B	#PIN_RX,	&PRXIN		;[4]
	JNZ		goodDelim
	BIT.B	#PIN_RX,	&PRXIN		;[4]
	JNZ		goodDelim
	BIT.B	#PIN_RX,	&PRXIN		;[4]
	JNZ		goodDelim

	BIT.B	#PIN_RX,	&PRXIN		;[4]
	JNZ		goodDelim				;[2]
	BIT.B	#PIN_RX,	&PRXIN		;[4]
	JNZ		goodDelim				;[2]
	BIT.B	#PIN_RX,	&PRXIN		;[4]
	JNZ		goodDelim				;[2]
	BIT.B	#PIN_RX,	&PRXIN		;[4]
	JNZ		goodDelim				;[2]
	BIT.B	#PIN_RX,	&PRXIN		;[4]
	JNZ		goodDelim				;[2]
	BIT.B	#PIN_RX,	&PRXIN		;[4]
	JNZ		goodDelim				;[2]
	BIT.B	#PIN_RX,	&PRXIN		;[4]
	JNZ		goodDelim				;[2]
	BIT.B	#PIN_RX,	&PRXIN		;[4]
	JNZ		goodDelim
	BIT.B	#PIN_RX,	&PRXIN		;[4]
	JNZ		goodDelim

; Delim is too short so go back to sleep.
badDelim:
	;calla	#toggleLED2
;	XOR.B   #PIN_AUX3,	&PIN_AUX3_OUT
	BIC.W	#(CCIE),&TA0CCTL0		; Disable timer interrupt to avoid entering lpm1 instead of lpm4.
	CLR		&TA0CTL					;[] Disable TimerA since we should again look for the next delim and stay in lpm4
	BIT.B   R15, R14                                    ;[]
	BIC     #CCIFG, &TA0CCTL0                           ;[] Clear the interrupt flag for Timer0A0 Compare (safety).
	CLR     &TA0R                                       ;[] Reset TAR value
	CLR     &(RXData.edge_capture_prev_ccr)               ;[] Clear previous value of CCR capture.
	CLR.B   &PRXIFG                                     ;[] Clear the Port 1 flag.
	OR.B 	#BIT7,	&P2IE
	AND.B 	#0x7F,	&PTXOUT
	MOV.B	#PIN_RX,	&PRXIE

	RETI

tooEarly:
	jmp		badDelim

; We found a delim ~12.5 us, now turn off PORT1 and prepare Timer0A0.
goodDelim:                                              ;[24]
	;TOGGLE_LED2
	;XOR.B   #PIN_TX, &PTXOUT
	BIS.B   #PIN_RX, &PRXSEL0                           ;[5] Enable Timer0A0
	BIC.B   #PIN_RX, &PRXSEL1                           ;[5] Enable Timer0A0
	CLR.B   &PRXIE                                      ;[4] Disable the Port 1 Interrupt
	BIC #(SCG1), 0(R1)                              ;[5] Enable the DCO to start counting
#define __TMPSYM CM_2+CCIE
	BIS.W #__TMPSYM, &TA0CCTL0                     ;[5] Wake up so we can make use of Timer0A0 control registers?
#undef __TMPSYM
#define __TMPSYM TASSEL__SMCLK+MC__CONTINOUS
	MOV #__TMPSYM, &TA0CTL 		;[] SMCLK and continuous mode.  (TASSEL1 + MC1), now timer0A0 can be started
#undef __TMPSYM

startupT0A0_ISR:                                        ;[22]
	BIC     #CCIFG, &TA0CCTL0                           ;[5] Clear the interrupt flag for Timer0A0 Compare
	CLR     &TA0R                                       ;[4] ***Reset clock!***
	CLR     &(RXData.edge_capture_prev_ccr)               ;[4] Clear previous value of CCR capture
	CLR.B   &PRXIFG                                     ;[4] Clear the Port 1 flag.

	;calla 	#toggleLED2
	; CALLA	#SendTo				                    	;[5] call the routine
	;AND.B 	#0x7F,	&PTXOUT
	; MOV.B	#PIN_RX,	&PRXIE

	RETI                                                ;[5] Return from interrupt (46 cycles total).

;*************************************************************************************************************************************
; DEFINE THE INTERRUPT VECTOR ASSIGNMENT
;*************************************************************************************************************************************
	;.sect ".int36"                                     ; Port 1 Vector
	;.short  RX_ISR                                     ; This sect/short pair sets int02 = RX_ISR addr.
	.end
