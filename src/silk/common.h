#ifndef SILK_COMMON_H
#define SILK_COMMON_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#define SILK_INVALID_INDEX SIZE_MAX

/*******************************************************
 * @brief pointer to compare function
 * @param x a value to compare
 * @param y a value to compare
 * @param userdata a user data
 * @return negative value while x < y
 *         positive value while x > y
 *         0 while x == y
 *******************************************************/
typedef int (*silk_compare_fn)(const void* x, const void* y, const void* userdata);

#endif // SILK_COMMON_H
