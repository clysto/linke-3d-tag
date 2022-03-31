#ifndef GLOBALS_H
#define GLOBALS_H

#include <msp430.h>

/*
 * Port 1
 */

// P1.0 - RX_BITLINE INPUT
#define PIN_RX_BITLINE		(BIT0)
#define PRX_BITLINEOUT 		(P1OUT)

// P1.4 - AUX3 -  INPUT/OUTPUT
#define		PIN_AUX3			(BIT4)
#define 	PIN_AUX3_OUT		(P1OUT)
#define 	PAUX3IN				(P1IN)
#define 	PDIR_AUX3			(P1DIR)
#define		PAUX3SEL0			(P1SEL0)
#define		PAUX3SEL1			(P1SEL1)

// P1.6 - I2C_SDA -  INPUT/OUTPUT
#define		PIN_I2C_SDA				(BIT6)
#define 	PI2C_SDAIN				(P1IN)
#define 	PDIR_I2C_SDA			(P1DIR)
#define		PI2C_SDASEL0			(P1SEL0)
#define		PI2C_SDASEL1			(P1SEL1)

// P1.7 - I2C_SCL -  INPUT/OUTPUT
#define		PIN_I2C_SCL				(BIT7)
#define 	PDIR_I2C_SCL			(P1DIR)
#define		PI2C_SCLSEL0			(P1SEL0)
#define		PI2C_SCLSEL1			(P1SEL1)

/*
 * Port 2
 */

// P2.0 - UART TX - OUTPUT
#define		PIN_UART_TX				(BIT0)
#define		PUART_TXSEL0			(P2SEL0)
#define		PUART_TXSEL1			(P2SEL1)

// P2.1 - UART RX - INPUT
#define		PIN_UART_RX				(BIT1)
#define		PUART_RXSEL0			(P2SEL0)
#define		PUART_RXSEL1			(P2SEL1)

// P2.3 - RECEIVE - INPUT
#define		PIN_RX			(BIT3)
#define 	PRXIN			(P2IN)
#define 	PDIR_RX			(P2DIR)
#define		PRXIES			(P2IES)
#define		PRXIE			(P2IE)
#define		PRXIFG			(P2IFG)
#define		PRXSEL0			(P2SEL0)
#define		PRXSEL1			(P2SEL1)
#define 	PRX_VECTOR_DEF	(PORT2_VECTOR)

// P2.4 - ACCEL_SCLK - OUTPUT
#define 	PIN_ACCEL_SCLK			(BIT4)
#define 	PDIR_ACCEL_SCLK			(P2DIR)
#define		PACCEL_SCLKSEL0			(P2SEL0)
#define		PACCEL_SCLKSEL1			(P2SEL1)

// P2.5 - ACCEL_MOSI - OUTPUT
#define 	PIN_ACCEL_MOSI			(BIT5)
#define 	PDIR_ACCEL_MOSI			(P2DIR)
#define		PACCEL_MOSISEL0			(P2SEL0)
#define		PACCEL_MOSISEL1			(P2SEL1)


// P2.6 - ACCEL_MISO - INPUT
#define 	PIN_ACCEL_MISO			(BIT6)
#define 	PDIR_ACCEL_MISO			(P2DIR)
#define		PACCEL_MISOSEL0			(P2SEL0)
#define		PACCEL_MISOSEL1			(P2SEL1)


// P2.7- TRANSMIT - OUTPUT
#define		PIN_TX			(BIT7)
#define 	PTXOUT			(P2OUT)
#define		PTXDIR			(P2DIR)

/*
 * Port 3
 */

// P3.4 - AUX1 -  INPUT/OUTPUT
#define		PIN_AUX1			(BIT4)
#define 	PAUX1IN				(P3IN)
#define 	PDIR_AUX1			(P3DIR)
#define		PAUX1SEL0			(P3SEL0)
#define		PAUX1SEL1			(P3SEL1)

// P3.5 - AUX2 -  INPUT/OUTPUT
#define		PIN_AUX2			(BIT5)
#define 	PAUX2IN				(P3IN)
#define 	PDIR_AUX2			(P3DIR)
#define		PAUX2SEL0			(P3SEL0)
#define		PAUX2SEL1			(P3SEL1)

// P3.6 - ACCEL_INT2 - INPUT
#define 	PIN_ACCEL_INT2			(BIT6)
#define 	PDIR_ACCEL_INT2			(P3DIR)
#define		PACCEL_INT2SEL0			(P3SEL0)
#define		PACCEL_INT2SEL1			(P3SEL1)

// P3.7 - ACCEL_INT1 - INPUT
#define 	PIN_ACCEL_INT1			(BIT7)
#define 	PDIR_ACCEL_INT1			(P3DIR)
#define		PACCEL_INT1SEL0			(P3SEL0)
#define		PACCEL_INT1SEL1			(P3SEL1)

/*
 * Port 4
 */

// P4.0 - LED1 OUTPUT
#define		PLED1OUT			(P4OUT)
#define 	PIN_LED1			(BIT0)
#define 	PDIR_LED1			(P4DIR)

// P4.1 MEAS INPUT
#define 	PIN_MEAS			(BIT1)
#define		PMEASOUT			(P4OUT)
#define		PMEASDIR			(P4DIR)
#define		PMEASSEL0			(P4SEL0)
#define		PMEASSEL1			(P4SEL1)

// P4.2 - ACCEL_EN - OUTPUT
#define PIN_ACCEL_EN		BIT2
#define POUT_ACCEL_EN		P4OUT
#define PDIR_ACCEL_EN		P4DIR

// P4.3 - ACCEL_CS - OUTPUT
#define PIN_ACCEL_CS		BIT3
#define POUT_ACCEL_CS		P4OUT
#define PDIR_ACCEL_CS		P4DIR

// P2.7 - RECEIVE ENABLE - OUTPUT
#define     PIN_RX_EN       (BIT5)
#define     PRXEOUT         (P4OUT)
#define     PDIR_RX_EN      (P4DIR)


// P4.6 - DEBUG LINE - OUTPUT
#define     PIN_DBG0        (BIT6)
#define     PDBGOUT         (P4OUT)

/*
 * Port 5
 */

/*
 * Port 6
 */

/*
 * Port J
 */

// PJ.1 MEAS_EN (OUTPUT)
#define		PMEAS_ENOUT			(PJOUT)
#define		PMEAS_ENDIR			(PJDIR)
#define 	PIN_MEAS_EN			(BIT1)


// PJ.6 - LED2
#define 	PDIR_LED2			(PJDIR)
#define		PLED2OUT			(PJOUT)
#define 	PIN_LED2			(BIT6)

/*
 * ADC Channel definitions
 */

/**
 * Default IO setup
 */
/** @todo: Default for unused pins should be output, not tristate.  */
/** @todo:  Make sure the Tx port pin should be tristate not output and unused pin to be output*/
// Set as many as possible pins to output and drive them low
#ifndef __ASSEMBLER__
#define setupDflt_IO() \
    P1OUT = 0x00;\
    P2OUT = 0x00;\
    P3OUT = 0x00;\
    P4OUT = 0xFE;\
    PJOUT = 0x00;\
    P1DIR = 0xFF;\
    PJDIR = 0xFF;\
    P2DIR = 0x80;\
    P3DIR = 0xFF;\
    P4DIR = (0xFF);\

#define OPEN_RX P1DIR = 0x01
#define CLOSE_RX P1DIR = 0xFF

#endif /* ~__ASSEMBLER__ */

/* SetLed related options */
#define LED1 (0x00)
#define LED2 (0x03)
#define TURN_ON (0x03)
#define TURN_OFF (0x00)

/* Global constants */
#define FOREVER (1)
#define NEVER (0)

#define TRUE (1)
#define FALSE (0)

#define HIGH (1)
#define LOW (0)

#define FAIL (0)
#define SUCCESS (1)

/** @todo write the comments for 4 below so I can actually read them... */
#define EPC_WORDS (6) /* length of EPC value in words, 0 <= n <= 31 */

#define CMDBUFF_SIZE (30) /* ? */
#define DATABUFF_SIZE     \
  (2 + (EPC_WORDS << 1) + \
   2) /* first2/last2 are reserved. put data into B2..B13     */
      /*      format: [storedPC|EPC|CRC16]                    */
#define RFIDBUFF_SIZE \
  (1 + 16 + 2 + 2 +   \
   50) /* longest command handled is the read command for 8 wds*/

#define USRBANK_SIZE (32) /* ? */

#define RFID_SEED \
  (0x1234)  // change this to change the RN16 selection behavior. if using
            // multiple tags make sure to put a different value on each one!!
            // /** @todo: maybe have this generated in INFO Mems during cal*/

#define CMD_PARSE_AS_QUERY_REP \
  (0x00) /** @todo   describe these myst vals!                   */
#define CMD_PARSE_AS_OVF (0xFF)
#define ENOUGH_BITS_TO_FORCE_EXECUTION (200)

#define RESET_BITS_VAL                                                    \
  (-2) /* this is the value which will reset the TA1_SM if found in 'bits \
          (R5)' by rfid_sm         */

// RFID TIMINGS (Taken a bit more liberately to support both R420 and R1000).
#define RTCAL_MIN \
  (400)  // strictly calculated it should be 2.5*TARI = 2.5*10 = 25 us = 400
         // cycles
#define RTCAL_MAX (560)  // 3.5*TARI = 3.5*10 = 35 us = 560 cycles
#define TRCAL_MIN \
  (220)  // We don't have time to do a MUL instruction, so we do 1.1*RTCAL_MIN
         // instead of 1.1*RTCAL.
#define TRCAL_MAX \
  (900)  // We don't have time to do a MUL instruction, so we do 3*RTCAL_MAX
         // instead of 3*RTCAL.

// TIMING----------------------------------------------------------------------------------------------------------------------------//
// Goal is 56.125/62.500/68.875us. Trying to shoot for the lower to save (a
// little) power. Note: 1 is minVal here due to the way decrement timing loop
// works. 0 will act like (0xFFFF+1)!
#define TX_TIMING_QUERY \
  (24) /*53.5-60us (depends on which Q value is loaded). */
#define TX_TIMING_ACK (20) /*60.0us*/  //(14,58.6us)

#define TX_TIMING_QR (52)     // 58.8us
#define TX_TIMING_QA (48)     // 60.0us
#define TX_TIMING_REQRN (33)  // 60.4us
#define TX_TIMING_READ (29)   // 58.0us
#define TX_TIMING_WRITE (31)  // 60.4us

#define QUERY_TIMEOUT_PERIOD (65535)

// PROTOCOL
// DEFS---------------------------------------------------------------------------------------------------------------------//
//(if # is rounded to 8 that is so  cmd[n] was finished being shifted in)
#define NUM_SETLED_BITS (18)
#define NUM_SEL_BITS                                                        \
  (48) /* only need to parse through mask: (4+3+3+2+8+8+16 = 44 -> round to \
          48)                        */
#define NUM_QUERY_BITS (22)
#define NUM_ACK_BITS (18)
#define NUM_REQRN_BITS (40)
#define NUM_WRITE_BITS (66)

#define EPC_LENGTH \
  (EPC_WORDS) /* 10h..14h EPC Length in Words. (6 is 96bit std) */
#define UMI                                                                   \
  (0x01) /* 15h      User-Memory Indicator. '1' means the tag has user memory \
            available. */
#define XI                                                                     \
  (0x00) /* 16h      XPC_W1 indicator. '0' means the tag does not support this \
            feature.  */
#define NSI (0x00) /* 17h..1Fh Numbering System Identifier. */
/*          all zeros means it isn't supported and is recommended default */

#define TREXT_ON (1)  /* Tag should use TRext format for backscatter  */
#define TREXT_OFF (0) /* Tag shouldn't use TRext format for backscatter */
#define WRITE_DATA_BLINK_LED (0x00)
#define WRITE_DATA_NEW_ID (0x01)

#ifndef __ASSEMBLER__
#include <stdint.h> /* use xintx_t good var defs (e.g. uint8_t)             */

// TYPEDEFS------------------------------------------------------------------------------------------------------------------------

// Boolean type
typedef uint8_t BOOL;

// THE RECIEVER STRUCT FOR RECIEVE CONTROL
typedef struct {
  // the data to be send
  uint8_t *dataPtr;
  // the length of data to be send
  uint8_t byteCount;
  // cycles count
  uint8_t cyclesCt;
  // pulse  count
  uint8_t pulseCt;
} TXstruct;
// THE RW STRUCT FOR ACCESS STATE VARS

typedef struct {
  // Parsed Cmd Fields
  uint8_t memBank; /* for Rd/Wr, this will hold memBank parsed from cmd when
                      hook is called            */
  uint8_t wordPtr; /* for Rd/Wr, this will hold wordPtr parsed from cmd when
                      hook is called            */
  uint16_t wrData; /* for Write this will hold the 16-bit Write Data value when
                      hook is called         */
  uint16_t bwrByteCount; /* for BlockWrite this will hold the number of BYTES
                            received                       */
  uint16_t *bwrBufPtr;   /* for BlockWrite this will hold a pointer to the data
                            buffer containing write data */

  // Function Hooks
  void **akHook;  /* this function is called with no params or return after an
                     ack command response   */
  void **wrHook;  /* this function is called with no params or return after a
                     write command response  */
  void **bwrHook; /* this function is called with no params or return after a
                     write command response  */
  void **rdHook;  /* this function is called with no params or return after a
                     read command response   */

  // Memory Map Bank Ptrs
  uint8_t *RESBankPtr; /* for read command, this is a pointer to the virtual,
                          mapped Reserved Bank         */
  uint8_t *EPCBankPtr; /* "" mapped EPC Bank */
  uint8_t *TIDBankPtr; /* "" mapped TID Bank */
  uint8_t *USRBankPtr; /* "" mapped USR Bank */
} RWstruct;
extern TXstruct TXData;
extern RWstruct RWData;
typedef struct {
  uint8_t TRext;      /** @todo What is this member? */
  uint16_t handle;    /** @todo What is this member? */
  uint16_t slotCount; /** @todo What is this member? */
  uint8_t Q;          /** @todo What is this member? */

  uint8_t mode;    /** @todo What is this member? */
  uint8_t abortOn; /*  List of command responses which cause the main RFID loop
                      to return              */
  uint8_t abortFlag;  /** @todo What is this member? */
  uint8_t isSelected; /* state of being selected via the select command. Zero if
                         not selected             */

  uint8_t rn8_ind; /* using our RN values in INFO_MEM, this points to the
                      current one to use next      */

  uint16_t edge_capture_prev_ccr; /* Previous value of CCR register, used to
                                     compute delta in edge capture ISRs       */

  /** @todo Add the following: CMD_enum latestCmd; */

} RFIDstruct; /* in MODE_USES_SEL!! */

extern RFIDstruct rfid;

// the  rx data
typedef struct {
  uint8_t abortFlag;
  uint16_t
      edge_capture_prev_ccr; /* Previous value of CCR register, used to compute
                                delta in edge capture ISRs		*/
} RXstruct;

extern RXstruct RXData;
// Memory Banks
extern uint8_t cmd[CMDBUFF_SIZE];
extern uint8_t dataBuf[DATABUFF_SIZE];
extern uint8_t rfidBuf[RFIDBUFF_SIZE];

/* Tag ID */
// #define TAG_ID (2)
extern uint32_t TAG_ID;

extern void SetTagId(int tag_id);

extern uint8_t usrBank[USRBANK_SIZE];
extern uint16_t wisp_ID;
extern volatile uint8_t isDoingLowPwrSleep;

// Register Macros
#define bits _get_R5_register()
#define dest _get_R4_register()
#define setBits(x) _set_R5_register(x)
#define setDest(x) _set_R4_register(x)

// FUNCTION
// PROTOTYPES---------------------------------------------------------------------------------------------------------------//

extern void WISP_TEST(void);
extern void SendTo(void);

extern void TxFM0(volatile uint8_t *data, uint8_t numBytes, uint8_t numBits,
                  uint8_t TRext);  // sends out MSB first...
extern void TxFM3(volatile uint8_t *data, uint8_t numBytes, uint8_t numBits,
                  uint8_t TRext);  // sends out MSB first...
extern void TxFM4(volatile uint8_t *data, uint8_t numBytes, uint8_t numBits,
                  uint8_t TRext);  // sends out MSB first...
extern void TxFM5(volatile uint8_t *data, uint8_t numBytes, uint8_t numBits,
                  uint8_t TRext);  // sends out MSB first...
extern void TxFM6(volatile uint8_t *data, uint8_t numBytes, uint8_t numBits,
                  uint8_t TRext);  // sends out MSB first...
extern void TxFM7(volatile uint8_t *data, uint8_t numBytes, uint8_t numBits,
                  uint8_t TRext);  // sends out MSB first...
extern void TxFM8(volatile uint8_t *data, uint8_t numBytes, uint8_t numBits,
                  uint8_t TRext);  // sends out MSB first...
extern void TxFM9(volatile uint8_t *data, uint8_t numBytes, uint8_t numBits,
                  uint8_t TRext);  // sends out MSB first...
extern void TxFM12(volatile uint8_t *data, uint8_t numBytes, uint8_t numBits,
                   uint8_t TRext);  // sends out MSB first...
extern void TxFM15(volatile uint8_t *data, uint8_t numBytes, uint8_t numBits,
                   uint8_t TRext);  // sends out MSB first...
extern void TxFM24(volatile uint8_t *data, uint8_t numBytes, uint8_t numBits,
                   uint8_t TRext);  // sends out MSB first...

// Linker hack: We need to reference assembly ISRs directly somewhere to force
// linker to include them in binary.
extern void RX_ISR(void);
extern void Timer0A0_ISR(void);
extern void Timer0A1_ISR(void);
extern void Timer1A0_ISR(void);
extern void MegaScatter_Start(void);

// Command handlers
extern void handleRead(void);
extern void handleSetLed(void);

// Utility functions
extern void lightLED1(void);
extern void lightLED2(void);
extern void toggleLED1(void);
extern void toggleLED2(void);
extern void toggleLED1(void);
extern void offLED1(void);
extern void offLED2(void);
extern void prepare_data();
extern void adc_setup();
extern void frame();
extern void to_cdma();
extern __interrupt void Port_2(void);
// MACROS----------------------------------------------------------------------------------------------------------------------------//
#define BITSET(port, pin) port |= (pin)
#define BITCLR(port, pin) port &= ~(pin)
#define BITTOG(port, pin) port ^= (pin)

// RFID
// DEFINITIONS------------------------------------------------------------------------------------------------------------------//

#define STORED_PC                                           \
  (((EPC_LENGTH & 0x001F) << 11) | ((UMI & 0x0001) << 10) | \
   ((XI & 0x0001) << 9) | (NSI & 0x01FF) << 01)
//**per EPC Spec would be:
//#define STORED_PC_GRR     (uint16_t)  (  ((NSI&0x01FF)<<7) | ((XI&0x01)<<6) |
//((UMI&0x01)<<5) | (EPC_LENGTH&0x1F)  )

// This is the ugliest, non-portable code ever BUT it allows the compiler to
// setup the memory at compile time.
#define STORED_PC1 ((STORED_PC & 0xFF00) >> 8)
#define STORED_PC0 ((STORED_PC & 0x00FF) >> 0)

#endif /* __ASSEMBLER__ */
#endif /* GLOBALS_H_ */
