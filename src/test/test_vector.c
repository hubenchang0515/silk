#include <silk/log.h>
#include <silk/vector.h>

#define N 10

void test_vector()
{
    // create
    silk_vector_t vector = silk_vector_new(sizeof(int));
    SILK_ASSERT(vector != NULL);
    SILK_ASSERT(silk_vector_data(vector) == NULL);
    SILK_ASSERT(silk_vector_const_data(vector) == NULL);
    SILK_ASSERT(silk_vector_element_size(vector) == sizeof(int));
    SILK_ASSERT(silk_vector_length(vector) == 0);
    SILK_ASSERT(silk_vector_capacity(vector) == 0);

    // append
    for (int i = 0; i < N; i++)
    {
        silk_vector_push_back(vector, (const void*)(&i));
        SILK_ASSERT(silk_vector_length(vector) == (i+1));
    }
    for (int i = 0; i < N; i++)
    {
        int n;
        SILK_ASSERT(silk_vector_get(vector, i, (void*)(&n)) == true);
        SILK_ASSERT(n == i);
    }
    for (int i = 0; i < N; i++)
    {
        int n = 233;
        SILK_ASSERT(silk_vector_set(vector, i, (void*)(&n)) == true);
        SILK_ASSERT(silk_vector_get(vector, i, (void*)(&n)) == true);
        SILK_ASSERT(n == 233);
    }

    // insert
    silk_vector_clear(vector);
    silk_vector_reserve(vector, N);
    for (int i = 0; i < N; i++)
    {
        SILK_ASSERT(silk_vector_push_front(vector, (void*)(&i)) == true);
    }
    for (int i = 0; i < N; i++)
    {
        SILK_ASSERT(silk_vector_insert(vector, N, (void*)(&i)) == true);
    }

    // pop front
    for (int i = 0; i < N; i++)
    {
        int n;
        silk_vector_pop_front(vector, &n);
        SILK_ASSERT(n == (N-1-i));
    }

    // recycle
    SILK_ASSERT(silk_vector_length(vector) == N);
    silk_vector_recycle(vector);
    SILK_ASSERT(silk_vector_capacity(vector) == N);

    // copy
    silk_vector_t copied = silk_vector_copy(vector);
    silk_vector_delete(vector);
    SILK_ASSERT(silk_vector_length(copied) == N);
    SILK_ASSERT(silk_vector_capacity(copied) == N);

    // pop back
    for (int i = 0; i < N; i++)
    {
        int n;
        silk_vector_pop_back(copied, &n);
        SILK_ASSERT(n == i);
    }

    silk_vector_delete(copied);
}