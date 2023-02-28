#ifndef SILK_VECTOR_H
#define SILK_VECTOR_H

#include "common.h"

typedef struct SilkVector* silk_vector_t;

/*******************************************************
 * @brief create a vector
 * @param element_size the size of a element
 * @return the vector
 *******************************************************/
silk_vector_t silk_vector_new(size_t element_size);

/*******************************************************
 * @brief delete a vector
 * @param vector the vector to be deleted
 *******************************************************/
void silk_vector_delete(silk_vector_t vector);

/*******************************************************
 * @brief clear a vector
 * @param vector the vector to be cleared
 *******************************************************/
void silk_vector_clear(silk_vector_t vector);

/*******************************************************
 * @brief copy a vector
 * @param vector the vector to be copied
 * @return the copied vector 
 *******************************************************/
silk_vector_t silk_vector_copy(silk_vector_t vector);

/*******************************************************
 * @brief get the raw data pointer of a vector
 * @param vector the vector
 * @return the data pointer
 *******************************************************/
void* silk_vector_data(silk_vector_t vector);

/*******************************************************
 * @brief get the constant raw data pointer of a vector
 * @param vector the vector
 * @return the data pointer
 *******************************************************/
const void* silk_vector_const_data(silk_vector_t vector);

/*******************************************************
 * @brief get the element size of a vector
 * @param vector the vector
 * @return the element size
 *******************************************************/
size_t silk_vector_element_size(silk_vector_t vector);

/*******************************************************
 * @brief get the length of a vector
 * @param vector the vector
 * @return the length
 *******************************************************/
size_t silk_vector_length(silk_vector_t vector);

/*******************************************************
 * @brief get the capacity of a vector
 * @param vector the vector
 * @return the capacity
 *******************************************************/
size_t silk_vector_capacity(silk_vector_t vector);

/*******************************************************
 * @brief recyle the idle memory of a vector
 * @param vector the vector
 * @return whether it is successful
 *******************************************************/
bool silk_vector_recycle(silk_vector_t vector);

/*******************************************************
 * @brief reserve enough memory of a vector
 * @param vector the vector
 * @return whether it is successful
 *******************************************************/
bool silk_vector_reserve(silk_vector_t vector, size_t capacity);

/*******************************************************
 * @brief append a element into a vector
 * @param vector the vector
 * @param data the element
 * @return whether it is successful
 *******************************************************/
bool silk_vector_append(silk_vector_t vector, const void* data);

/*******************************************************
 * @brief insert a element into a vector
 * @param vector the vector
 * @param index the index
 * @param data the element
 * @return whether it is successful
 *******************************************************/
bool silk_vector_insert(silk_vector_t vector, size_t index, const void* data);

/*******************************************************
 * @brief remove a element from a vector
 * @param vector the vector
 * @param index the index
 * @return whether it is successful
 *******************************************************/
bool silk_vector_remove(silk_vector_t vector, size_t index);

/*******************************************************
 * @brief set a element value of a vector
 * @param vector the vector
 * @param index the index
 * @param data the element value
 * @return whether it is successful
 *******************************************************/
bool silk_vector_set(silk_vector_t vector, size_t index, const void* data);

/*******************************************************
 * @brief get a element value of a vector
 * @param vector the vector
 * @param index the index
 * @param data return the element value
 * @return whether it is successful
 *******************************************************/
bool silk_vector_get(silk_vector_t vector, size_t index, void* data);

/*******************************************************
 * @brief push a element to the front of a vector
 * @param vector the vector
 * @param data the element 
 * @return whether it is successful
 *******************************************************/
bool silk_vector_push_front(silk_vector_t vector, const void* data);

/*******************************************************
 * @brief push a element to the back of a vector
 * @param vector the vector
 * @param data the element 
 * @return whether it is successful
 *******************************************************/
bool silk_vector_push_back(silk_vector_t vector, const void* data);

/*******************************************************
 * @brief pop a element from the front of a vector
 * @param vector the vector
 * @param data return the element, nullable
 * @return whether it is successful
 *******************************************************/
bool silk_vector_pop_front(silk_vector_t vector, void* data);

/*******************************************************
 * @brief pop a element from the back of a vector
 * @param vector the vector
 * @param data return the element, nullable
 * @return whether it is successful
 *******************************************************/
bool silk_vector_pop_back(silk_vector_t vector, void* data);

#endif // SILK_VECTOR_H