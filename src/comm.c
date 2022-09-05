#include "comm.h"

#include <driverlib.h>
#include <string.h>

#include "encode.h"

// 用户设置参数
COMM_initParam *USER_PARAM;

uint16_t CRC_SEED = 0x00;

// 发送缓冲区(在rx_isr.S中调用)
// [5 byte preamble] + [32 * 2 byte payload] + [2 * 2 byte CRC] + [1 byte
// dummy1]
uint8_t BITSTREAM[74] = {0};

void COMM_init(COMM_initParam *param) { USER_PARAM = param; }

/**
 * @brief 数据发送前会先运行这个函数
 *
 * 用户通过定义 USER_PARAM->beforeSend 函数
 * 在发送数据前对 payload 进行填充
 */
void COMM_beforeSend() {
  uint8_t payload[34] = {0};

  // 用户回调函数
  USER_PARAM->beforeSend(payload, 32);

  // IMPORTANT!!!!!!!! 清空 BITSTREAM
  memset(BITSTREAM, 0, 74);

  // 前导码 0000 1010 1010 1010 1010 1010 1010 1101 0010 0011
  BITSTREAM[0] = 0x0A;
  BITSTREAM[1] = 0xAA;
  BITSTREAM[2] = 0xAA;
  BITSTREAM[3] = 0xAD;
  BITSTREAM[4] = 0x23;

  // 计算 CRC (CRC16_CCIT_ZERO)
  CRC_setSeed(CRC_BASE, CRC_SEED);
  for (int i = 0; i < 32; i++) {
    // Add all of the values into the CRC signature
    CRC_set8BitDataReversed(CRC_BASE, payload[i]);
  }
  uint16_t crcResult = CRC_getResult(CRC_BASE);
  // memcpy(payload + 32, &crcResult, sizeof(uint16_t));
  payload[32] = (crcResult >> 8) & 0xFFU;
  payload[33] = crcResult & 0xFFU;

  // 使用 FM0 对 payload 编码
  ENCODE_FM0(payload, BITSTREAM + 5, 34);

  // FM0 End-of-Signaling
  if ((BITSTREAM[72] & 1) == 0) {
    // Add dummy 1
    BITSTREAM[73] = 0xC0;
  } else {
    BITSTREAM[73] = 0x00;
  }
}
