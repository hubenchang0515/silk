#ifndef SILK_ENDIAN_H
#define SILK_ENDIAN_H

#include <stdint.h>

/*******************************************************
 * @brief read little-endian uint16_t value from data
 * @param data the data
 * @return the value
 *******************************************************/
uint16_t silk_endian_read_little16(const void* data);

/*******************************************************
 * @brief read little-endian uint32_t value from data
 * @param data the data
 * @return the value
 *******************************************************/
uint32_t silk_endian_read_little32(const void* data);

/*******************************************************
 * @brief read little-endian uint64_t value from data
 * @param data the data
 * @return the value
 *******************************************************/
uint64_t silk_endian_read_little64(const void* data);

/*******************************************************
 * @brief read big-endian uint16_t value from data
 * @param data the data
 * @return the value
 *******************************************************/
uint16_t silk_endian_read_big16(const void* data);

/*******************************************************
 * @brief read big-endian uint32_t value from data
 * @param data the data
 * @return the value
 *******************************************************/
uint32_t silk_endian_read_big32(const void* data);

/*******************************************************
 * @brief read big-endian uint64_t value from data
 * @param data the data
 * @return the value
 *******************************************************/
uint64_t silk_endian_read_big64(const void* data);

/*******************************************************
 * @brief write little-endian uint16_t value to data
 * @param data the data
 * @param value the value
 *******************************************************/
void silk_endian_write_little16(const void* data, uint16_t value);

/*******************************************************
 * @brief write little-endian uint32_t value to data
 * @param data the data
 * @param value the value
 *******************************************************/
void silk_endian_write_little32(const void* data, uint32_t value);

/*******************************************************
 * @brief write little-endian uint64_t value to data
 * @param data the data
 * @param value the value
 *******************************************************/
void silk_endian_write_little64(const void* data, uint64_t value);

/*******************************************************
 * @brief write big-endian uint16_t value to data
 * @param data the data
 * @param value the value
 *******************************************************/
void silk_endian_write_big16(const void* data, uint16_t value);

/*******************************************************
 * @brief write big-endian uint32_t value to data
 * @param data the data
 * @param value the value
 *******************************************************/
void silk_endian_write_big32(const void* data, uint32_t value);

/*******************************************************
 * @brief write big-endian uint64_t value to data
 * @param data the data
 * @param value the value
 *******************************************************/
void silk_endian_write_big64(const void* data, uint64_t value);

#endif // SILK_ENDIAN_H