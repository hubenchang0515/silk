#include <silk/log.h>
#include <silk/hash.h>

#include <string.h>

void test_hash_murmur3_32()
{
    const char* test_str = "helloworld";
    SILK_ASSERT(silk_hash_murmur3_32(test_str, strlen(test_str), 0) == 2687965642);
    SILK_ASSERT(silk_hash_murmur3_32(test_str, strlen(test_str), 1) == 2081296690);
    SILK_ASSERT(silk_hash_murmur3_32(test_str, strlen(test_str), UINT32_MAX) == 1308330980);

    uint8_t data[32] = {
         1,  2,  3,  4,  5,  6,  7,  8, 
         9, 10, 11, 12, 13, 14, 15, 16, 
        17, 18, 19, 20, 21, 22, 23, 24, 
        25, 26, 27, 28, 29, 30, 31, 32
    };

    // remain 0
    SILK_ASSERT(silk_hash_murmur3_32(data, 32, 0) == 3939779180);
    SILK_ASSERT(silk_hash_murmur3_32(data, 32, 1) == 4224611204);
    SILK_ASSERT(silk_hash_murmur3_32(data, 32, UINT32_MAX) == 15435841);

    // remain 3
    SILK_ASSERT(silk_hash_murmur3_32(data, 31, 0) == 2070738917);
    SILK_ASSERT(silk_hash_murmur3_32(data, 31, 1) == 2758145370);
    SILK_ASSERT(silk_hash_murmur3_32(data, 31, UINT32_MAX) == 697923434);

    // remain 2
    SILK_ASSERT(silk_hash_murmur3_32(data, 30, 0) == 18287138);
    SILK_ASSERT(silk_hash_murmur3_32(data, 30, 1) == 3096548982);
    SILK_ASSERT(silk_hash_murmur3_32(data, 30, UINT32_MAX) == 4018556236);

    // remain 1
    SILK_ASSERT(silk_hash_murmur3_32(data, 29, 0) == 781610037);
    SILK_ASSERT(silk_hash_murmur3_32(data, 29, 1) == 3051931994);
    SILK_ASSERT(silk_hash_murmur3_32(data, 29, UINT32_MAX) == 3650431031);
}

void test_hash()
{
    test_hash_murmur3_32();
}