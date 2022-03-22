#include <driverlib.h>

#include "accel.h"
#include "led.h"

int main(void) {
  WDT_A_hold(WDT_A_BASE);
  LED_init();
  ACCEL_init();

  __delay_cycles(100);
  __bis_SR_register(LPM0_bits + GIE);
  __no_operation();
  return 0;
}
