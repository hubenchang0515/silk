#include <silk/log.h>
#include <silk/vector.h>

#define N 4096

void test_vector_map_callback(void* element)
{
    int* p = (int*)element;
    *p *= 2;
}

void test_vector_map()
{
    silk_vector_t vector = silk_vector_new(sizeof(int));

    for (int i = 0; i < N; i++)
    {
        silk_vector_append(vector, &i);    
    }

    silk_vector_map(vector, test_vector_map_callback);

    for (int i = 0; i < N; i++)
    {
        int n;
        silk_vector_pop_front(vector, &n);
        SILK_ASSERT(n == i*2);    
    }

    silk_vector_delete(vector);
}

void test_vector_reduce_callback(void* data, void* element)
{
    int* p1 = (int*)data;
    int* p2 = (int*)element;

    *p1 = *p1 + *p2;
}

void test_vector_reduce()
{
    silk_vector_t vector = silk_vector_new(sizeof(int));

    int sum = 0;
    for (int i = 0; i < N; i++)
    {
        silk_vector_append(vector, &i); 
        sum += i;   
    }

    int result = 0;
    silk_vector_reduce(vector, test_vector_reduce_callback, &result);
    SILK_ASSERT(result == sum);
    
    silk_vector_delete(vector);
}

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
        SILK_ASSERT(silk_vector_find(vector, (void*)(&i), 0, silk_vector_default_compare) == SILK_INVALID_INDEX);
        SILK_ASSERT(silk_vector_push_back(vector, (void*)(&i)) == true);
        SILK_ASSERT(silk_vector_length(vector) == (size_t)(i+1));
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
    silk_vector_reserve(vector, 2*N);
    silk_vector_reserve(vector, N);
    for (int i = 0; i < N; i++)
    {
        SILK_ASSERT(silk_vector_push_front(vector, (void*)(&i)) == true);
    }
    for (int i = 0; i < N; i++)
    {
        SILK_ASSERT(silk_vector_insert(vector, N, (void*)(&i)) == true);
    }

    // find
    for (int i = 0; i < N; i++)
    {
        SILK_ASSERT(silk_vector_find(vector, (void*)(&i), 0, silk_vector_default_compare) == (size_t)(N - i - 1));
        SILK_ASSERT(silk_vector_find(vector, (void*)(&i), N, silk_vector_default_compare) == (size_t)(2*N - i - 1));
    }
    
    // sort 
    silk_vector_sort(vector, silk_compare_int);

    // pop front
    for (int i = 0; i < N; i++)
    {
        int n;
        SILK_ASSERT(silk_vector_pop_front(vector, (void*)(&n)) == true);
        SILK_ASSERT(n == i/2);
    }

    // recycle
    SILK_ASSERT(silk_vector_length(vector) == N);
    silk_vector_recycle(vector);
    SILK_ASSERT(silk_vector_capacity(vector) == N);

    // copy
    silk_vector_t copied = silk_vector_copy(vector);
    SILK_ASSERT(silk_vector_length(copied) == N);
    SILK_ASSERT(silk_vector_capacity(copied) == N);

    // clear
    silk_vector_clear(vector);
    SILK_ASSERT(silk_vector_data(vector) == NULL);
    SILK_ASSERT(silk_vector_const_data(vector) == NULL);
    SILK_ASSERT(silk_vector_length(vector) == 0);
    SILK_ASSERT(silk_vector_capacity(vector) == 0);

    // sort length <= 1
    {
        for (int i = 0; i < 2; i++)
            silk_vector_append(vector, &i);
        silk_vector_sort(vector, silk_compare_int); // sort length == 2
        SILK_ASSERT(silk_vector_pop_back(vector, NULL) == true);
        silk_vector_sort(vector, silk_compare_int); // sort length == 1
        SILK_ASSERT(silk_vector_pop_front(vector, NULL) == true);
        silk_vector_sort(vector, silk_compare_int); // sort length == 0
    }

    // clear empty vector
    silk_vector_clear(vector);

    // delete empty vector
    silk_vector_delete(vector);

    // pop back
    for (int i = 0; i < N; i++)
    {
        int n;
        silk_vector_pop_back(copied, (void*)(&n));
        SILK_ASSERT(n == N - i/2 - 1);
    }

    // delete
    silk_vector_delete(copied);

    test_vector_map();
    test_vector_reduce();
}