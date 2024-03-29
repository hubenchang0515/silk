#include <silk/vector.h>
#include <silk/log.h>

#include <string.h>

struct SilkVector
{
    void* data;
    size_t element_size;
    size_t length;
    size_t capacity;
};

// get the V[I] element data pointer
#define SILK_VECTOR_ELEMENT(V, I)           ((void*)((uint8_t*)((V)->data) + (I)*((V)->element_size)))

// get the byte size from begin to I
#define SILK_VECTOR_SIZE_TO(V, I)       ((V)->element_size * (I))

// get the byte size from I to end
#define SILK_VECTOR_SIZE_FROM(V, I)        ((V)->element_size * ((V)->length - (I)))

static bool silk_vector_expand(silk_vector_t vector)
{
    SILK_ASSERT(vector != NULL, false);

    size_t capacity = vector->capacity;
    if (capacity == 0)
    {
        capacity = 1;
    }
    else if (capacity <= 1024)
    {
        capacity = 2 * capacity;
    }
    else
    {
        capacity = capacity + 1024;
    }

    void* data = silk_realloc(vector->data, vector->element_size * capacity);
    SILK_ASSERT(data != NULL, false);

    vector->data = data;
    vector->capacity = capacity;
    return true;
}

/*******************************************************
 * @brief check if capacity is enough, auto alloc
 * @param vector the vector
 * @param count count of new elements
 * @return whether is is enough
 *******************************************************/
static bool silk_vector_enough(silk_vector_t vector, size_t count)
{
    SILK_ASSERT(vector != NULL, false);

    while (vector->capacity <= vector->length + count)
    {
        SILK_ASSERT(silk_vector_expand(vector), false);
    }

    return true;
}

/*******************************************************
 * @brief create a vector
 * @param element_size the size of an element
 * @return the vector
 *******************************************************/
silk_vector_t silk_vector_new(size_t element_size)
{
    silk_vector_t vector = silk_alloc(sizeof(struct SilkVector));
    SILK_ASSERT(vector, NULL);

    vector->data = NULL;
    vector->element_size = element_size;
    vector->length = 0;
    vector->capacity = 0;
    return vector;
}

/*******************************************************
 * @brief delete a vector
 * @param vector the vector to be deleted
 *******************************************************/
void silk_vector_delete(silk_vector_t vector)
{
    SILK_ASSERT(vector != NULL);

    if (vector->data != NULL)
        silk_free(vector->data);

    silk_free(vector);
}

/*******************************************************
 * @brief clear a vector
 * @param vector the vector to be cleared
 *******************************************************/
void silk_vector_clear(silk_vector_t vector)
{
    SILK_ASSERT(vector != NULL);
    if (vector->data != NULL)
        silk_free(vector->data);
    vector->data = NULL;
    vector->capacity = 0;
    vector->length = 0;
}

/*******************************************************
 * @brief copy a vector
 * @param vector the vector to be copied
 * @return the copied vector 
 *******************************************************/
silk_vector_t silk_vector_copy(silk_vector_t vector)
{
    SILK_ASSERT(vector != NULL, NULL);

    silk_vector_t new_vector = silk_alloc(sizeof(struct SilkVector));
    SILK_ASSERT(new_vector != NULL, NULL);

    silk_copy(new_vector, vector, sizeof(struct SilkVector));
    new_vector->data = silk_alloc(vector->element_size * vector->capacity);
    SILK_ASSERT(new_vector->data != NULL, silk_free(new_vector), NULL);

    silk_copy(new_vector->data, vector->data, vector->element_size * vector->length);
    return new_vector;
}

/*******************************************************
 * @brief invoke callback for every elements
 *        see https://en.wikipedia.org/wiki/MapReduce
 * @param vector the vector
 * @param callback the callback function
 * @return whether it is successful
 *******************************************************/
bool silk_vector_map(silk_vector_t vector, silk_map_callback_t callback)
{
    SILK_ASSERT(vector != NULL, false);

    for (size_t i = 0; i < vector->length; i++)
    {
        callback(SILK_VECTOR_ELEMENT(vector, i));
    }

    return true;
}

/*******************************************************
 * @brief invoke callback for every elements like
 *        data = callback(data, element)
 *        see https://en.wikipedia.org/wiki/MapReduce
 * @param vector the vector
 * @param callback the callback function
 * @param data the data input init value and output result
 * @return the result value
 *******************************************************/
bool silk_vector_reduce(silk_vector_t vector, silk_reduce_callback_t callback, void* data)
{
    SILK_ASSERT(vector != NULL, false);

    for (size_t i = 0; i < vector->length; i++)
    {
        callback(data, SILK_VECTOR_ELEMENT(vector, i));
    }

    return true;
}

/*******************************************************
 * @brief get the raw data pointer of a vector
 * @param vector the vector
 * @return the data pointer
 *******************************************************/
void* silk_vector_data(silk_vector_t vector)
{
    SILK_ASSERT(vector != NULL, NULL);
    return vector->data;
}

/*******************************************************
 * @brief get the constant raw data pointer of a vector
 * @param vector the vector
 * @return the data pointer
 *******************************************************/
const void* silk_vector_const_data(silk_vector_t vector)
{
    SILK_ASSERT(vector != NULL, NULL);
    return (const void*)vector->data;
}

/*******************************************************
 * @brief get the element size of a vector
 * @param vector the vector
 * @return the element size
 *******************************************************/
size_t silk_vector_element_size(silk_vector_t vector)
{
    SILK_ASSERT(vector != NULL, 0);
    return vector->element_size;
}

/*******************************************************
 * @brief get the length of a vector
 * @param vector the vector
 * @return the length
 *******************************************************/
size_t silk_vector_length(silk_vector_t vector)
{
    SILK_ASSERT(vector != NULL, 0);
    return vector->length;
}

/*******************************************************
 * @brief get the capacity of a vector
 * @param vector the vector
 * @return the capacity
 *******************************************************/
size_t silk_vector_capacity(silk_vector_t vector)
{
    SILK_ASSERT(vector != NULL, 0);
    return vector->capacity;
}

/*******************************************************
 * @brief recyle the idle memory of a vector
 * @param vector the vector
 * @return whether it is successful
 *******************************************************/
bool silk_vector_recycle(silk_vector_t vector)
{
    SILK_ASSERT(vector != NULL, false);
    void* data = silk_realloc(vector->data, vector->element_size * vector->length);
    SILK_ASSERT(data != NULL, false);

    vector->data = data;
    vector->capacity = vector->length;
    return true;
}

/*******************************************************
 * @brief reserve enough memory of a vector
 * @param vector the vector
 * @return whether it is successful
 *******************************************************/
bool silk_vector_reserve(silk_vector_t vector, size_t capacity)
{
    SILK_ASSERT(vector != NULL, false);
    if (vector->capacity >= capacity)
        return true;

    void* data = silk_realloc(vector->data, vector->element_size * capacity);
    SILK_ASSERT(data != NULL, false);

    vector->data = data;
    vector->capacity = capacity;
    return true;
}

/*******************************************************
 * @brief insert elements into a vector
 * @param vector the vector
 * @param index the index
 * @param data the first element address
 * @param count the count of elements
 * @return whether it is successful
 *******************************************************/
bool silk_vector_inserts(silk_vector_t vector, size_t index, const void* data, size_t count)
{
    SILK_ASSERT(vector != NULL, false);
    SILK_ASSERT(data != NULL, false);
    SILK_ASSERT(index <= vector->length, false);
    SILK_ASSERT(silk_vector_enough(vector, count), false);

    silk_overlap_copy(SILK_VECTOR_ELEMENT(vector, index+count), SILK_VECTOR_ELEMENT(vector, index), SILK_VECTOR_SIZE_FROM(vector, index));
    silk_copy(SILK_VECTOR_ELEMENT(vector, index), data, vector->element_size * count);
    vector->length += count;
    return true;
}

/*******************************************************
 * @brief insert an element into a vector
 * @param vector the vector
 * @param index the index
 * @param data the element
 * @return whether it is successful
 *******************************************************/
bool silk_vector_insert(silk_vector_t vector, size_t index, const void* data)
{
    return silk_vector_inserts(vector, index, data, 1);
}

/*******************************************************
 * @brief append an element into a vector
 * @param vector the vector
 * @param data the element
 * @return whether it is successful
 *******************************************************/
bool silk_vector_append(silk_vector_t vector, const void* data)
{
    return silk_vector_insert(vector, vector->length, data);
}

/*******************************************************
 * @brief remove elements from a vector
 * @param vector the vector
 * @param index the index
 * @param count the count of elements
 * @return whether it is successful
 *******************************************************/
bool silk_vector_removes(silk_vector_t vector, size_t index, size_t count)
{
    SILK_ASSERT(vector != NULL, false);
    SILK_ASSERT(index + count - 1 < vector->length, false);

    silk_overlap_copy(SILK_VECTOR_ELEMENT(vector, index), 
                        SILK_VECTOR_ELEMENT(vector, index+count), 
                        SILK_VECTOR_SIZE_FROM(vector, index+count));
    vector->length -= count;
    return true;
}

/*******************************************************
 * @brief remove an element from a vector
 * @param vector the vector
 * @param index the index
 * @return whether it is successful
 *******************************************************/
bool silk_vector_remove(silk_vector_t vector, size_t index)
{
    return silk_vector_removes(vector, index, 1);
}

/*******************************************************
 * @brief set an element value of a vector
 * @param vector the vector
 * @param index the index
 * @param data the element value
 * @return whether it is successful
 *******************************************************/
bool silk_vector_set(silk_vector_t vector, size_t index, const void* data)
{
    SILK_ASSERT(vector != NULL, false);
    SILK_ASSERT(index < vector->length, false);

    silk_copy(SILK_VECTOR_ELEMENT(vector, index), data, vector->element_size);
    return true;
}

/*******************************************************
 * @brief get an element value of a vector
 * @param vector the vector
 * @param index the index
 * @param data return the element value
 * @return whether it is successful
 *******************************************************/
bool silk_vector_get(silk_vector_t vector, size_t index, void* data)
{
    SILK_ASSERT(vector != NULL, false);
    SILK_ASSERT(index < vector->length, false);

    silk_copy(data, SILK_VECTOR_ELEMENT(vector, index), vector->element_size);
    return true;
}

/*******************************************************
 * @brief push an element to the front of a vector
 * @param vector the vector
 * @param data the element 
 * @return whether it is successful
 *******************************************************/
bool silk_vector_push_front(silk_vector_t vector, const void* data)
{
    SILK_ASSERT(vector != NULL, false);

    return silk_vector_insert(vector, 0, data);
}

/*******************************************************
 * @brief push an element to the back of a vector
 * @param vector the vector
 * @param data the element 
 * @return whether it is successful
 *******************************************************/
bool silk_vector_push_back(silk_vector_t vector, const void* data)
{
    SILK_ASSERT(vector != NULL, false);

    return silk_vector_append(vector, data);
}

/*******************************************************
 * @brief pop an element from the front of a vector
 * @param vector the vector
 * @param data return the element, nullable
 * @return whether it is successful
 *******************************************************/
bool silk_vector_pop_front(silk_vector_t vector, void* data)
{
    SILK_ASSERT(vector != NULL, false);
    SILK_ASSERT(vector->length > 0, false);

    if (data != NULL)
        SILK_ASSERT(silk_vector_get(vector, 0, data), false);

    return silk_vector_remove(vector, 0);
}

/*******************************************************
 * @brief pop an element from the back of a vector
 * @param vector the vector
 * @param data return the element, nullable
 * @return whether it is successful
 *******************************************************/
bool silk_vector_pop_back(silk_vector_t vector, void* data)
{
    SILK_ASSERT(vector != NULL, false);
    SILK_ASSERT(vector->length > 0, false);

    if (data != NULL)
        SILK_ASSERT(silk_vector_get(vector, vector->length-1, data), false);

    return silk_vector_remove(vector, vector->length-1);
}

/*******************************************************
 * @brief default compare function implemented by memcmp
 * @note  this function compare byte by byte
 *        so it can be used to determine if value is equal, 
 *        but it cannot compare the values of those type
 *        like little-endian int, float and double
 * @param x a value to compare
 * @param y a value to compare
 * @param vector the vector
 * @return negative value while x < y
 *         positive value while x > y
 *         0 while x == y
 *******************************************************/
int silk_vector_default_compare(const void* x, const void* y, const void* userdata)
{
    SILK_ASSERT(x != NULL, 0);
    SILK_ASSERT(y != NULL, 0);
    SILK_ASSERT(userdata != NULL, 0);

    const silk_vector_t vector = (const silk_vector_t)(userdata);
    return memcmp(x, y, vector->element_size);
}

/*******************************************************
 * @brief find an element in vector
 * @param vector the vector
 * @param data the element value
 * @param begin the begin index
 * @param compare function to compare
 * @return index of the element, or 
 *******************************************************/
size_t silk_vector_find(silk_vector_t vector, const void* data, size_t begin, silk_compare_t compare)
{
    SILK_ASSERT(vector != NULL, SILK_INVALID_INDEX);
    SILK_ASSERT(data != NULL, SILK_INVALID_INDEX);
    SILK_ASSERT(compare != NULL, SILK_INVALID_INDEX);
    
    for (size_t i = begin; i < vector->length; i++)
    {
        if (compare(SILK_VECTOR_ELEMENT(vector, i), data, vector) == 0)
        {
            return i;
        }
    }

    return SILK_INVALID_INDEX;
}

/*******************************************************
 * @brief sort a vector by quick sort algorithm 
 *        with stack rather than recursion
 * @param vector the vector
 * @param compare function to compare
 * @return whether it is successful
 *******************************************************/
bool silk_vector_sort(silk_vector_t vector, silk_compare_t compare)
{
    SILK_ASSERT(vector != NULL, false);
    SILK_ASSERT(compare != NULL, false);

    if (vector->length <= 1)
        return true;

    silk_vector_t stack = silk_vector_new(sizeof(size_t));
    SILK_ASSERT(stack != NULL, false);
    void* buffer = silk_alloc(vector->element_size);
    SILK_ASSERT(buffer != NULL, silk_vector_delete(stack), false);

    size_t begin = 0;
    size_t end = vector->length - 1;
    SILK_ASSERT(silk_vector_push_back(stack, &begin), silk_free(buffer), silk_vector_delete(stack), false);
    SILK_ASSERT(silk_vector_push_back(stack, &end), silk_free(buffer), silk_vector_delete(stack), false);

    while (stack->length > 0)
    {
        silk_vector_pop_back(stack, &end);
        silk_vector_pop_back(stack, &begin);
        size_t base = begin;
        size_t left = begin;
        size_t right = end;
        while (left < right)
        {
            // find right smaller than base
            for (; right > left; right--)
            {
                if (compare(SILK_VECTOR_ELEMENT(vector, right), SILK_VECTOR_ELEMENT(vector, base), vector) < 0)
                {
                    break;
                }
            }

            // find left greater than base
            for (; left < right; left++)
            {
                if (compare(SILK_VECTOR_ELEMENT(vector, left), SILK_VECTOR_ELEMENT(vector, base), vector) > 0)
                {
                    break;
                }
            }

            if (left == right)
                break;

            // swap right and left
            silk_copy(buffer, SILK_VECTOR_ELEMENT(vector, left), vector->element_size);
            silk_copy(SILK_VECTOR_ELEMENT(vector, left),  SILK_VECTOR_ELEMENT(vector, right), vector->element_size);
            silk_copy(SILK_VECTOR_ELEMENT(vector, right),  buffer, vector->element_size);
        }

        // swap base and meetion
        silk_copy(buffer, SILK_VECTOR_ELEMENT(vector, left), vector->element_size);
        silk_copy(SILK_VECTOR_ELEMENT(vector, left), SILK_VECTOR_ELEMENT(vector, base), vector->element_size);
        silk_copy(SILK_VECTOR_ELEMENT(vector, base),  buffer, vector->element_size);

        // push the range of next turn 
        if (begin + 1 < left)
        {
            size_t index = left - 1;
            SILK_ASSERT(silk_vector_push_back(stack, &begin), silk_free(buffer), silk_vector_delete(stack), false);
            SILK_ASSERT(silk_vector_push_back(stack, &index), silk_free(buffer), silk_vector_delete(stack), false);
        }
        if (end - 1> left)
        {
            size_t index = left + 1;
            SILK_ASSERT(silk_vector_push_back(stack, &index), silk_free(buffer), silk_vector_delete(stack), false);
            SILK_ASSERT(silk_vector_push_back(stack, &end), silk_free(buffer), silk_vector_delete(stack), false);
        }
    }

    silk_free(buffer);
    silk_vector_delete(stack);
    return true;
}