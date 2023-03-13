#ifndef SILK_MEMORY_H
#define SILK_MEMORY_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

typedef void* (*silk_alloc_t)(size_t bytes);
typedef void (*silk_free_t)(void* ptr);
typedef void* (*silk_realloc_t)(void* ptr, size_t byets);
typedef void* (*silk_copy_t)(void* dst, const void* src, size_t byets);

/*******************************************************
 * @brief set the alloc function
 * @param alloc_func the new alloc function
 * @return the old alloc function
 *******************************************************/
silk_alloc_t silk_set_alloc_func(silk_alloc_t alloc_func);

/*******************************************************
 * @brief set the free function
 * @param free_func the new free function
 * @return the old free function
 *******************************************************/
silk_free_t silk_set_free_func(silk_free_t free_func);

/*******************************************************
 * @brief set the realloc function
 * @param realloc_func the new realloc function
 * @return the old realloc function
 *******************************************************/
silk_realloc_t silk_set_realloc_func(silk_realloc_t realloc_func);

/*******************************************************
 * @brief set the memory copy function
 * @param realloc_func the new memory copy function
 * @return the old memory copy function
 *******************************************************/
silk_copy_t silk_set_copy_func(silk_copy_t copy_func);

/*******************************************************
 * @brief alloc memory
 * @param bytes the bytes of memory
 * @return the pointer to the memory
 *******************************************************/
void* silk_alloc(size_t bytes);

/*******************************************************
 * @brief free memory
 * @param ptr the pointer to the memory
 *******************************************************/
void  silk_free(void* ptr);

/*******************************************************
 * @brief realloc memory
 * @param ptr the pointer of old memory
 * @param bytes the bytes of new memory
 * @return the pointer to the new memory
 *******************************************************/
void* silk_realloc(void* ptr, size_t bytes);

/*******************************************************
 * @brief copy memory
 * @param dst the pointer to destination memory
 * @param src the pointer to source memory
 * @param byte the bytes
 * @return dst
 *******************************************************/
void* silk_copy(void* dst, const void* src, size_t bytes);

#endif // SILK_MEMORY_H