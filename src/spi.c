#include "spi.h"

#include <driverlib.h>
#include <msp430.h>

void SPI_init() {
  // DCO 晶振频率设置为 1MHz (CS_DCOFSEL_0)
  // CS_setDCOFreq(CS_DCORSEL_0, CS_DCOFSEL_0);
  // 设置 SMCLK 的时钟源为 DCO
  // CS_initClockSignal(CS_SMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);

  /**
   * P2.4 为 UCA1CLK  引脚
   * P2.5 为 UCA1SIMO 引脚
   * P2.6 为 UCA1SOMI 引脚
   */
  GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P2,
                                             GPIO_PIN4 + GPIO_PIN5 + GPIO_PIN6,
                                             GPIO_SECONDARY_MODULE_FUNCTION);

  EUSCI_A_SPI_initMasterParam param = {0};
  // 使用 SMCLK 作为 SPI 时钟源
  param.selectClockSource = EUSCI_A_SPI_CLOCKSOURCE_SMCLK;
  // SMCLK 时钟 1MHz
  param.clockSourceFrequency = CS_getSMCLK();
  // SPI 时钟 1MHz
  // 这里如果设置不同的频率,EUSCI_A_SPI_initMaster函数
  // 会通过配置 UCAxBRW 寄存器参数来实现分频
  param.desiredSpiClock = CS_getSMCLK();
  param.msbFirst = EUSCI_A_SPI_MSB_FIRST;
  param.clockPhase = EUSCI_A_SPI_PHASE_DATA_CAPTURED_ONFIRST_CHANGED_ON_NEXT;
  param.clockPolarity = EUSCI_A_SPI_CLOCKPOLARITY_INACTIVITY_LOW;
  // 3PIN 模式
  param.spiMode = EUSCI_A_SPI_3PIN;
  // 初始化 master
  EUSCI_A_SPI_initMaster(EUSCI_A1_BASE, &param);
  // 使能 EUSCI SPI A1 模块
  EUSCI_A_SPI_enable(EUSCI_A1_BASE);
  // 清除发送中断 flag
  EUSCI_A_SPI_clearInterrupt(EUSCI_A1_BASE, EUSCI_A_SPI_TRANSMIT_INTERRUPT);
  // 清除接受中断 flag
  EUSCI_A_SPI_clearInterrupt(EUSCI_A1_BASE, EUSCI_A_SPI_RECEIVE_INTERRUPT);
}

void SPI_transaction(uint8_t* rxBuf, uint8_t const* txBuf, uint16_t size) {
  unsigned int curRx = 0;
  unsigned int curTx = 0;

  do {
    // 发送一个字节的数据
    EUSCI_A_SPI_transmitData(EUSCI_A1_BASE, txBuf[curTx]);
    // 等待 SLAVE 接受成功
    while (!(UCA1IFG & UCRXIFG))
      ;
    // 接收数据
    rxBuf[curRx] = EUSCI_A_SPI_receiveData(EUSCI_A1_BASE);
    // TODO: 此处直接访问了寄存器, 以后改为使用 driverlib 控制
    UCA1IFG &= ~UCRXIFG;
    UCA1IFG &= ~UCTXIFG;
    curTx++;
    curRx++;
    size--;
  } while (size);
}
