#include <silk/log.h>
#include <silk/list.h>

#define TYPE float
#define N 2048

void test_list_map_callback(void* element)
{
    int* p = (int*)element;
    *p *= 2;
}

void test_list_map()
{
    silk_list_t list = silk_list_new(sizeof(int));

    for (int i = 0; i < N; i++)
    {
        silk_list_push_back(list, &i);    
    }

    silk_list_map(list, test_list_map_callback);

    for (int i = 0; i < N; i++)
    {
        int n;
        silk_list_pop_front(list, &n);
        SILK_ASSERT(n == i*2);    
    }

    silk_list_delete(list);
}

void test_list_reduce_callback(void* data, void* element)
{
    int* p1 = (int*)data;
    int* p2 = (int*)element;

    *p1 = *p1 + *p2;
}

void test_list_reduce()
{
    silk_list_t list = silk_list_new(sizeof(int));

    int sum = 0;
    for (int i = 0; i < N; i++)
    {
        silk_list_push_back(list, &i); 
        sum += i;   
    }

    int result = 0;
    silk_list_reduce(list, test_list_reduce_callback, &result);
    SILK_ASSERT(result == sum);
    
    silk_list_delete(list);
}

void test_list()
{
    silk_list_t list = silk_list_new(sizeof(TYPE));
    SILK_ASSERT(list != NULL);

    SILK_ASSERT(silk_list_element_size(list) == sizeof(TYPE));
    SILK_ASSERT(silk_list_length(list) == 0);
    SILK_ASSERT(silk_list_head(list) == NULL);
    SILK_ASSERT(silk_list_tail(list) == NULL);

    // push front
    for (int i = 0; i < N; i++)
    {
        TYPE data = i * 2.0f;
        SILK_ASSERT(silk_list_push_front(list, &data) != NULL);
        SILK_ASSERT(silk_list_length(list) == (size_t)(i + 1));
    }
    SILK_ASSERT(silk_list_next(silk_list_tail(list)) == NULL);
    SILK_ASSERT(silk_list_prev(silk_list_head(list)) == NULL);

    // at backward
    for (int i = 0; i < N; i++)
    {
        TYPE data;
        silk_list_node_t node = silk_list_at_backward(list, i);
        SILK_ASSERT(silk_list_get(node, &data) == true);
        SILK_ASSERT(data == 2.0f * i);
    }

    // pop back
    for (int i = 0; i < N; i++)
    {
        TYPE data;
        silk_list_pop_back(list, &data);
        SILK_ASSERT(data == i * 2.0f);
    }
    SILK_ASSERT(silk_list_head(list) == NULL);
    SILK_ASSERT(silk_list_tail(list) == NULL);

    // push back
    for (int i = 0; i < N; i++)
    {
        TYPE data = i * 2.0f;
        SILK_ASSERT(silk_list_push_back(list, &data) != NULL);
        SILK_ASSERT(silk_list_length(list) == (size_t)(i + 1));
    }

    // at
    for (int i = 0; i < N; i++)
    {
        TYPE data;
        silk_list_node_t node = silk_list_at(list, i);
        SILK_ASSERT(silk_list_get(node, &data) == true);
        SILK_ASSERT(data == 2.0f * i);
    }

    // pop front
    for (int i = 0; i < N; i++)
    {
        TYPE data;
        silk_list_pop_front(list, &data);
        SILK_ASSERT(data == i * 2.0f);
    }
    SILK_ASSERT(silk_list_head(list) == NULL);
    SILK_ASSERT(silk_list_tail(list) == NULL);

    for (int i = 0; i < N; i++)
    {
        TYPE data = 0.0f;
        SILK_ASSERT(silk_list_push_front(list, &data) != NULL);
        SILK_ASSERT(silk_list_length(list) == (size_t)(i + 1));
    }

    // next
    {
        silk_list_node_t node = silk_list_head(list);
        for (int i = 0; i < N; i++)
        {
            TYPE data = 10.0f * i;
            SILK_ASSERT(silk_list_set(node, &data) == true);
            node = silk_list_next(node);
        }
        SILK_ASSERT(node == NULL);
    }

    // prev
    {
        silk_list_node_t node = silk_list_tail(list);
        for (int i = 0; i < N; i++)
        {
            TYPE data;
            SILK_ASSERT(silk_list_get(node, &data) == true);
            SILK_ASSERT(data == 10.0f * (N-i-1));
            node = silk_list_prev(node);
        }
        SILK_ASSERT(node == NULL);
    }

    // copy
    {
        silk_list_t new_list = silk_list_copy(list);
        silk_list_node_t node = silk_list_tail(new_list);
        for (int i = 0; i < N; i++)
        {
            TYPE data;
            SILK_ASSERT(silk_list_get(node, &data) == true);
            SILK_ASSERT(data == 10.0f * (N-i-1));
            node = silk_list_prev(node);
        }
        SILK_ASSERT(node == NULL);
        silk_list_delete(new_list);
    }

    // find and insert
    {
        TYPE data = 10.0f * N;
        silk_list_node_t node = silk_list_find(silk_list_head(list), &data, silk_list_default_compare);
        SILK_ASSERT(node == NULL);

        data = 10.0f * (N/2);
        node = silk_list_find(silk_list_head(list), &data, silk_list_default_compare);
        SILK_ASSERT(node == silk_list_at(list, N/2));

        data = 233.0f;
        for (int i = 0; i < 10; i++)
        {
            silk_list_insert_before(node, &data);
            silk_list_insert_after(node, &data);
        }
        SILK_ASSERT(silk_list_length(list) == N + 10*2);

        node = silk_list_head(list);
        for (int i = 0; i < 10; i++)
        {
            node = silk_list_find(node, &data, silk_list_default_compare);
            SILK_ASSERT(node == silk_list_at(list, N/2 + i));
            node = silk_list_next(node);
        }
    }

    // sort
    {
        silk_list_clear(list);
        silk_list_sort(list, silk_compare_float);
        for (int i = 0; i < N; i++)
        {
            TYPE data = i * 1.0f;
            SILK_ASSERT(silk_list_push_front(list, &data) != NULL);
        }
        for (int i = 0; i < N; i++)
        {
            TYPE data = i * 1.0f;
            SILK_ASSERT(silk_list_push_front(list, &data) != NULL);
        }

        silk_list_sort(list, silk_compare_float);
        silk_list_node_t node = silk_list_head(list);
        for (int i = 0; i < N; i++)
        {
            SILK_ASSERT(node != NULL);
            TYPE data;
            SILK_ASSERT(silk_list_get(node, &data) == true);
            SILK_ASSERT(data == i/2 *1.0f);
            node = silk_list_next(node);
        }
    }

    silk_list_delete(list);

    test_list_map();
    test_list_reduce();
}