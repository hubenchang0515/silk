#include <silk/log.h>
#include <silk/compare.h>

#include <stdint.h>
#include <stddef.h>
#include <float.h>
#include <limits.h>

#define COMPARE_TEST(TYPE, NAME, BEGIN, END, DELTA)             \
{                                                               \
    for (TYPE x = BEGIN; x < END; x = x+DELTA)                  \
    {                                                           \
        TYPE y = x;                                             \
        SILK_ASSERT(silk_compare_##NAME(&x, &y, NULL) == 0);    \
    }                                                           \
                                                                \
    for (TYPE x = BEGIN; x < END; x = x + DELTA)                \
    {                                                           \
        for (TYPE y = BEGIN; y < x; y = y + DELTA)              \
            SILK_ASSERT(silk_compare_##NAME(&x, &y, NULL) > 0); \
    }                                                           \
                                                                \
    for (TYPE x = BEGIN; x < END; x = x + DELTA)        \
    {                                                           \
        for (TYPE y = x+DELTA; y < END - DELTA; y = y + DELTA)  \
            SILK_ASSERT(silk_compare_##NAME(&x, &y, NULL) < 0); \
    }                                                           \
}

#define TEST_RANGE 64

void test_compare()
{
    COMPARE_TEST(int,   int,    INT_MIN,                INT_MIN+TEST_RANGE,     1);
    COMPARE_TEST(int,   int,    INT_MAX-TEST_RANGE,     INT_MAX,                1);

    COMPARE_TEST(int8_t, int8, INT8_MIN, INT8_MAX, 1);

    COMPARE_TEST(int16_t,   int16,  INT16_MIN,              INT16_MIN+TEST_RANGE,   1);
    COMPARE_TEST(int16_t,   int16,  -TEST_RANGE,            TEST_RANGE,             1);
    COMPARE_TEST(int16_t,   int16,  INT16_MAX-TEST_RANGE,   INT16_MAX,              1);

    COMPARE_TEST(int32_t,   int32,  INT32_MIN,              INT32_MIN+TEST_RANGE,   1);
    COMPARE_TEST(int32_t,   int32,  -TEST_RANGE,            TEST_RANGE,             1);
    COMPARE_TEST(int32_t,   int32,  INT32_MAX-TEST_RANGE,   INT32_MAX,              1);

    COMPARE_TEST(int64_t,   int64,  INT64_MIN, INT64_MIN+TEST_RANGE, 1);
    COMPARE_TEST(int64_t,   int64,  -TEST_RANGE, TEST_RANGE, 1);
    COMPARE_TEST(int64_t,   int64,  INT64_MAX-TEST_RANGE, INT64_MAX, 1);

    COMPARE_TEST(intmax_t, intmax, INTMAX_MIN, INTMAX_MIN+TEST_RANGE, 1);
    COMPARE_TEST(intmax_t, intmax, -TEST_RANGE, TEST_RANGE, 1);
    COMPARE_TEST(intmax_t, intmax, INTMAX_MAX-TEST_RANGE, INTMAX_MAX, 1);

    COMPARE_TEST(intptr_t, intptr, INTPTR_MIN, INTPTR_MIN+TEST_RANGE, 1);
    COMPARE_TEST(intptr_t, intptr, -TEST_RANGE, TEST_RANGE, 1);
    COMPARE_TEST(intptr_t, intptr, INTPTR_MAX-TEST_RANGE, INTPTR_MAX, 1);

    COMPARE_TEST(uint,  uint,   0,                      0+TEST_RANGE, 1);
    COMPARE_TEST(uint,  uint,   UINT_MAX-TEST_RANGE,    UINT_MAX, 1);

    COMPARE_TEST(uint8_t,   uint8,  0,  UINT8_MAX,  1);

    COMPARE_TEST(uint16_t,  uint16,     0,                      0+TEST_RANGE,   1);
    COMPARE_TEST(uint16_t,  uint16,     UINT16_MAX-TEST_RANGE,  UINT16_MAX,     1);

    COMPARE_TEST(uint32_t,  uint32,     0,                      0+TEST_RANGE,   1);
    COMPARE_TEST(uint32_t,  uint32,     UINT32_MAX-TEST_RANGE,  UINT32_MAX,     1);

    COMPARE_TEST(uint64_t,  uint64,     0,                      0+TEST_RANGE,   1);
    COMPARE_TEST(uint64_t,  uint64,     UINT64_MAX-TEST_RANGE,  UINT64_MAX,     1);

    COMPARE_TEST(uintmax_t, uintmax,    0,                      0+TEST_RANGE,   1);
    COMPARE_TEST(uintmax_t, uintmax,    UINTMAX_MAX-TEST_RANGE, UINTMAX_MAX,    1);

    COMPARE_TEST(uintptr_t, uintptr,    0,                      0+TEST_RANGE,   1);
    COMPARE_TEST(uintptr_t, uintptr,    UINTPTR_MAX-TEST_RANGE, UINTPTR_MAX,    1);


    COMPARE_TEST(float,     float,  FLT_MIN,                        FLT_MIN+TEST_RANGE*FLT_EPSILON, FLT_EPSILON);
    COMPARE_TEST(float,     float,  FLT_MAX-TEST_RANGE*FLT_EPSILON, FLT_MAX,                        FLT_EPSILON);

    COMPARE_TEST(double,    double, DBL_MIN,                        DBL_MIN+TEST_RANGE*DBL_EPSILON, DBL_EPSILON);
    COMPARE_TEST(double,    double, DBL_MAX-TEST_RANGE*DBL_EPSILON, DBL_MAX,                        DBL_EPSILON);
}