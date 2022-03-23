#include <driverlib.h>

#include "accel.h"
#include "led.h"
#include "spi.h"

int main(void) {
  // 关闭看门狗
  WDT_A_hold(WDT_A_BASE);
  PMM_unlockLPM5();
  // 初始化 LED
  LED_init();
  // 初始化 SPI
  SPI_init();


  __delay_cycles(100);
  // 初始化加速度计
  ACCEL_init();

  __delay_cycles(100);
  __bis_SR_register(LPM0_bits + GIE);
  __no_operation();
  return 0;
}
