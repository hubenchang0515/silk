#ifndef SILK_VECTOR_H
#define SILK_VECTOR_H

#include "common.h"
#include "compare.h"
#include "memory.h"

typedef struct SilkVector* silk_vector_t;

/*******************************************************
 * @brief create a vector
 * @param element_size the size of an element
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
 * @brief invoke callback for every elements
 *        see https://en.wikipedia.org/wiki/MapReduce
 * @param vector the vector
 * @param callback the callback function
 * @return whether it is successful
 *******************************************************/
bool silk_vector_map(silk_vector_t vector, silk_map_callback_t callback);

/*******************************************************
 * @brief invoke callback for every elements like
 *        data = callback(data, element)
 *        see https://en.wikipedia.org/wiki/MapReduce
 * @param vector the vector
 * @param callback the callback function
 * @param data the data input init value and output result
 * @return the result value
 *******************************************************/
bool silk_vector_reduce(silk_vector_t vector, silk_reduce_callback_t callback, void* data);

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
 * @brief insert elements into a vector
 * @param vector the vector
 * @param index the index
 * @param data the first element address
 * @param count the count of elements
 * @return whether it is successful
 *******************************************************/
bool silk_vector_inserts(silk_vector_t vector, size_t index, const void* data, size_t count);

/*******************************************************
 * @brief insert an element into a vector
 * @param vector the vector
 * @param index the index
 * @param data the element
 * @return whether it is successful
 *******************************************************/
bool silk_vector_insert(silk_vector_t vector, size_t index, const void* data);

/*******************************************************
 * @brief append an element into a vector
 * @param vector the vector
 * @param data the element
 * @return whether it is successful
 *******************************************************/
bool silk_vector_append(silk_vector_t vector, const void* data);

/*******************************************************
 * @brief remove elements from a vector
 * @param vector the vector
 * @param index the index
 * @param count the count of elements
 * @return whether it is successful
 *******************************************************/
bool silk_vector_removes(silk_vector_t vector, size_t index, size_t count);

/*******************************************************
 * @brief remove an element from a vector
 * @param vector the vector
 * @param index the index
 * @return whether it is successful
 *******************************************************/
bool silk_vector_remove(silk_vector_t vector, size_t index);

/*******************************************************
 * @brief set an element value of a vector
 * @param vector the vector
 * @param index the index
 * @param data the element value
 * @return whether it is successful
 *******************************************************/
bool silk_vector_set(silk_vector_t vector, size_t index, const void* data);

/*******************************************************
 * @brief get an element value of a vector
 * @param vector the vector
 * @param index the index
 * @param data return the element value
 * @return whether it is successful
 *******************************************************/
bool silk_vector_get(silk_vector_t vector, size_t index, void* data);

/*******************************************************
 * @brief push an element to the front of a vector
 * @param vector the vector
 * @param data the element 
 * @return whether it is successful
 *******************************************************/
bool silk_vector_push_front(silk_vector_t vector, const void* data);

/*******************************************************
 * @brief push an element to the back of a vector
 * @param vector the vector
 * @param data the element 
 * @return whether it is successful
 *******************************************************/
bool silk_vector_push_back(silk_vector_t vector, const void* data);

/*******************************************************
 * @brief pop an element from the front of a vector
 * @param vector the vector
 * @param data return the element, nullable
 * @return whether it is successful
 *******************************************************/
bool silk_vector_pop_front(silk_vector_t vector, void* data);

/*******************************************************
 * @brief pop an element from the back of a vector
 * @param vector the vector
 * @param data return the element, nullable
 * @return whether it is successful
 *******************************************************/
bool silk_vector_pop_back(silk_vector_t vector, void* data);

/*******************************************************
 * @brief default compare function with memcpy
 * @note  this function compare byte by byte
 *        so it can be used to determine if value is equal, 
 *        but it cannot compare the values of those type
 *        like little-endian int, float and double
 * @param x a value to compare
 * @param y a value to compare
 * @param userdata the vector
 * @return negative value while x < y
 *         positive value while x > y
 *         0 while x == y
 *******************************************************/
int silk_vector_default_compare(const void* x, const void* y, const void* userdata);

/*******************************************************
 * @brief find an element in vector
 * @param vector the vector
 * @param data the element value
 * @param begin the begin index
 * @param compare function to compare
 * @return index of the element, or SILK_INVALID_INDEX
 *******************************************************/
size_t silk_vector_find(silk_vector_t vector, const void* data, size_t begin, silk_compare_t compare);

/*******************************************************
 * @brief sort a vector by quick sort algorithm 
 *        with stack rather than recursion
 * @param vector the vector
 * @param compare function to compare
 * @return whether it is successful
 *******************************************************/
bool silk_vector_sort(silk_vector_t vector, silk_compare_t compare);

#endif // SILK_VECTOR_H