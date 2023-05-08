#include <silk/endian.h>

#define SILK_ENDIAN_LEFT_SHIFT_READ(TYPE, PTR, INDEX, SHIFT)    (((TYPE)(*(PTR + INDEX))) << SHIFT) 
#define SILK_ENDIAN_RIGHT_SHIFT_WRITE(VALUE, PTR, INDEX, SHIFT) (*(PTR + INDEX) = (uint8_t)((value >> SHIFT) & 0xff))

/*******************************************************
 * @brief read little-endian uint16_t value from data
 * @param data the data
 * @return the value
 *******************************************************/
uint16_t silk_endian_read_little16(const void* data)
{
    const uint8_t* p = (const uint8_t*)(data);
    uint16_t value = SILK_ENDIAN_LEFT_SHIFT_READ(uint16_t, p, 0, 0) | 
                        SILK_ENDIAN_LEFT_SHIFT_READ(uint16_t, p, 1, 8);
    return value;
}

/*******************************************************
 * @brief read little-endian uint32_t value from data
 * @param data the data
 * @return the value
 *******************************************************/
uint32_t silk_endian_read_little32(const void* data)
{
    const uint8_t* p = (const uint8_t*)(data);
    uint32_t value = SILK_ENDIAN_LEFT_SHIFT_READ(uint32_t, p, 0, 0)     | 
                        SILK_ENDIAN_LEFT_SHIFT_READ(uint32_t, p, 1, 8)  |
                        SILK_ENDIAN_LEFT_SHIFT_READ(uint32_t, p, 2, 16) |
                        SILK_ENDIAN_LEFT_SHIFT_READ(uint32_t, p, 3, 24);
    return value;
}

/*******************************************************
 * @brief read little-endian uint64_t value from data
 * @param data the data
 * @return the value
 *******************************************************/
uint64_t silk_endian_read_little64(const void* data)
{
    const uint8_t* p = (const uint8_t*)(data);
    uint64_t value = SILK_ENDIAN_LEFT_SHIFT_READ(uint64_t, p, 0, 0)     | 
                        SILK_ENDIAN_LEFT_SHIFT_READ(uint64_t, p, 1, 8)  |
                        SILK_ENDIAN_LEFT_SHIFT_READ(uint64_t, p, 2, 16) |
                        SILK_ENDIAN_LEFT_SHIFT_READ(uint64_t, p, 3, 24) |
                        SILK_ENDIAN_LEFT_SHIFT_READ(uint64_t, p, 4, 32) |
                        SILK_ENDIAN_LEFT_SHIFT_READ(uint64_t, p, 5, 40) |
                        SILK_ENDIAN_LEFT_SHIFT_READ(uint64_t, p, 6, 48) |
                        SILK_ENDIAN_LEFT_SHIFT_READ(uint64_t, p, 7, 56);
    return value;
}

/*******************************************************
 * @brief read big-endian uint16_t value from data
 * @param data the data
 * @return the value
 *******************************************************/
uint16_t silk_endian_read_big16(const void* data)
{
    const uint8_t* p = (const uint8_t*)(data);
    uint16_t value = SILK_ENDIAN_LEFT_SHIFT_READ(uint16_t, p, 0, 8) | 
                        SILK_ENDIAN_LEFT_SHIFT_READ(uint16_t, p, 1, 0);
    return value;
}

/*******************************************************
 * @brief read big-endian uint32_t value from data
 * @param data the data
 * @return the value
 *******************************************************/
uint32_t silk_endian_read_big32(const void* data)
{
    const uint8_t* p = (const uint8_t*)(data);
    uint32_t value = SILK_ENDIAN_LEFT_SHIFT_READ(uint32_t, p, 0, 24)    | 
                        SILK_ENDIAN_LEFT_SHIFT_READ(uint32_t, p, 1, 16) |
                        SILK_ENDIAN_LEFT_SHIFT_READ(uint32_t, p, 2, 8)  |
                        SILK_ENDIAN_LEFT_SHIFT_READ(uint32_t, p, 3, 0);
    return value;
}

/*******************************************************
 * @brief read big-endian uint64_t value from data
 * @param data the data
 * @return the value
 *******************************************************/
uint64_t silk_endian_read_big64(const void* data)
{
    const uint8_t* p = (const uint8_t*)(data);
    uint64_t value = SILK_ENDIAN_LEFT_SHIFT_READ(uint64_t, p, 0, 56)    | 
                        SILK_ENDIAN_LEFT_SHIFT_READ(uint64_t, p, 1, 48) |
                        SILK_ENDIAN_LEFT_SHIFT_READ(uint64_t, p, 2, 40) |
                        SILK_ENDIAN_LEFT_SHIFT_READ(uint64_t, p, 3, 32) |
                        SILK_ENDIAN_LEFT_SHIFT_READ(uint64_t, p, 4, 24) |
                        SILK_ENDIAN_LEFT_SHIFT_READ(uint64_t, p, 5, 16) |
                        SILK_ENDIAN_LEFT_SHIFT_READ(uint64_t, p, 6, 8)  |
                        SILK_ENDIAN_LEFT_SHIFT_READ(uint64_t, p, 7, 0);
    return value;
}

/*******************************************************
 * @brief write little-endian uint16_t value to data
 * @param data the data
 * @param value the value
 *******************************************************/
void silk_endian_write_little16(const void* data, uint16_t value)
{
    uint8_t* p = (uint8_t*)(data);
    SILK_ENDIAN_RIGHT_SHIFT_WRITE(value, p, 0, 0);
    SILK_ENDIAN_RIGHT_SHIFT_WRITE(value, p, 1, 8);
}

/*******************************************************
 * @brief write little-endian uint32_t value to data
 * @param data the data
 * @param value the value
 *******************************************************/
void silk_endian_write_little32(const void* data, uint32_t value)
{
    uint8_t* p = (uint8_t*)(data);
    SILK_ENDIAN_RIGHT_SHIFT_WRITE(value, p, 0, 0);
    SILK_ENDIAN_RIGHT_SHIFT_WRITE(value, p, 1, 8);
    SILK_ENDIAN_RIGHT_SHIFT_WRITE(value, p, 2, 16);
    SILK_ENDIAN_RIGHT_SHIFT_WRITE(value, p, 3, 24);
}

/*******************************************************
 * @brief write little-endian uint64_t value to data
 * @param data the data
 * @param value the value
 *******************************************************/
void silk_endian_write_little64(const void* data, uint64_t value)
{
    uint8_t* p = (uint8_t*)(data);
    SILK_ENDIAN_RIGHT_SHIFT_WRITE(value, p, 0, 0);
    SILK_ENDIAN_RIGHT_SHIFT_WRITE(value, p, 1, 8);
    SILK_ENDIAN_RIGHT_SHIFT_WRITE(value, p, 2, 16);
    SILK_ENDIAN_RIGHT_SHIFT_WRITE(value, p, 3, 24);
    SILK_ENDIAN_RIGHT_SHIFT_WRITE(value, p, 4, 32);
    SILK_ENDIAN_RIGHT_SHIFT_WRITE(value, p, 5, 40);
    SILK_ENDIAN_RIGHT_SHIFT_WRITE(value, p, 6, 48);
    SILK_ENDIAN_RIGHT_SHIFT_WRITE(value, p, 7, 56);
}

/*******************************************************
 * @brief write big-endian uint16_t value to data
 * @param data the data
 * @param value the value
 *******************************************************/
void silk_endian_write_big16(const void* data, uint16_t value)
{
    uint8_t* p = (uint8_t*)(data);
    SILK_ENDIAN_RIGHT_SHIFT_WRITE(value, p, 0, 8);
    SILK_ENDIAN_RIGHT_SHIFT_WRITE(value, p, 1, 0);
}

/*******************************************************
 * @brief write big-endian uint32_t value to data
 * @param data the data
 * @param value the value
 *******************************************************/
void silk_endian_write_big32(const void* data, uint32_t value)
{
    uint8_t* p = (uint8_t*)(data);
    SILK_ENDIAN_RIGHT_SHIFT_WRITE(value, p, 0, 24);
    SILK_ENDIAN_RIGHT_SHIFT_WRITE(value, p, 1, 16);
    SILK_ENDIAN_RIGHT_SHIFT_WRITE(value, p, 2, 8);
    SILK_ENDIAN_RIGHT_SHIFT_WRITE(value, p, 3, 0);
}

/*******************************************************
 * @brief write big-endian uint64_t value to data
 * @param data the data
 * @param value the value
 *******************************************************/
void silk_endian_write_big64(const void* data, uint64_t value)
{
    uint8_t* p = (uint8_t*)(data);
    SILK_ENDIAN_RIGHT_SHIFT_WRITE(value, p, 0, 56);
    SILK_ENDIAN_RIGHT_SHIFT_WRITE(value, p, 1, 48);
    SILK_ENDIAN_RIGHT_SHIFT_WRITE(value, p, 2, 40);
    SILK_ENDIAN_RIGHT_SHIFT_WRITE(value, p, 3, 32);
    SILK_ENDIAN_RIGHT_SHIFT_WRITE(value, p, 4, 24);
    SILK_ENDIAN_RIGHT_SHIFT_WRITE(value, p, 5, 16);
    SILK_ENDIAN_RIGHT_SHIFT_WRITE(value, p, 6, 8);
    SILK_ENDIAN_RIGHT_SHIFT_WRITE(value, p, 7, 0);
}