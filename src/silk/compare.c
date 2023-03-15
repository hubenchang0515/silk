#include "compare.h"

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include "log.h"

#define SILK_COMPARE_DEFINE(TYPE, NAME)         \
SILK_COMPARE_DECLARE(TYPE, NAME)                \
{                                               \
    (void)userdata;                             \
    if (*(const TYPE*)x > *(const TYPE*)y)      \
        return 1;                               \
    else if (*(const TYPE*)x < *(const TYPE*)y) \
        return -1;                              \
    else                                        \
        return 0;                               \
}

SILK_COMPARE_DEFINE(int,      int);
SILK_COMPARE_DEFINE(int8_t,   int8);
SILK_COMPARE_DEFINE(int16_t,  int16);
SILK_COMPARE_DEFINE(int32_t,  int32);
SILK_COMPARE_DEFINE(int64_t,  int64);
SILK_COMPARE_DEFINE(intmax_t, intmax);
SILK_COMPARE_DEFINE(intptr_t, intptr);

SILK_COMPARE_DEFINE(unsigned,  uint);
SILK_COMPARE_DEFINE(uint8_t,   uint8);
SILK_COMPARE_DEFINE(uint16_t,  uint16);
SILK_COMPARE_DEFINE(uint32_t,  uint32);
SILK_COMPARE_DEFINE(uint64_t,  uint64);
SILK_COMPARE_DEFINE(uintmax_t, uintmax);
SILK_COMPARE_DEFINE(uintptr_t, uintptr);

SILK_COMPARE_DEFINE(float,  float);
SILK_COMPARE_DEFINE(double, double);