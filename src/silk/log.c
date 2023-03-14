#include "log.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>

static bool silk_inner_error_abort = true;
static FILE* silk_inner_log_file_fp = NULL;

void silk_log_set_error_abort(bool abort)
{
    silk_inner_error_abort = abort;
}

bool silk_log_redirect(const char* file)
{
    if (file == NULL)
    {
        if (silk_inner_log_file_fp != NULL)
        {
            fclose(silk_inner_log_file_fp);
            silk_inner_log_file_fp = NULL;
        }
        return true;
    }
    else
    {
        FILE* fp = fopen(file, "ab");
        if (fp == NULL)
        {
            SILK_LOG("cannot redirect to '%s': %s\n", file, strerror(errno));
            return false;
        }
        else
        {
            if (silk_inner_log_file_fp != NULL)
                fclose(silk_inner_log_file_fp);

            silk_inner_log_file_fp = fp;
            return true;
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

    strcpy(flag, category);
    strcat(flag, suffix);

    const char* env = getenv(flag);
    if (env == NULL)
        return false;

    return strcmp(env, "1") == 0;
}

bool silk_log_printf(const char* category, const char* fmt, ...)
{
    if (!silk_inner_check_category(category, "_LOG"))
        return false;

    if (category != NULL)
        fprintf(silk_inner_log_file_fp == NULL ? stdout : silk_inner_log_file_fp, "[%s_LOG]: ", category);

    va_list args;
    va_start(args, fmt);
    vfprintf(silk_inner_log_file_fp == NULL ? stdout : silk_inner_log_file_fp, fmt, args);
    va_end(args);
    return true;
}

bool silk_debug_printf(const char* category, const char* fmt, ...)
{
    if (!silk_inner_check_category(category, "_DEBUG"))
        return false;

    if (category != NULL)
        fprintf(silk_inner_log_file_fp == NULL ? stdout : silk_inner_log_file_fp, "[%s_DEBUG]: ", category);
    
    va_list args;
    va_start(args, fmt);
    vfprintf(silk_inner_log_file_fp == NULL ? stdout : silk_inner_log_file_fp, fmt, args);
    va_end(args);
    return true;
}

bool silk_error_printf(const char* category, const char* fmt, ...)
{
    if (!silk_inner_check_category(category, "_ERROR"))
        return false;

    if (category != NULL)
        fprintf(silk_inner_log_file_fp == NULL ? stdout : silk_inner_log_file_fp, "[%s_ERROR]: ", category);

    va_list args;
    va_start(args, fmt);
    vfprintf(silk_inner_log_file_fp == NULL ? stdout : silk_inner_log_file_fp, fmt, args);
    va_end(args);

    if (silk_inner_error_abort)
    {
        fflush(silk_inner_log_file_fp == NULL ? stdout : silk_inner_log_file_fp);
        abort();
    }
    return true;
}