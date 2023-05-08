#ifndef SILK_UTILS_H
#define SILK_UTILS_H

/*******************************************************
 * @brief rotate left
 * @param VALUE the src value
 * @param BITS the rotate bits
 * @param LENGTH the bits length of value
 * @return the rotated value
 *******************************************************/
#define SILK_ROL(LENGTH, VALUE, BITS) ((VALUE << BITS) | (VALUE >> (LENGTH - BITS)))

/*******************************************************
 * @brief rotate right
 * @param VALUE the src value
 * @param BITS the rotate bits
 * @param LENGTH the bits length of value
 * @return the rotated value
 *******************************************************/
#define SILK_ROR(LENGTH, VALUE, BITS) ((VALUE >> BITS) | (VALUE << (LENGTH - BITS)))

#endif // SILK_UTILS_H