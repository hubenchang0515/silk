#include "vector.h"
#include "log.h"

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
    SILK_ASSERT(vector != NULL);

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
    if (data == NULL)
        return false;

    vector->data = data;
    vector->capacity = capacity;
    return true;
}

static bool silk_vector_enough(silk_vector_t vector)
{
    SILK_ASSERT(vector != NULL);

    if (vector->capacity > vector->length)
        return true;

    return silk_vector_expand(vector);
}

/*******************************************************
 * @brief create a vector
 * @param element_size the size of a element
 * @return the vector
 *******************************************************/
silk_vector_t silk_vector_new(size_t element_size)
{
    silk_vector_t vector = silk_alloc(sizeof(struct SilkVector));
    SILK_ASSERT(vector);

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
    SILK_ASSERT(vector != NULL);

    silk_vector_t new_vector = silk_alloc(sizeof(struct SilkVector));
    SILK_ASSERT(new_vector != NULL);

    silk_copy(new_vector, vector, sizeof(struct SilkVector));
    new_vector->data = silk_alloc(vector->element_size * vector->capacity);
    SILK_ASSERT(new_vector->data != NULL);

    silk_copy(new_vector->data, vector->data, vector->element_size * vector->length);
    return new_vector;
}

/*******************************************************
 * @brief get the raw data pointer of a vector
 * @param vector the vector
 * @return the data pointer
 *******************************************************/
void* silk_vector_data(silk_vector_t vector)
{
    SILK_ASSERT(vector != NULL);
    return vector->data;
}

/*******************************************************
 * @brief get the constant raw data pointer of a vector
 * @param vector the vector
 * @return the data pointer
 *******************************************************/
const void* silk_vector_const_data(silk_vector_t vector)
{
    SILK_ASSERT(vector != NULL);
    return (const void*)vector->data;
}

/*******************************************************
 * @brief get the element size of a vector
 * @param vector the vector
 * @return the element size
 *******************************************************/
size_t silk_vector_element_size(silk_vector_t vector)
{
    SILK_ASSERT(vector != NULL);
    return vector->element_size;
}

/*******************************************************
 * @brief get the length of a vector
 * @param vector the vector
 * @return the length
 *******************************************************/
size_t silk_vector_length(silk_vector_t vector)
{
    SILK_ASSERT(vector != NULL);
    return vector->length;
}

/*******************************************************
 * @brief get the capacity of a vector
 * @param vector the vector
 * @return the capacity
 *******************************************************/
size_t silk_vector_capacity(silk_vector_t vector)
{
    SILK_ASSERT(vector != NULL);
    return vector->capacity;
}

/*******************************************************
 * @brief recyle the idle memory of a vector
 * @param vector the vector
 * @return whether it is successful
 *******************************************************/
bool silk_vector_recycle(silk_vector_t vector)
{
    SILK_ASSERT(vector != NULL);
    void* data = silk_realloc(vector->data, vector->element_size * vector->length);
    if (data == NULL)
        return false;

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
    SILK_ASSERT(vector != NULL);
    if (vector->capacity >= capacity)
        return true;

    void* data = silk_realloc(vector->data, vector->element_size * capacity);
    if (data == NULL)
        return false;

    vector->data = data;
    vector->capacity = capacity;
    return true;
}

/*******************************************************
 * @brief append a element into a vector
 * @param vector the vector
 * @param data the element
 * @return whether it is successful
 *******************************************************/
bool silk_vector_append(silk_vector_t vector, const void* data)
{
    SILK_ASSERT(vector != NULL);
    SILK_ASSERT(data != NULL);

    if (!silk_vector_enough(vector))
        return false;

    silk_copy(SILK_VECTOR_ELEMENT(vector, vector->length), data, vector->element_size);
    vector->length += 1;
    return true;
}

/*******************************************************
 * @brief insert a element into a vector
 * @param vector the vector
 * @param index the index
 * @param data the element
 * @return whether it is successful
 *******************************************************/
bool silk_vector_insert(silk_vector_t vector, size_t index, const void* data)
{
    SILK_ASSERT(vector != NULL);
    SILK_ASSERT(data != NULL);
    SILK_ASSERT(index <= vector->length);

    if (!silk_vector_enough(vector))
        return false;

    silk_copy(SILK_VECTOR_ELEMENT(vector, index+1), SILK_VECTOR_ELEMENT(vector, index), SILK_VECTOR_SIZE_FROM(vector, index));
    silk_copy(SILK_VECTOR_ELEMENT(vector, index), data, vector->element_size);
    vector->length += 1;
    return true;
}

/*******************************************************
 * @brief remove a element from a vector
 * @param vector the vector
 * @param index the index
 * @return whether it is successful
 *******************************************************/
bool silk_vector_remove(silk_vector_t vector, size_t index)
{
    SILK_ASSERT(vector != NULL);
    SILK_ASSERT(index < vector->length);

    silk_copy(SILK_VECTOR_ELEMENT(vector, index), SILK_VECTOR_ELEMENT(vector, index+1), SILK_VECTOR_SIZE_FROM(vector, index+1));
    vector->length -= 1;
    return true;
}

/*******************************************************
 * @brief set a element value of a vector
 * @param vector the vector
 * @param index the index
 * @param data the element value
 * @return whether it is successful
 *******************************************************/
bool silk_vector_set(silk_vector_t vector, size_t index, const void* data)
{
    SILK_ASSERT(vector != NULL);
    SILK_ASSERT(index < vector->length);

    silk_copy(SILK_VECTOR_ELEMENT(vector, index), data, vector->element_size);
    return true;
}

/*******************************************************
 * @brief get a element value of a vector
 * @param vector the vector
 * @param index the index
 * @param data return the element value
 * @return whether it is successful
 *******************************************************/
bool silk_vector_get(silk_vector_t vector, size_t index, void* data)
{
    SILK_ASSERT(vector != NULL);
    SILK_ASSERT(index < vector->length);

    silk_copy(data, SILK_VECTOR_ELEMENT(vector, index), vector->element_size);
    return true;
}

/*******************************************************
 * @brief push a element to the front of a vector
 * @param vector the vector
 * @param data the element 
 * @return whether it is successful
 *******************************************************/
bool silk_vector_push_front(silk_vector_t vector, const void* data)
{
    SILK_ASSERT(vector != NULL);

    return silk_vector_insert(vector, 0, data);
}

/*******************************************************
 * @brief push a element to the back of a vector
 * @param vector the vector
 * @param data the element 
 * @return whether it is successful
 *******************************************************/
bool silk_vector_push_back(silk_vector_t vector, const void* data)
{
    SILK_ASSERT(vector != NULL);

    return silk_vector_append(vector, data);
}

/*******************************************************
 * @brief pop a element from the front of a vector
 * @param vector the vector
 * @param data return the element, nullable
 * @return whether it is successful
 *******************************************************/
bool silk_vector_pop_front(silk_vector_t vector, void* data)
{
    SILK_ASSERT(vector != NULL);

    if (vector->length == 0)
        return false;

    if (data != NULL && !silk_vector_get(vector, 0, data))
        return false;

    return silk_vector_remove(vector, 0);
}

/*******************************************************
 * @brief pop a element from the back of a vector
 * @param vector the vector
 * @param data return the element, nullable
 * @return whether it is successful
 *******************************************************/
bool silk_vector_pop_back(silk_vector_t vector, void* data)
{
    SILK_ASSERT(vector != NULL);

    if (vector->length == 0)
        return false;

    if (data != NULL && !silk_vector_get(vector, vector->length-1, data))
        return false;

    return silk_vector_remove(vector, vector->length-1);
}

/*******************************************************
 * @brief default compare function with memcmp
 * @param x a value to compare
 * @param y a value to compare
 * @param vector the vector
 * @return negative value while x < y
 *         positive value while x > y
 *         0 while x == y
 *******************************************************/
int silk_vector_default_compare(const void* x, const void* y, const void* userdata)
{
    SILK_ASSERT(x != NULL);
    SILK_ASSERT(y != NULL);
    SILK_ASSERT(userdata != NULL);

    const silk_vector_t vector = (const silk_vector_t)(userdata);
    return memcmp(x, y, vector->element_size);
}

/*******************************************************
 * @brief find a element in vector
 * @param vector the vector
 * @param data the element value
 * @param begin the begin index
 * @param compare function to compare
 * @return index of the element, or 
 *******************************************************/
size_t silk_vector_find(silk_vector_t vector, const void* data, size_t begin, silk_compare_fn compare)
{
    SILK_ASSERT(vector != NULL);
    SILK_ASSERT(data != NULL);
    SILK_ASSERT(compare != NULL);
    
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
 *******************************************************/
void silk_vector_sort(silk_vector_t vector, silk_compare_fn compare)
{
    SILK_ASSERT(vector != NULL);
    SILK_ASSERT(compare != NULL);

    if (vector->length <= 1)
        return;

    silk_vector_t stack = silk_vector_new(sizeof(size_t));
    SILK_ASSERT(stack != NULL);
    void* buffer = silk_alloc(vector->element_size);
    SILK_ASSERT(buffer != NULL);

    size_t begin = 0;
    size_t end = vector->length - 1;
    silk_vector_push_back(stack, &begin);
    silk_vector_push_back(stack, &end);

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
            silk_vector_push_back(stack, &begin);
            silk_vector_push_back(stack, &index);
        }
        if (end - 1> left)
        {
            size_t index = left + 1;
            silk_vector_push_back(stack, &index);
            silk_vector_push_back(stack, &end);
        }
    }

    silk_free(buffer);
    silk_vector_delete(stack);
}