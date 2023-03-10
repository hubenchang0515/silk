#include "vector.h"
#include "log.h"

struct SilkVector
{
    void* data;
    size_t element_size;
    size_t length;
    size_t capacity;
};

#define SILK_VEC_POS(V,I)       ((void*)((uint8_t*)((V)->data) + (I)*((V)->element_size)))
#define SILK_VEC_BEFORE(V, I)   ((V)->element_size * I)
#define SILK_VEC_AFTER(V, I)   ((V)->element_size * ((V)->length - I))

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
    if (new_vector == NULL)
        return NULL;

    silk_copy(new_vector, vector, sizeof(struct SilkVector));
    new_vector->data = silk_alloc(vector->element_size * vector->capacity);
    if (new_vector->data == NULL)
    {
        silk_free(new_vector);
        return NULL;
    }

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

    uint8_t* ptr = (uint8_t*)(vector->data);
    silk_copy(SILK_VEC_POS(vector, vector->length), data, vector->element_size);
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

    uint8_t* ptr = (uint8_t*)(vector->data);
    silk_copy(SILK_VEC_POS(vector, index+1), SILK_VEC_POS(vector, index), SILK_VEC_AFTER(vector, index));
    silk_copy(SILK_VEC_POS(vector, index), data, vector->element_size);
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
    SILK_ASSERT(index <= vector->length);

    silk_copy(SILK_VEC_POS(vector, index), SILK_VEC_POS(vector, index+1), SILK_VEC_AFTER(vector, index));
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
    SILK_ASSERT(index <= vector->length);

    silk_copy(SILK_VEC_POS(vector, index), data, vector->element_size);
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
    SILK_ASSERT(index <= vector->length);

    silk_copy(data, SILK_VEC_POS(vector, index), vector->element_size);
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
    if (data != NULL && !silk_vector_get(vector, vector->length-1, data))
        return false;

    return silk_vector_remove(vector, vector->length-1);
}