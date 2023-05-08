#include <silk/string.h>
#include <silk/log.h>
#include <silk/vector.h>

#include <string.h>

struct SilkString
{
    silk_vector_t data;
};

/*******************************************************
 * @brief create a string
 * @param cstr init value, c-style string
 * @return the string
 *******************************************************/
silk_string_t silk_string_new(const char* cstr)
{
    silk_string_t str = silk_alloc(sizeof(struct SilkString));
    SILK_ASSERT(str != NULL, NULL);

    str->data = silk_vector_new(sizeof(char));
    SILK_ASSERT(str->data, silk_free(str), NULL);
    
    size_t len = cstr == NULL ? 0 : strlen(cstr);
    if (len > 0)
    {
        silk_vector_inserts(str->data, 0, cstr, len+1); // +1 to copy the '\0'
    }
    else
    {
        silk_vector_append(str->data, "\0"); // always keep '\0' as end
    }
    return str;
}

/*******************************************************
 * @brief delete a string
 * @return the string
 *******************************************************/
void silk_string_delete(silk_string_t str)
{
    SILK_ASSERT(str != NULL);
    SILK_ASSERT(str->data != NULL);

    silk_vector_delete(str->data);
    silk_free(str);
}

/*******************************************************
 * @brief clear a string
 * @return the string
 *******************************************************/
void silk_string_clear(silk_string_t str)
{
    SILK_ASSERT(str != NULL);
    SILK_ASSERT(str->data != NULL);

    silk_vector_clear(str->data);
    SILK_ASSERT(silk_vector_append(str->data, "\0")); // always keep '\0' as end
}

/*******************************************************
 * @brief get sub-string
 * @param str the source string
 * @param index the index
 * @param length the length
 * @return the sub-string
 *******************************************************/
silk_string_t silk_string_sub(silk_string_t str, size_t index, size_t length)
{
    SILK_ASSERT(str != NULL, false);
    SILK_ASSERT(index + length <= silk_string_length(str), false);

    silk_string_t sub = silk_string_new(NULL);
    silk_vector_inserts(sub->data, 0, silk_vector_data(str->data) + index, length);
    return sub;
}

/*******************************************************
 * @brief set string value
 * @param str the string to be set
 * @param cstr init value, c-style string
 * @return whether it is successful
 *******************************************************/
bool silk_string_set(silk_string_t str, const char* cstr)
{
    SILK_ASSERT(str != NULL, false);

    silk_string_clear(str);

    size_t len = cstr == NULL ? 0 : strlen(cstr);
    if (len > 0)
    {
        silk_vector_inserts(str->data, 0, cstr, len);
    }
    return true;
}

/*******************************************************
 * @brief get string value as c-style string
 * @param str the string to be get
 * @return c-style string value
 *******************************************************/
const char* silk_string_get(silk_string_t str)
{
    SILK_ASSERT(str != NULL, NULL);
    
    return silk_vector_const_data(str->data);
}

/*******************************************************
 * @brief copy a string
 * @param str the string to be copied
 * @return the copied string 
 *******************************************************/
silk_string_t silk_string_copy(silk_string_t str)
{
    SILK_ASSERT(str != NULL, NULL);

    return silk_string_new(silk_string_get(str));
}

/*******************************************************
 * @brief get length of a string
 * @param str the string
 * @return the length
 *******************************************************/
size_t silk_string_length(silk_string_t str)
{
    SILK_ASSERT(str != NULL, 0);

    size_t length = silk_vector_length(str->data);
    return length > 0 ? length - 1 : 0;
}

/*******************************************************
 * @brief get string value as c-style string
 * @param str the string to be get
 * @return c-style string value
 *******************************************************/
char* silk_string_data(silk_string_t str)
{
    SILK_ASSERT(str != NULL, NULL);
    
    return silk_vector_data(str->data);
}

/*******************************************************
 * @brief determine whether two string are equal
 * @param str1 the string to be determine
 * @param str2 the string to be determine
 * @return whether two string are equal
 *******************************************************/
bool silk_string_equal(silk_string_t str1, silk_string_t str2)
{
    SILK_ASSERT(str1 != NULL, false);
    SILK_ASSERT(str2 != NULL, false);

    return (strcmp(silk_string_get(str1), silk_string_get(str2)) == 0);
}

/*******************************************************
 * @brief get char at index of string
 * @param str the string
 * @param index the index
 * @return char at index of string
 *******************************************************/
char silk_string_at(silk_string_t str, size_t index)
{
    SILK_ASSERT(str != NULL, 0);
    SILK_ASSERT(index < silk_string_length(str), 0);

    return silk_string_get(str)[index];
}

/*******************************************************
 * @brief insert character into string
 * @param str the string
 * @param index the index
 * @param ch the character
 * @return whether it is successful
 *******************************************************/
bool silk_string_insert(silk_string_t str, size_t index, char ch)
{
    SILK_ASSERT(str != NULL, false);
    SILK_ASSERT(index <= silk_string_length(str), false);
    
    return silk_vector_insert(str->data, index, &ch);
}

/*******************************************************
 * @brief insert c-style string into string
 * @param str the string
 * @param index the index
 * @param cstr the c-style string
 * @return whether it is successful
 *******************************************************/
bool silk_string_inserts(silk_string_t str, size_t index, const char* cstr)
{
    SILK_ASSERT(str != NULL, false);
    SILK_ASSERT(index <= silk_string_length(str), false);
    
    size_t len = cstr == NULL ? 0 : strlen(cstr);
    if (len > 0)
    {
        SILK_ASSERT(silk_vector_inserts(str->data, index, cstr, len));
    }
    return true;
}

/*******************************************************
 * @brief append character into string
 * @param str the string
 * @param index the index
 * @param ch the character
 * @return whether it is successful
 *******************************************************/
bool silk_string_append(silk_string_t str, char ch)
{
    SILK_ASSERT(str != NULL, false);

    return silk_string_insert(str, silk_string_length(str), ch);
}

/*******************************************************
 * @brief append c-style string into string
 * @param str the string
 * @param index the index
 * @param cstr the c-style string
 * @return whether it is successful
 *******************************************************/
bool silk_string_appends(silk_string_t str, const char* cstr)
{
    SILK_ASSERT(str != NULL, false);

    return silk_string_inserts(str, silk_string_length(str), cstr);
}

/*******************************************************
 * @brief remove a character from a string
 * @param str the string
 * @param index the index
 * @return whether it is successful
 *******************************************************/
bool silk_string_remove(silk_string_t str, size_t index)
{
    SILK_ASSERT(str != NULL, false);
    SILK_ASSERT(index < silk_string_length(str), false);

    return silk_vector_removes(str->data, index, 1); 
}

/*******************************************************
 * @brief remove some characters from a string
 * @param str the string
 * @param index the index
 * @param length to be replaced
 * @return whether it is successful
 *******************************************************/
bool silk_string_removes(silk_string_t str, size_t index, size_t length)
{
    SILK_ASSERT(str != NULL, false);
    SILK_ASSERT(index + length < silk_string_length(str), false);

    return silk_vector_removes(str->data, index, length);
}