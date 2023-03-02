#include <silk/log.h>
#include <silk/memory.h>
#include <stdlib.h>
#include <string.h>

void test_memory()
{
    SILK_ASSERT(silk_set_alloc_func(NULL) == malloc);
    SILK_ASSERT(silk_set_free_func(NULL) == free);
    SILK_ASSERT(silk_set_realloc_func(NULL) == realloc);
    SILK_ASSERT(silk_set_copy_func(NULL) == memmove);
}