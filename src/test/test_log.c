#include <stdlib.h>
#include <silk/log.h>

void test_log()
{
    silk_log_set_error_abort(false);
    SILK_ASSERT(silk_log_redirect("") == false);

    SILK_ASSERT(silk_log_redirect("test_log.txt") == true);
    SILK_ASSERT(SILK_LOG("hello world\n") == true);
    SILK_ASSERT(SILK_DEBUG("hello world\n") == true);
    SILK_ASSERT(SILK_ERROR("hello world\n") == true);

    SILK_ASSERT(silk_log_redirect("test_log2.txt") == true);
    SILK_ASSERT(SILK_LOG("hello world\n") == true);
    SILK_ASSERT(SILK_DEBUG("hello world\n") == true);
    SILK_ASSERT(SILK_ERROR("hello world\n") == true);

    SILK_ASSERT(silk_log_redirect(NULL) == true);

    setenv("TEST_LOG", "0", 1);
    SILK_ASSERT(silk_log_printf("TEST", "hello world\n") == false);
    setenv("TEST_LOG", "1", 1);
    SILK_ASSERT(silk_log_printf("TEST", "hello world\n") == true);

    setenv("TEST_DEBUG", "0", 1);
    SILK_ASSERT(silk_debug_printf("TEST", "hello world\n") == false);
    setenv("TEST_DEBUG", "1", 1);
    SILK_ASSERT(silk_debug_printf("TEST", "hello world\n") == true);

    setenv("TEST_ERROR", "0", 1);
    SILK_ASSERT(silk_error_printf("TEST", "hello world\n") == false);
    setenv("TEST_ERROR", "1", 1);
    SILK_ASSERT(silk_error_printf("TEST", "hello world\n") == true);
}