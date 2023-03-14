#include <stdlib.h>
#include <silk/log.h>

void test_log()
{
    SILK_ASSERT(silk_log_redirect("") == false);
    SILK_ASSERT(silk_log_redirect("test_log.txt") == true);
    SILK_ASSERT(silk_log_redirect("test_log2.txt") == true);

    SILK_ASSERT(SILK_LOG("hello world\n") == true);
    SILK_ASSERT(SILK_DEBUG("hello world\n") == true);

    silk_log_set_error_abort(false);
    SILK_ASSERT(SILK_ERROR("hello world\n") == true);
    silk_log_set_error_abort(true);

    SILK_ASSERT(silk_log_redirect("test_log2.txt") == true);
    SILK_ASSERT(SILK_LOG("hello world\n") == true);
    SILK_ASSERT(SILK_DEBUG("hello world\n") == true);

    silk_log_set_error_abort(false);
    SILK_ASSERT(SILK_ERROR("hello world\n") == true);
    silk_log_set_error_abort(true);

    SILK_ASSERT(silk_log_redirect(NULL) == true);

    // category out of range
    SILK_ASSERT(silk_log_printf("SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS", "hello world\n") == false);
    SILK_ASSERT(silk_debug_printf("SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS", "hello world\n") == false);
    SILK_ASSERT(silk_error_printf("SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS", "hello world\n") == false);


#if _POSIX_C_SOURCE >= 200112L || _BSD_SOURCE
    setenv("TEST_LOG", "0", 1);
    SILK_ASSERT(silk_log_printf("TEST", "hello world\n") == false);
    setenv("TEST_LOG", "1", 1);
    SILK_ASSERT(silk_log_printf("TEST", "hello world\n") == true);
    unsetenv("TEST_LOG");
    SILK_ASSERT(silk_log_printf("TEST", "hello world\n") == false);

    setenv("TEST_DEBUG", "0", 1);
    SILK_ASSERT(silk_debug_printf("TEST", "hello world\n") == false);
    setenv("TEST_DEBUG", "1", 1);
    SILK_ASSERT(silk_debug_printf("TEST", "hello world\n") == true);
    unsetenv("TEST_DEBUG");
    SILK_ASSERT(silk_debug_printf("TEST", "hello world\n") == false);

    silk_log_set_error_abort(false);
    setenv("TEST_ERROR", "0", 1);
    SILK_ASSERT(silk_error_printf("TEST", "hello world\n") == false);
    setenv("TEST_ERROR", "1", 1);
    SILK_ASSERT(silk_error_printf("TEST", "hello world\n") == true);
    unsetenv("TEST_ERROR");
    SILK_ASSERT(silk_error_printf("TEST", "hello world\n") == false);
    silk_log_set_error_abort(true);
#endif
}