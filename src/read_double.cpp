#include "common.h"
#include "color.h"
#include "is_a_tty.h"
#include "read_double.h"


#include "errno.h"
#include "ctype.h"
#include "stdio.h"
#include "stdlib.h"
#include "stdarg.h"





int read_double(double *result, const char *fmt, ...)
{
    assert(result != NULL);
    
    *result = 0.0;
    while (1)
    {
        if (is_input_terminal())
        {        
            va_list args = NULL;
            va_start(args, fmt);
            vfprintf(stderr, fmt, args);
            va_end(args);
        }
        
        char buffer[128] = {}, *end = NULL;
        if (fgets(buffer, sizeof(buffer), stdin) == NULL)
        {
            if (feof(stdin))
            {
                return READ_COEFFICIENTS_EOF;
            }
            return READ_COEFFICIENTS_FGETS_ERROR;
        }

        *result = strtod(buffer, &end);
        if (buffer == end)
        {
            fprintf(stderr, "Error.\n");
            continue;
        }
        if (errno == ERANGE)
        {        
            fprintf(stderr, "Overflow/Underflow.\n");
            errno = 0;
            continue;
        }
        while (isspace(*end)) { end++; }
        if (*end == 0)
        {
            if (*(end - 1) == '\n')
            {   
                break;
            }
            fprintf(stderr, "Too long string. Length must be less than %ld.\n", (long)(sizeof(buffer) - 2));
            /* skip all text up to \n */
            while (getchar() != '\n') { }
            continue;
        }
        fprintf(stderr, "Trash in the end of line.\n");
    }
    return 0;
}
