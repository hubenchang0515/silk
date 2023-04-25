#include <silk/log.h>
#include <silk/string.h>

#include <string.h>

void test_string_new()
{
    silk_string_t str = silk_string_new(NULL);
    SILK_ASSERT(silk_string_length(str) == 0);
    // SILK_ASSERT(silk_string_get(str) == NULL);
    // SILK_ASSERT(silk_string_data(str) == NULL);
    silk_string_delete(str);

    str = silk_string_new("");
    SILK_ASSERT(silk_string_length(str) == 0);
    // SILK_ASSERT(silk_string_get(str) == NULL);
    // SILK_ASSERT(silk_string_data(str) == NULL);
    silk_string_delete(str);
    
    const char* cstr = "hello world";
    str = silk_string_new(cstr);
    SILK_ASSERT(strcmp(silk_string_get(str), cstr) == 0);
    SILK_ASSERT(strcmp(silk_string_data(str), cstr) == 0);
    SILK_ASSERT(silk_string_length(str) == strlen(cstr));
    for (size_t i = 0; i < strlen(cstr); i++)
    {
        SILK_ASSERT(silk_string_at(str, i) == cstr[i]);
    }
    silk_string_delete(str);
}

void test_string_sub()
{
    silk_string_t str = silk_string_new("hello silk world");
    silk_string_t sub1 = silk_string_sub(str, 0, 5);
    silk_string_t sub2 = silk_string_sub(str, 6, 4);
    silk_string_t sub3 = silk_string_sub(str, 11, 5);

    SILK_ASSERT(strcmp(silk_string_get(sub1), "hello") == 0);
    SILK_ASSERT(strcmp(silk_string_get(sub2), "silk") == 0);
    SILK_ASSERT(strcmp(silk_string_get(sub3), "world") == 0);

    silk_string_delete(str);
    silk_string_delete(sub1);
    silk_string_delete(sub2);
    silk_string_delete(sub3);
}


void test_string_copy()
{
    const char* cstr = "hello world";
    silk_string_t str = silk_string_new(cstr);
    silk_string_t copied = silk_string_copy(str);
    SILK_ASSERT(silk_string_equal(str, copied));
    silk_string_delete(copied);
    silk_string_delete(str);
}

void test_string_clear()
{
    const char* cstr = "hello world";
    silk_string_t str = silk_string_new(cstr);
    silk_string_clear(str);
    SILK_ASSERT(silk_string_length(str) == 0);
    // SILK_ASSERT(silk_string_get(str) == NULL);
    // SILK_ASSERT(silk_string_data(str) == NULL);
    silk_string_delete(str);
}

void test_string_set()
{
    const char* cstr = "hello world";
    silk_string_t str = silk_string_new(cstr);
    SILK_ASSERT(strcmp(silk_string_get(str), cstr) == 0);
    SILK_ASSERT(strcmp(silk_string_data(str), cstr) == 0);
    SILK_ASSERT(silk_string_length(str) == strlen(cstr));

    silk_string_set(str, "");
    SILK_ASSERT(silk_string_length(str) == 0);
    // SILK_ASSERT(silk_string_get(str) == NULL);
    // SILK_ASSERT(silk_string_data(str) == NULL);

    silk_string_set(str, cstr);
    SILK_ASSERT(strcmp(silk_string_get(str), cstr) == 0);
    SILK_ASSERT(strcmp(silk_string_data(str), cstr) == 0);
    SILK_ASSERT(silk_string_length(str) == strlen(cstr));
    
    silk_string_delete(str);
}

void test_string_insert()
{
    silk_string_t str = silk_string_new("hello world");
    SILK_ASSERT(silk_string_insert(str, 6, ' '));
    SILK_ASSERT(silk_string_insert(str, 6, 'k'));
    SILK_ASSERT(silk_string_insert(str, 6, 'l'));
    SILK_ASSERT(silk_string_insert(str, 6, 'i'));
    SILK_ASSERT(silk_string_insert(str, 6, 's'));
    SILK_ASSERT(strcmp(silk_string_get(str), "hello silk world") == 0);
    silk_string_delete(str);
}

void test_string_inserts()
{
    silk_string_t str = silk_string_new(NULL);
    SILK_ASSERT(silk_string_inserts(str, 0, "hello world"));
    SILK_ASSERT(silk_string_inserts(str, 6, "silk "));
    SILK_ASSERT(strcmp(silk_string_get(str), "hello silk world") == 0);
    silk_string_delete(str);
}

void test_string_append()
{
    const char* cstr = "hello world";
    silk_string_t str = silk_string_new(NULL);
    
    for (size_t i = 0; i < strlen(cstr); i++)
        SILK_ASSERT(silk_string_append(str, cstr[i]));
    SILK_ASSERT(strcmp(silk_string_get(str), "hello world") == 0);
    silk_string_delete(str);
}

void test_string_appends()
{
    silk_string_t str = silk_string_new(NULL);
    SILK_ASSERT(silk_string_appends(str, "hello"));
    SILK_ASSERT(silk_string_appends(str, " silk"));
    SILK_ASSERT(strcmp(silk_string_get(str), "hello silk") == 0);
    silk_string_delete(str);
}

void test_string_remove()
{
    silk_string_t str = silk_string_new("hello world");
    for (size_t i = 0; i < 6; i++)
    {
        SILK_ASSERT(silk_string_remove(str, 5));
    }
    SILK_ASSERT(strcmp(silk_string_get(str), "hello") == 0);
    silk_string_delete(str);
}

void test_string_removes()
{
    silk_string_t str = silk_string_new("test_string_removes");
    SILK_ASSERT(silk_string_removes(str, 5, 7));
    SILK_ASSERT(strcmp(silk_string_get(str), "test_removes") == 0);
    silk_string_delete(str);
}

void test_string()
{
    test_string_new();
    test_string_sub();
    test_string_copy();
    test_string_clear();
    test_string_set();
    test_string_insert();
    test_string_inserts();
    test_string_append();
    test_string_appends();
    test_string_remove();
    test_string_removes();
}