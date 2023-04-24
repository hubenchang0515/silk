#ifndef SILK_STRING_H
#define SILK_STRING_H

#include "common.h"
#include "compare.h"
#include "memory.h"

typedef struct SilkString* silk_string_t;

/*******************************************************
 * @brief create a string
 * @param cstr init value, c-style string
 * @return the string
 *******************************************************/
silk_string_t silk_string_new(const char* cstr);

/*******************************************************
 * @brief delete a string
 * @return the string
 *******************************************************/
void silk_string_delete(silk_string_t str);

/*******************************************************
 * @brief clear a string
 * @return the string
 *******************************************************/
void silk_string_clear(silk_string_t str);

/*******************************************************
 * @brief get sub-string
 * @param str the source string
 * @param index the index
 * @param length the length
 * @return the sub-string
 *******************************************************/
silk_string_t silk_string_sub(silk_string_t cstr, size_t index, size_t length);

/*******************************************************
 * @brief set string value
 * @param str the string to be set
 * @param cstr init value, c-style string
 * @return whether it is successful
 *******************************************************/
bool silk_string_set(silk_string_t str, const char* cstr);

/*******************************************************
 * @brief get string value as c-style string
 * @param str the string to be get
 * @return c-style string value
 *******************************************************/
const char* silk_string_get(silk_string_t str);

/*******************************************************
 * @brief copy a string
 * @param str the string to be copied
 * @return the copied string 
 *******************************************************/
silk_string_t silk_string_copy(silk_string_t str);

/*******************************************************
 * @brief get length of a string
 * @param str the string
 * @return the length
 *******************************************************/
size_t silk_string_length(silk_string_t str);

/*******************************************************
 * @brief get string value as c-style string
 * @param str the string to be get
 * @return c-style string value
 *******************************************************/
char* silk_string_data(silk_string_t str);

/*******************************************************
 * @brief determine whether two string are equal
 * @param str1 the string to be determine
 * @param str2 the string to be determine
 * @return whether two string are equal
 *******************************************************/
bool silk_string_equal(silk_string_t str1, silk_string_t str2);

/*******************************************************
 * @brief get char at index of string
 * @param str the string
 * @param index the index
 * @return char at index of string
 *******************************************************/
char silk_string_at(silk_string_t str, size_t index);

/*******************************************************
 * @brief insert character into string
 * @param str the string
 * @param index the index
 * @param ch the character
 * @return whether it is successful
 *******************************************************/
bool silk_string_insert(silk_string_t str, size_t index, char ch);


/*******************************************************
 * @brief insert c-style string into string
 * @param str the string
 * @param index the index
 * @param cstr the c-style string
 * @return whether it is successful
 *******************************************************/
bool silk_string_inserts(silk_string_t str, size_t index, const char* cstr);

/*******************************************************
 * @brief append character into string
 * @param str the string
 * @param index the index
 * @param ch the character
 * @return whether it is successful
 *******************************************************/
bool silk_string_append(silk_string_t str, char ch);

/*******************************************************
 * @brief append c-style string into string
 * @param str the string
 * @param index the index
 * @param cstr the c-style string
 * @return whether it is successful
 *******************************************************/
bool silk_string_appends(silk_string_t str, const char* cstr);

/*******************************************************
 * @brief remove a character from a string
 * @param str the string
 * @param index the index
 * @return whether it is successful
 *******************************************************/
bool silk_string_remove(silk_string_t str, size_t index);

/*******************************************************
 * @brief remove some characters from a string
 * @param str the string
 * @param index the index
 * @param length to be replaced
 * @return whether it is successful
 *******************************************************/
bool silk_string_removes(silk_string_t str, size_t index, size_t length);

#endif // SILK_STRING_H