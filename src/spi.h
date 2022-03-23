#ifndef SPI_H
#define SPI_H

#include <driverlib.h>

void SPI_init();

void SPI_transaction(uint8_t* rxBuf, uint8_t* txBuf, uint16_t size);

#endif