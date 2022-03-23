#include "accel.h"

#include <driverlib.h>
#include <msp430.h>

#include "spi.h"

uint8_t const ADXL_CONFIG_RESET[] = {ADXL_CMD_WRITE_REG, ADXL_REG_SOFT_RESET,
                                     0x52};
uint8_t const ADXL_READ_DEVID[] = {ADXL_CMD_READ_REG, ADXL_REG_DEVID_AD, 0x00};
uint8_t const ADXL_READ_PARTID[] = {ADXL_CMD_READ_REG, ADXL_REG_PARTID, 0x00};

uint8_t ACCEL_readDEVID() {
  uint8_t rxBuf[16];
  GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN3);
  SPI_transaction(rxBuf, ADXL_READ_DEVID, sizeof(ADXL_READ_DEVID));
  GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN3);
  return rxBuf[2];
}

uint8_t ACCEL_readPARTID() {
  uint8_t rxBuf[16];
  GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN3);
  SPI_transaction(rxBuf, ADXL_READ_PARTID, sizeof(ADXL_READ_PARTID));
  GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN3);
  return rxBuf[2];
}

void ACCEL_init() {
  // P4.2 ACCEL_EN 引脚
  GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN2);
  // P4.3 ACCEL_CS 引脚
  GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN3);
  // 使能 ACCEL_EN 端口
  GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN2);
}
