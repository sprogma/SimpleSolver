#include "common.h"
#include "color.h"
#include "read_double.h"


#include "stdio.h"
#include "stdarg.h"




int read_double(double *result, const char *fmt, ...)
{
    int ch, scan_result;
    *result = 0.0;
    while (1)
    {
        if (is_in_terminal())
        {        
            va_list args;
            va_start(args, fmt);
            vfprintf(stderr, fmt, args);
            va_end(args);
        }
        scan_result = scanf("%lg", result);
        if (scan_result == 1)
        {
            break;
        }
        if (scan_result == EOF)
        {
            return READ_COEFFICIENTS_EOF;
        }
        do { ch = getchar(); } 
        while (ch != EOF && ch != '\n');
        if (ch == EOF)
        {
            return READ_COEFFICIENTS_EOF;
        }
    }
    return 0;
}
