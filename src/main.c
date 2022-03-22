#include <driverlib.h>
#include <msp430.h>

int main(void) {
  // 关闭看门狗
  WDT_A_hold(WDT_A_BASE);
  // Disable the GPIO power-on default high-impedance
  PM5CTL0 &= ~LOCKLPM5;
  // 初始化 SPI
  EUSCI_A_SPI_initMasterParam param = {0};
  param.msbFirst = EUSCI_A_SPI_MSB_FIRST;
  param.selectClockSource = EUSCI_A_SPI_CLOCKSOURCE_SMCLK;
  param.spiMode = EUSCI_A_SPI_3PIN;
  // 时钟 1MHz
  param.clockSourceFrequency = 1000000;
  param.desiredSpiClock = 1000000;
  EUSCI_A_SPI_initMaster(EUSCI_A1_BASE, &param);
  EUSCI_A_SPI_enable(EUSCI_A1_BASE);

  P4DIR |= 0x01;  // Set P1.0 to output direction

  for (;;) {
    volatile unsigned int i;  // volatile to prevent optimization

    P4OUT ^= 0x01;  // Toggle P1.0 using exclusive-OR

    i = 10000;  // SW Delay
    do i--;
    while (i != 0);
  }

  return 0;
}
