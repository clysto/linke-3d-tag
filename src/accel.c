#include "accel.h"

#include <driverlib.h>

#include "spi.h"

/* clang-format off */
uint8_t const ADXL_READ_PARTID[] = {ADXL_CMD_READ_REG, ADXL_REG_PARTID, 0x00};
uint8_t const ADXL_READ_DEVID[] = {ADXL_CMD_READ_REG, ADXL_REG_DEVID_AD, 0x00};
uint8_t const ADXL_REAsxD_STATUS[] = {ADXL_CMD_READ_REG, ADXL_REG_STATUS, 0x00};
uint8_t const ADXL_READ_XYZ_8BIT[] = {ADXL_CMD_READ_REG, ADXL_REG_XDATA, 0x00, 0x00, 0x00};
uint8_t const ADXL_READ_XYZ_16BIT[] = {ADXL_CMD_READ_REG, ADXL_REG_XDATA_L, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t const ADXL_READ_XYZ_16BIT_FIFO[] = {ADXL_CMD_READ_FIFO, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t const ADXL_CONFIG_MEAS[] = {ADXL_CMD_WRITE_REG, ADXL_REG_POWER_CTL, 0x22};
uint8_t const ADXL_CONFIG_STBY[] = {ADXL_CMD_WRITE_REG, ADXL_REG_POWER_CTL, 0x00};
uint8_t const ADXL_CONFIG_RESET[] = {ADXL_CMD_WRITE_REG, ADXL_REG_SOFT_RESET, 0x52};
uint8_t const ADXL_CONFIG_FILTER[] = {ADXL_CMD_WRITE_REG, ADXL_REG_FILTER_CTL, 0x14};
uint8_t const ADXL_CONFIG_INTERRUPT[] = {ADXL_CMD_WRITE_REG, ADXL_REG_INTMAP1, 0X01};
uint8_t const ADXL_CONFIG_FIFO_CTL[] = {ADXL_CMD_WRITE_REG, ADXL_REG_FIFO_CONTROL, 0X0A};
uint8_t const ADXL_CONFIG_FIFO_SAMPLE[] = {ADXL_CMD_WRITE_REG, ADXL_REG_FIFO_SAMPLES, 6};
/* clang-format on */

/**
 * @brief 获取 DEVID 寄存器的值
 *
 * ADXL362 的 DEVID 是 0xAD
 * @return uint8_t
 */
uint8_t ACCEL_getDEVID() {
  uint8_t rxBuf[16];
  GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN3);
  SPI_transaction(rxBuf, ADXL_READ_DEVID, sizeof(ADXL_READ_DEVID));
  GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN3);
  return rxBuf[2];
}

/**
 * @brief 获取 PARTID 寄存器的值
 *
 * ADXL362 的 PARTID 是 0xF2
 * @return uint8_t
 */
uint8_t ACCEL_getPARTID() {
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
  // 软复位
  uint8_t rxBuf[16];
  GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN3);
  SPI_transaction(rxBuf, ADXL_CONFIG_RESET, sizeof(ADXL_CONFIG_RESET));
  GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN3);
  __delay_cycles(10000);
  // 进入 MEASUREMENT MODE (Ultralow noise mode)
  GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN3);
  SPI_transaction(rxBuf, ADXL_CONFIG_MEAS, sizeof(ADXL_CONFIG_MEAS));
  GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN3);
  __delay_cycles(10000);
  // 配置 filter
  GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN3);
  SPI_transaction(rxBuf, ADXL_CONFIG_FILTER, sizeof(ADXL_CONFIG_FILTER));
  GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN3);
}

uint8_t ACCEL_status() {
  uint8_t rxBuf[16];
  GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN3);
  SPI_transaction(rxBuf, ADXL_REAsxD_STATUS, sizeof(ADXL_REAsxD_STATUS));
  GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN3);
  return rxBuf[2];
}

void ACCEL_singleSample(ACCEL_result *result) {
  uint8_t rxBuf[16];
  // 进入 MEASUREMENT MODE (Ultralow noise mode)
  GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN3);
  SPI_transaction(rxBuf, ADXL_CONFIG_MEAS, sizeof(ADXL_CONFIG_MEAS));
  GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN3);

  GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN3);
  SPI_transaction(rxBuf, ADXL_READ_XYZ_16BIT, sizeof(ADXL_READ_XYZ_16BIT));
  GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN3);
  result->x = ((uint16_t)rxBuf[3] << 8) + rxBuf[2];
  result->y = ((uint16_t)rxBuf[5] << 8) + rxBuf[4];
  result->z = ((uint16_t)rxBuf[7] << 8) + rxBuf[6];
}
