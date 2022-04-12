#include <driverlib.h>

#include "accel.h"
#include "led.h"
#include "spi.h"

uint8_t const DATA[] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x00, 0x01, 0x02,
    0x03, 0x04, 0x05, 0x06, 0x07, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05,
    0x06, 0x07, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
};

uint8_t id;
uint8_t status;
float x, y, z;

int main(void) {
  // 关闭看门狗
  WDT_A_hold(WDT_A_BASE);

  // Disable FRAM wait cycles to allow clock operation over 8MHz
  // FRAMCtl_configureWaitStateControl(FRAMCTL_ACCESS_TIME_CYCLES_1);

  // 配置 DCO 为 16 MHz
  // CS_setDCOFreq(CS_DCORSEL_1, CS_DCOFSEL_4);
  CS_setDCOFreq(CS_DCORSEL_0, CS_DCOFSEL_0);
  // MCLK 时钟源配置为 DCO
  CS_initClockSignal(CS_MCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
  // SMCLK 时钟源配置为 DCO (16MHz / 16 = 1MHz)
  CS_initClockSignal(CS_SMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
  CS_enableClockRequest(CS_MCLK);
  CS_enableClockRequest(CS_SMCLK);

  __delay_cycles(1000);

  // 初始化 LED
  LED_init();
  // 初始化 SPI
  SPI_init();
  // 初始化加速度计
  ACCEL_init();

  // P4.5 配置为天线使能
  GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN5);

  // P2.7 配置为天线输出
  GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN7);

  // P2.3 配置为天线输入
  GPIO_setAsInputPin(GPIO_PORT_P2, GPIO_PIN3);

  // 使能天线
  GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN5);

  // P2.3 下降沿中断触发
  GPIO_selectInterruptEdge(GPIO_PORT_P2, GPIO_PIN3,
                           GPIO_HIGH_TO_LOW_TRANSITION);

  PMM_unlockLPM5();

  GPIO_clearInterrupt(GPIO_PORT_P2, GPIO_PIN3);
  // 使能RX中断(rx_isr.S)
  GPIO_enableInterrupt(GPIO_PORT_P2, GPIO_PIN3);

  __delay_cycles(100000);
  ACCEL_result accelResult;

  id = ACCEL_getDEVID();

  __delay_cycles(100000);

  while (1) {
    // status = ACCEL_status();
    // __delay_cycles(100000);
    ACCEL_singleSample(&accelResult);
    __delay_cycles(100000);
  }

  // start
  // LED_turnOnLED1();
  __bis_SR_register(LPM4_bits + GIE);
  __no_operation();
  return 0;
}
