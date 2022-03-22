#include "accel.h"

#include <driverlib.h>
#include <msp430.h>

uint8_t const ADXL_CONFIG_RESET[] = {ADXL_CMD_WRITE_REG, ADXL_REG_SOFT_RESET,
                                     0x52};
uint8_t const ADXL_READ_DEVID[] = {ADXL_CMD_READ_REG, ADXL_REG_DEVID_AD, 0x00};

uint8_t ACCEL_readID() {
  uint8_t rxBuf[32];
  ACCEL_sendCommand(ADXL_READ_DEVID, rxBuf, sizeof(ADXL_READ_DEVID));
  return rxBuf[2];
}

void ACCEL_sendCommand(uint8_t* txBuf, uint8_t* rxBuf, uint16_t size) {
  unsigned int curRx = 0;
  unsigned int curTx = 0;

  do {
    // 发送数据
    EUSCI_A_SPI_transmitData(EUSCI_A1_BASE, txBuf[curTx]);
    // 等待接受
    while (!EUSCI_A_SPI_getInterruptStatus(EUSCI_A1_BASE,
                                           EUSCI_A_SPI_TRANSMIT_INTERRUPT))
      ;
    // 接收数据
    rxBuf[curRx] = EUSCI_A_SPI_receiveData(EUSCI_A1_BASE);
    curTx++;
    curTx++;
    size--;
  } while (size);
}

void ACCEL_init() {
  // 首先初始化 SPI 模块

  // 时钟设置
  CS_setDCOFreq(CS_DCORSEL_0, CS_DCOFSEL_3);
  CS_initClockSignal(CS_SMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
  GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P2, GPIO_PIN4,
                                             GPIO_SECONDARY_MODULE_FUNCTION);
  GPIO_setAsPeripheralModuleFunctionInputPin(
      GPIO_PORT_P2, GPIO_PIN5 + GPIO_PIN6, GPIO_SECONDARY_MODULE_FUNCTION);
  PMM_unlockLPM5();

  // 初始化 master
  EUSCI_A_SPI_initMasterParam param = {0};
  param.selectClockSource = EUSCI_A_SPI_CLOCKSOURCE_SMCLK;
  param.clockSourceFrequency = CS_getSMCLK();
  param.desiredSpiClock = 500000;
  param.msbFirst = EUSCI_A_SPI_MSB_FIRST;
  param.clockPhase = EUSCI_A_SPI_PHASE_DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT;
  param.clockPolarity = EUSCI_A_SPI_CLOCKPOLARITY_INACTIVITY_HIGH;
  param.spiMode = EUSCI_A_SPI_3PIN;
  EUSCI_A_SPI_initMaster(EUSCI_A1_BASE, &param);

  // Enable SPI module
  EUSCI_A_SPI_enable(EUSCI_A1_BASE);

  EUSCI_A_SPI_clearInterrupt(EUSCI_A1_BASE, EUSCI_A_SPI_RECEIVE_INTERRUPT);
  // Enable USCI_A1 RX interrupt
  EUSCI_A_SPI_enableInterrupt(EUSCI_A1_BASE, EUSCI_A_SPI_RECEIVE_INTERRUPT);

  // SPI 初始化结束

  // 初始化 ADXL362

  BITSET(PDIR_ACCEL_EN, PIN_ACCEL_EN);
  BITCLR(POUT_ACCEL_EN, PIN_ACCEL_EN);

  uint8_t id = ACCEL_readID();
}

__attribute__((interrupt(USCI_A1_VECTOR))) void USCI_A1_ISR(void) {
  switch (__even_in_range(UCA1IV, USCI_SPI_UCTXIFG)) {
    case USCI_SPI_UCRXIFG:
      // 延迟 40 个周期
      __delay_cycles(40);
      break;
    default:
      break;
  }
}