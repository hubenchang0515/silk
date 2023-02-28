#include <assert.h>
#include <silk/vector.h>

#define N 10

void test_vector()
{
    // create
    silk_vector_t vector = silk_vector_new(sizeof(int));
    assert(vector != NULL);
    assert(silk_vector_data(vector) == NULL);
    assert(silk_vector_const_data(vector) == NULL);
    assert(silk_vector_element_size(vector) == sizeof(int));
    assert(silk_vector_length(vector) == 0);
    assert(silk_vector_capacity(vector) == 0);

    // append
    for (int i = 0; i < N; i++)
    {
        silk_vector_push_back(vector, (const void*)(&i));
        assert(silk_vector_length(vector) == (i+1));
    }
    for (int i = 0; i < N; i++)
    {
        int n;
        assert(silk_vector_get(vector, i, (void*)(&n)) == true);
        assert(n == i);
    }
    for (int i = 0; i < N; i++)
    {
        int n = 233;
        assert(silk_vector_set(vector, i, (void*)(&n)) == true);
        assert(silk_vector_get(vector, i, (void*)(&n)) == true);
        assert(n == 233);
    }

    // insert
    silk_vector_clear(vector);
    silk_vector_reserve(vector, N);
    for (int i = 0; i < N; i++)
    {
        assert(silk_vector_push_front(vector, (void*)(&i)) == true);
    }
    for (int i = 0; i < N; i++)
    {
        assert(silk_vector_insert(vector, N, (void*)(&i)) == true);
    }

    // pop front
    for (int i = 0; i < N; i++)
    {
        int n;
        silk_vector_pop_front(vector, &n);
        assert(n == (N-1-i));
    }

    // recycle
    assert(silk_vector_length(vector) == N);
    silk_vector_recycle(vector);
    assert(silk_vector_capacity(vector) == N);

    // copy
    silk_vector_t copied = silk_vector_copy(vector);
    silk_vector_delete(vector);
    assert(silk_vector_length(copied) == N);
    assert(silk_vector_capacity(copied) == N);

    // pop back
    for (int i = 0; i < N; i++)
    {
        int n;
        silk_vector_pop_back(copied, &n);
        assert(n == i);
    }

    silk_vector_delete(copied);
}