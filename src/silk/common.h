#ifndef SILK_COMMON_H
#define SILK_COMMON_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#define SILK_INVALID_INDEX SIZE_MAX

typedef void(*silk_map_callback_t)(void* element);
typedef void(*silk_reduce_callback_t)(void* data, void* element);

#include "utils.h"

#endif // SILK_COMMON_H
