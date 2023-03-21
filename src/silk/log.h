#ifndef SILK_LOG_H
#define SILK_LOG_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>

#define SILK_LOG_CATEGORY_MAX_LENGTH (32 + 1)

void silk_log_set_error_abort(bool abort);
bool silk_log_redirect(const char* file);

bool silk_log_printf(const char* category, const char* fmt, ...);
bool silk_debug_printf(const char* category, const char* fmt, ...);
bool silk_error_printf(const char* category, const char* fmt, ...);

#define SILK_LOG(FMT, ...)      silk_log_printf(NULL, "[SILK LOG]: " FMT, ##__VA_ARGS__)
#define SILK_DEBUG(FMT, ...)    silk_debug_printf(NULL, "[SILK DEBUG - %s:%d]: " FMT, __FILE__, __LINE__, ##__VA_ARGS__)
#define SILK_ERROR(FMT, ...)    silk_error_printf(NULL, "[SILK ERROR - %s:%d]: " FMT, __FILE__, __LINE__, ##__VA_ARGS__)

/*******************************************************
 * @brief assert condition by strict mode 
 *        if condition is false, will abort
 * @param COND the condition
 * @note SILK_ASSERT_LOOSE(COND)  - if (!COND) { abort(); }
 *******************************************************/
#define SILK_ASSERT_STRICT(COND) do { if (!(COND)) { SILK_ERROR("assert '%s' failed.\n", #COND); abort(); } } while(0)

/*******************************************************
 * @brief assert condition by loose mode 
 *        if condition is false, will return
 * @param COND  the condition
 * @param CMD   execute it if condition is false, could empty
 * @param VALUE return it condition is false, could empty
 * @note SILK_ASSERT_LOOSE(COND)             - if (!COND) { return; }
 * @note SILK_ASSERT_LOOSE(COND, VALUE)      - if (!COND) { return VALUE; }
 * @note SILK_ASSERT_LOOSE(COND, CMD, VALUE) - if (!COND) { CMD; return VALUE; }
 *******************************************************/
#define SILK_ASSERT_LOOSE(COND, ...) do { if (!(COND)) { return __VA_ARGS__; } } while(0)

/*******************************************************
 * @brief assert condition by ignore mode 
 *        condition will execute but will not be checked
 * @param COND the condition
 * @note SILK_ASSERT_LOOSE(COND)  - {COND;}
 *******************************************************/
#define SILK_ASSERT_IGNORE(COND) do {COND;} while(0)

// assert mode options, default 0
#define SILK_ASSERT_MODE_STRICT     0
#define SILK_ASSERT_MODE_LOOSE      1
#define SILK_ASSERT_MODE_IGNORE     2

// set assert mode
#if SILK_ASSERT_MODE == SILK_ASSERT_MODE_STRICT
    #define SILK_ASSERT(COND, ...) SILK_ASSERT_STRICT(COND)
#elif SILK_ASSERT_MODE == SILK_ASSERT_MODE_LOOSE
    #define SILK_ASSERT(COND, ...) SILK_ASSERT_LOOSE(COND, ##__VA_ARGS__)
#elif SILK_ASSERT_MODE == SILK_ASSERT_MODE_IGNORE
    #define SILK_ASSERT(COND, ...) SILK_ASSERT_IGNORE(COND, ##__VA_ARGS__)
#else

#endif // SILK_ASSERT_MODE

#endif // SLIK_LOG_H