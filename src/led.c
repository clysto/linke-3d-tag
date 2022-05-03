#include "led.h"

#include <driverlib.h>

void LED_init() {
  // LED1 <---> P4.0
  GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN0);
  // 默认熄灭
  GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN0);
  // LED2 <---> PJ.6
  GPIO_setAsOutputPin(GPIO_PORT_PJ, GPIO_PIN6);
  // 默认熄灭
  GPIO_setOutputLowOnPin(GPIO_PORT_PJ, GPIO_PIN6);
}

void LED_toggleLED1() { GPIO_toggleOutputOnPin(GPIO_PORT_P4, GPIO_PIN0); }

void LED_toggleLED2() { GPIO_toggleOutputOnPin(GPIO_PORT_PJ, GPIO_PIN6); }

void LED_turnOnLED1() { GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN0); }

void LED_turnOnLED2() { GPIO_setOutputHighOnPin(GPIO_PORT_PJ, GPIO_PIN6); }

void LED_turnOffLED1() { GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN0); }

void LED_turnOffLED2() { GPIO_setOutputLowOnPin(GPIO_PORT_PJ, GPIO_PIN6); }

/**
 * @brief 使用 LED 灯表示一个 uint16 数据
 * LED1 亮起表示1
 * LED2 亮起表示0
 * 从最高位开始发送
 * 
 * @param data 要表示的 uint16 数据
 */
void LED_showUint16(uint16_t data) {
  LED_turnOffLED1();
  LED_turnOffLED2();
  for (int i = 0; i < 16; i++) {
    if (data >> (15 - i) & 0x0001) {
      LED_turnOnLED1();
    } else {
      LED_turnOnLED2();
    }
    __delay_cycles(50000);
    LED_turnOffLED1();
    LED_turnOffLED2();
    __delay_cycles(50000);
  }
}
