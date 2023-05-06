#ifndef SILK_LIST_H
#define SILK_LIST_H

#include "common.h"

/*******************************************************
 * @brief calculate the hash value by MurmurHash
 *        see: https://en.wikipedia.org/wiki/MurmurHash
 * @param element_size the size of an element
 * @return the list
 *******************************************************/
uint32_t silk_hash_murmur3_32(const void* data, size_t len, uint32_t seed);

#endif // SILK_LIST_H