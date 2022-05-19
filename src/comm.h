#ifndef COMM_H
#define COMM_H

#include <stdint.h>

typedef struct COMM_initParam {
  void (*beforeSend)(uint8_t *, int);
} COMM_initParam;

void COMM_init(COMM_initParam *param);

#endif
