#include "hash.h"
#include "log.h"

/*******************************************************
 * @brief calculate the hash value by MurmurHash
 *        see: https://en.wikipedia.org/wiki/MurmurHash
 * @param data the data
 * @param len length of the data
 * @param seed seed of hash
 * @return the hash value
 *******************************************************/
uint32_t silk_hash_murmur3_32(const void* data, size_t len, uint32_t seed)
{
    SILK_ASSERT(data != NULL, seed);

    uint32_t c1 = 0xcc9e2d51;
    uint32_t c2 = 0x1b873593;
    uint32_t r1 = 15;
    uint32_t r2 = 13;
    uint32_t m = 5;
    uint32_t n = 0xe6546b64;
    uint32_t hash = seed;

    const uint32_t* chunks = (const uint32_t*)(data);
    size_t i = 0;
    for (; (i + 1) * sizeof(uint32_t) - 1 < len; i++)
    {
        uint32_t k = chunks[i];
        k = k * c1;
        k = SILK_ROL(32, k, r1);
        k = k * c2;

        hash = hash ^ k;
        hash = SILK_ROL(32, hash, r2);
        hash = (hash * m) + n;
    }

    const uint8_t* remaining = (const uint8_t*)(data) + (i * sizeof(uint32_t));
    uint32_t remainingBytes = 0;
    size_t remainingSize = len - i * sizeof(uint32_t);

    if (remainingSize >= 3)
        remainingBytes |= (remaining[2] << 16);

    if (remainingSize >= 2)
        remainingBytes |= (remaining[1] << 8);

    if (remainingSize >= 1)
    {
        remainingBytes |= remaining[0];

        remainingBytes = remainingBytes * c1;
        remainingBytes = SILK_ROL(32, remainingBytes, r1);
        remainingBytes = remainingBytes * c2;
        hash = hash ^ remainingBytes;
    }

    hash = hash ^ len;
    hash = hash ^ (hash >> 16);
    hash = hash * 0x85ebca6b;
    hash = hash ^ (hash >> 13);
    hash = hash * 0xc2b2ae35;
    hash = hash ^ (hash >> 16);

    return hash;
}