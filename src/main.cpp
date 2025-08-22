#include "common.h"
#include "solver.h"
#include "interactive.h"
#include "help.h"
#include "solve_commandline_args.h"
#include "parse_commandline_coefficients.h"

#include "string.h"
#include "errno.h"
#include "stdlib.h"
#include "stdio.h"
#include "ctype.h"
#include "inttypes.h"


int parse_arguments(int argc, const char **argv);


int main(int argc, const char **argv)
{
    return parse_arguments(argc, argv);
}



int parse_arguments(int argc, const char **argv)
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
            return print_help();
        }
        else if (!strcmp(argv[curr], "--coeff") || !strcmp(argv[curr], "-c"))
        {
            if (coefficients_set)
            {
                fprintf(stderr, "Given two \"coeff\" arguments at the same time.\n");
            }
            
            int res = parse_commandline_coefficients(argc, argv, &curr, &coeffs);

            if (res != 0)
            {
                fprintf(stderr, "Error while parse commandline coefficients.\n");
                return res;
            }

            coefficients_set = -1;
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
