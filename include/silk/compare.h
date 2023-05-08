#ifndef SILK_COMPARE_H
#define SILK_COMPARE_H

/*******************************************************
 * @brief pointer to compare function
 * @param x a value to compare
 * @param y a value to compare
 * @param userdata a user data
 * @return negative value while x < y
 *         positive value while x > y
 *         0 while x == y
 *******************************************************/
typedef int (*silk_compare_t)(const void* x, const void* y, const void* userdata);

#define SILK_COMPARE_DECLARE(TYPE, NAME)                                     \
extern int silk_compare_##NAME(const void* x, const void* y, const void* userdata)

SILK_COMPARE_DECLARE(int,      int);
SILK_COMPARE_DECLARE(int8_t,   int8);
SILK_COMPARE_DECLARE(int16_t,  int16);
SILK_COMPARE_DECLARE(int32_t,  int32);
SILK_COMPARE_DECLARE(int64_t,  int64);
SILK_COMPARE_DECLARE(intmax_t, intmax);
SILK_COMPARE_DECLARE(intptr_t, intptr);

SILK_COMPARE_DECLARE(unsigned,  uint);
SILK_COMPARE_DECLARE(uint8_t,   uint8);
SILK_COMPARE_DECLARE(uint16_t,  uint16);
SILK_COMPARE_DECLARE(uint32_t,  uint32);
SILK_COMPARE_DECLARE(uint64_t,  uint64);
SILK_COMPARE_DECLARE(uintmax_t, uintmax);
SILK_COMPARE_DECLARE(uintptr_t, uintptr);

SILK_COMPARE_DECLARE(float,  float);
SILK_COMPARE_DECLARE(double, double);

#endif // SILK_COMPARE_H