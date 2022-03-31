#include "globals.h"

; Tx 时钟设置为1MHz
TxClock:           
	MOV.B           #(0xA5), &CSCTL0_H ;
#define __TMPSYM DCORSEL | DCOFSEL_4
	MOV.W #__TMPSYM, &CSCTL1 ;
#undef __TMPSYM
#define __TMPSYM SELA_1 | SELM_3
	MOV.W #__TMPSYM, &CSCTL2     ;
#undef __TMPSYM
	BIS.W           #(SELS_3), &CSCTL2
#define __TMPSYM DIVA_0 |DIVS_0 | DIVM_0
	MOV.W #__TMPSYM, &CSCTL3 ;
#undef __TMPSYM
#define __TMPSYM MODCLKREQEN|SMCLKREQEN|MCLKREQEN
	BIC.W #__TMPSYM, &CSCTL6
#undef __TMPSYM
	BIS.W			#(ACLKREQEN), &CSCTL6
	RETA


; Rx 时钟设为 16MHz
RxClock:
    MOV.B           #(0xA5), &CSCTL0_H ;[] Switch to corr Rx frequency  16MHz
    ; DCO 设置为 16MHz
    MOV.W           #(DCORSEL|DCOFSEL_4), &CSCTL1 ;

    MOV.W           #(SELA_1|SELM_3), &CSCTL2     ;
    BIS.W           #(SELS_3), &CSCTL2
    ; divider 全部设置成 1
    MOV.W           #(DIVA_0|DIVS_0|DIVM_0), &CSCTL3 ;
    BIC.W           #(MODCLKREQEN|SMCLKREQEN|MCLKREQEN), &CSCTL6
    BIS.W           #(ACLKREQEN), &CSCTL6

    RETA

    .end
