#ifndef LED_H
#define LED_H

#include <driverlib.h>

void LED_init();

void LED_toggleLED1();

void LED_toggleLED2();

void LED_turnOnLED1();

void LED_turnOnLED2();

void LED_turnOffLED1();

void LED_turnOffLED2();

void LED_showUint16(uint16_t data);

#endif