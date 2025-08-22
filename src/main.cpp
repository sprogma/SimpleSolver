#include "common.h"
#include "solver.h"
#include "interactive.h"
#include "solve_commandline_args.h"

#include "string.h"
#include "errno.h"
#include "stdlib.h"
#include "stdio.h"
#include "ctype.h"
#include "inttypes.h"


int parse_arguments(int argc, char **argv);


int main(int argc, char **argv)
{
    return parse_arguments(argc, argv);
}



int parse_arguments(int argc, char **argv)
{
    uint32_t coefficients_set = 0;
    struct coefficients_t coeffs = {};
    
    for (int curr = 1; curr < argc; ++curr)
    {
        if (!strcmp(argv[curr], "--"))
        {
            break;
        }
        else if (!strcmp(argv[curr], "--help") || !strcmp(argv[curr], "-h"))
        {
            char buff[16] = {};
            FILE *file = fopen("help.txt", "r");
            while (!feof(file))
            {
                size_t count = fread(buff, 1, sizeof(buff), file);
                fwrite(buff, 1, count, stdout);
            }
            return 0;
        }
        else if (!strcmp(argv[curr], "--coeff") || !strcmp(argv[curr], "-c"))
        {
            if (coefficients_set)
            {
                fprintf(stderr, "Given two \"coeff\" arguments at the same time.");
            }
            curr++;
            double value = 0.0;
            size_t id = 0;
            while (curr < argc)
            {
                char *end_ptr;
                value = strtod(argv[curr], &end_ptr);
                
                while (isspace(*end_ptr)) { end_ptr++; }

                if (errno == ERANGE)
                {        
                    fprintf(stderr, "Overflow/Underflow in command line arguments.\n");
                    return 1;
                }

                if (*end_ptr != 0)
                {
                    break;
                }             

                switch (id)
                {
                    case 0:
                       coeffs.c = value;
                       break;
                    case 1:
                       coeffs.b = coeffs.c;
                       coeffs.c = value;
                       break;
                    case 2:
                       coeffs.a = coeffs.b;
                       coeffs.b = coeffs.c;
                       coeffs.c = value;
                       break;
                    default:
                        fprintf(stderr, "Warning: too many coefficients given. skip them.\n");
                        break;
                }
                
                id++;
                curr++;
            }
            coefficients_set = -1;
            /* set pointer on last read argument */
            --curr;
        }
        else
        {
            fprintf(stderr, "Unknown command line flag: %s\n", argv[curr]);
        }
    }

    /* call solvers */

    if (coefficients_set)
    {
        return solve_command_line_coefficients(&coeffs);
    }
    else
    {
        return run_interactive();
    }
}
