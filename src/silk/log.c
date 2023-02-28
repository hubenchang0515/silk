#include "log.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>



static FILE* silk_inner_log_file_fp = NULL;

void silk_log_redirect(const char* file)
{
    if (file == NULL)
    {
        fclose(silk_inner_log_file_fp);
        silk_inner_log_file_fp = NULL;
        return;
    }
    else
    {
        FILE* fp = fopen(file, "ab");
        if (fp == NULL)
        {
            SILK_ERROR("cannot redirect to %s: %s\n", file, strerror(errno));
            return;
        }
        else
        {
            if (silk_inner_log_file_fp != NULL)
                fclose(silk_inner_log_file_fp);

            silk_inner_log_file_fp = fp;
        }
    }
}

static bool silk_inner_check_category(const char* category, const char* suffix)
{
    char flag[SILK_LOG_CATEGORY_MAX_LENGTH + 8];
    
    if (category == NULL)
        return true;

    if (strlen(category) >= SILK_LOG_CATEGORY_MAX_LENGTH)
        return false;

    strcat(flag, suffix);

    const char* env = getenv(flag);
    if (env == NULL)
        return false;

    return strcmp(env, "1") == 0;
}

void silk_log_printf(const char* category, const char* fmt, ...)
{
    if (!silk_inner_check_category(category, "_LOG"))
        return;

    va_list args;
    va_start(args, fmt);
    vfprintf(silk_inner_log_file_fp == NULL ? stdout : silk_inner_log_file_fp, fmt, args);
    va_end(args);
}

void silk_debug_printf(const char* category, const char* fmt, ...)
{
    if (!silk_inner_check_category(category, "_DEBUG"))
        return;

    va_list args;
    va_start(args, fmt);
    vfprintf(silk_inner_log_file_fp == NULL ? stdout : silk_inner_log_file_fp, fmt, args);
    va_end(args);
}

void silk_error_printf(const char* category, const char* fmt, ...)
{
    if (!silk_inner_check_category(category, "_ERROR"))
        return;

    va_list args;
    va_start(args, fmt);
    vfprintf(silk_inner_log_file_fp == NULL ? stdout : silk_inner_log_file_fp, fmt, args);
    va_end(args);
    abort();
}