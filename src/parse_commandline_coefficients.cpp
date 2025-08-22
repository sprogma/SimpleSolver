#include "common.h"
#include "solver.h"
#include "parse_commandline_coefficients.h"

#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "ctype.h"
#include "errno.h"



int parse_commandline_coefficients(int argc, const char **argv, struct coefficients_t *coeffs)
{
    int curr = 0;
    double value = 0.0;
    size_t id = 0;
    while (curr < argc)
    {
        char *end_ptr = NULL;
        value = strtod(argv[curr], &end_ptr);
        
        while (isspace(*end_ptr)) { end_ptr++; }

        if (errno == ERANGE)
        {        
            fprintf(stderr, "Overflow/Underflow in command line arguments.\n");
            errno = 0;
            return 1;
        }

        if (*end_ptr != 0)
        {
            break;
        }             

        switch (id)
        {
            case 0:
               coeffs->c = value;
               break;
            case 1:
               coeffs->b = coeffs->c;
               coeffs->c = value;
               break;
            case 2:
               coeffs->a = coeffs->b;
               coeffs->b = coeffs->c;
               coeffs->c = value;
               break;
            default:
                fprintf(stderr, "Warning: too many coefficients given. skip them.\n");
                break;
        }
        
        id++;
        curr++;
    }
    
    return 0;
}
