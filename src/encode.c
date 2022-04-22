#include <driverlib.h>

#define SETBIT(bitstream, index) \
  bitstream[(index) / 8] |= (0x80U >> ((index) % 8));

/**
 * @brief FM0 编码
 *
 * encodedBitstream 必须全是 0
 * @param bitstream 要编码的比特流
 * @param encodedBitstream 编码后的比特流
 * @param size 编码比特流的大小 (byte)
 */
void ENCODE_FM0(uint8_t *bitstream, uint8_t *encodedBitstream, int size) {
  uint8_t first, second, pre = 0;
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < 8; j++) {
      int cur_bit = (0x80U >> j) & bitstream[i];
      // symbol 开始电平翻转
      first = pre ^ 1;
      if (cur_bit) {
        // 如果是 1: symbol 中间不翻转
        second = first;
      } else {
        // 如果是 0: symbol 中间翻转
        second = first ^ 1;
      }
      pre = second;
      if (first) {
        SETBIT(encodedBitstream, (i * 8 + j) * 2);
      }
      if (second) {
        SETBIT(encodedBitstream, (i * 8 + j) * 2 + 1);
      }
    }
  }
}
