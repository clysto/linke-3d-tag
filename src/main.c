#include <driverlib.h>

#include "accel.h"
#include "crc.h"
#include "encode.h"
#include "led.h"
#include "spi.h"

uint16_t CRC_SEED = 0x00;

// 前两个字节是前导码序列
// 最后两个字节是 CRC16 校验
// "hello linke lab!!!!!!!!!!!!!" == CRC => 0x0FE0
uint8_t RAW_DATA[32] = {0x00, 0x00, 0x68, 0x65, 0x6c, 0x6c, 0x6f, 0x20,
                        0x6c, 0x69, 0x6e, 0x6b, 0x65, 0x20, 0x6c, 0x61,
                        0x62, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21,
                        0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x00, 0x00};

// 发送缓冲区(在rx_isr.S中调用)
uint8_t BITSTREAM[64] = {0};

void sample() {
  // ACCEL_result accelResult;
  // ACCEL_singleSample(&accelResult);

  // 计算 CRC (CRC16_CCIT_ZERO)
  CRC_setSeed(CRC_BASE, CRC_SEED);
  for (int i = 2; i < 30; i++) {
    // Add all of the values into the CRC signature
    CRC_set8BitDataReversed(CRC_BASE, RAW_DATA[i]);
  }
  uint16_t crcResult = CRC_getResult(CRC_BASE);
  RAW_DATA[30] = (uint8_t)(crcResult & 0xFF);
  RAW_DATA[31] = (uint8_t)((crcResult >> 8) & 0xFF);

  // 使用 FM0 对原始数据编码
  ENCODE_FM0(RAW_DATA, BITSTREAM, 32);
  // 填充前导码
  BITSTREAM[0] = 0xAA;
  BITSTREAM[1] = 0xAA;
  BITSTREAM[2] = 0xAA;
  BITSTREAM[3] = 0xAA;
}

int main(void) {
  // 关闭看门狗
  WDT_A_hold(WDT_A_BASE);

  // Disable FRAM wait cycles to allow clock operation over 8MHz
  FRAMCtl_configureWaitStateControl(FRAMCTL_ACCESS_TIME_CYCLES_1);
  // 配置 DCO 为 16 MHz
  CS_setDCOFreq(CS_DCORSEL_1, CS_DCOFSEL_4);
  // MCLK 时钟源配置为 DCO
  CS_initClockSignal(CS_MCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
  // SMCLK 时钟源配置为 DCO (16MHz / 16 = 1MHz)
  CS_initClockSignal(CS_SMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_16);
  CS_enableClockRequest(CS_MCLK);
  CS_enableClockRequest(CS_SMCLK);

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

  __bis_SR_register(LPM4_bits + GIE);
  __no_operation();
  return 0;
}
