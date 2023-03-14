#ifndef SILK_LOG_H
#define SLIK_LOG_H

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

#define SILK_ASSERT(X) do { if (!(X)) SILK_ERROR("assert '%s' failed.\n", #X); } while(0)

#endif // SLIK_LOG_H