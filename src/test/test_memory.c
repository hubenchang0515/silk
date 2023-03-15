#include <silk/log.h>
#include <silk/memory.h>
#include <stdlib.h>
#include <string.h>

#define N 1024

void test_memory()
{
    SILK_ASSERT(silk_set_alloc_func(NULL) == malloc);
    SILK_ASSERT(silk_set_free_func(NULL) == free);
    SILK_ASSERT(silk_set_realloc_func(NULL) == realloc);
    SILK_ASSERT(silk_set_copy_func(NULL) == memcpy);
    SILK_ASSERT(silk_set_overlap_copy_func(NULL) == memmove);

    void* p = silk_alloc(100);
    SILK_ASSERT(p != NULL);
    silk_free(p);
    
    p = silk_realloc(NULL, 100);
    SILK_ASSERT(p != NULL);
    silk_free(p);

    int buffer[N];
    for (int i = 0; i < N; i++)
    {
        buffer[i] = i;
    }

    int buffer2[N];
    silk_copy(buffer2, buffer, N*sizeof(int));
    for (int i = 1; i < N; i++)
    {
        SILK_ASSERT(buffer[i] == i);
    }
    
    silk_overlap_copy(buffer + 1, buffer, (N-1)*sizeof(int));
    for (int i = 1; i < N; i++)
    {
        SILK_ASSERT(buffer[i] == i-1);
    }
}