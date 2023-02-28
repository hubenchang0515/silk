#include "common.h"
#include <stdlib.h>
#include <string.h>

static silk_alloc_t     silk_inner_alloc    = malloc;
static silk_free_t      silk_inner_free     = free;
static silk_realloc_t   silk_inner_realloc  = realloc;
static silk_copy_t      silk_inner_copy     = memmove;

/*******************************************************
 * @brief set the alloc function
 * @param alloc_func the new alloc function
 * @return the old alloc function
 *******************************************************/
silk_alloc_t silk_set_alloc_func(silk_alloc_t alloc_func)
{
    silk_alloc_t old = silk_inner_alloc;
    silk_inner_alloc = alloc_func == NULL ? malloc : alloc_func;
    return old;
}

/*******************************************************
 * @brief set the free function
 * @param alloc_func the new free function
 * @return the old free function
 *******************************************************/
silk_free_t silk_set_free_func(silk_free_t free_func)
{
    silk_free_t old = silk_inner_free;
    silk_inner_free = free_func == NULL ? free : free_func;
    return old;
}

/*******************************************************
 * @brief set the realloc function
 * @param realloc_func the new realloc function
 * @return the old realloc function
 *******************************************************/
silk_realloc_t silk_set_realloc_func(silk_realloc_t realloc_func)
{
    silk_realloc_t old = silk_inner_realloc;
    silk_inner_realloc = realloc_func == NULL ? realloc : realloc_func;
    return old;
}

/*******************************************************
 * @brief set the memory copy function
 * @param realloc_func the new memory copy function
 * @return the old memory copy function
 *******************************************************/
silk_copy_t silk_set_copy_func(silk_copy_t copy_func)
{
    silk_copy_t old = silk_inner_copy;
    silk_inner_copy = copy_func;
    return old;
}

/*******************************************************
 * @brief alloc memory
 * @param bytes the bytes of memory
 * @return the pointer to the memory
 *******************************************************/
void* silk_alloc(size_t bytes)
{
    return silk_inner_alloc(bytes);
}

/*******************************************************
 * @brief free memory
 * @param ptr the pointer to the memory
 *******************************************************/
void  silk_free(void* ptr)
{
    silk_inner_free(ptr);
}

/*******************************************************
 * @brief realloc memory
 * @param ptr the pointer of old memory
 * @param bytes the bytes of new memory
 * @return the pointer to the new memory
 *******************************************************/
void* silk_realloc(void* ptr, size_t bytes)
{
    return silk_inner_realloc(ptr, bytes);
}

/*******************************************************
 * @brief copy memory
 * @param dst the pointer to destination memory
 * @param src the pointer to source memory
 * @param byte the bytes
 * @return dst
 *******************************************************/
void* silk_copy(void* dst, const void* src, size_t bytes)
{
    return silk_inner_copy(dst, src, bytes);
}