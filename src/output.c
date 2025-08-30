#include "common.h"
#include "solver.h"
#include "output.h"

#include "stdio.h"

#include "is_a_tty.h"
#include "color.h"


int print_result_color(const double *roots, long long result_code);
int print_result_text(const double *roots, long long result_code);

int print_result_color(const double *roots, long long result_code)
{
    assert(roots != NULL);
    
    switch (result_code)
    {
        case RESULT_INFINITE_SOLUTIONS:
            printf(COLOR_YELLOW("Any number is solution")"\n");
            break;
        case RESULT_ERROR_EQUATION:
            printf(COLOR_RED("There is error in equation, probably nan.")"\n");
            break;
        case 0:
            printf(COLOR_RED("There is no solutions.") "\n" );
            break;
        default:
            printf(COLOR_GREEN("Found %ld roots:")"\n", (long int)result_code);
            for (long long i = 0; i < result_code; ++i)
            {
                printf("%lg\n", roots[i]);
            }
            break;
    }
    return 0;
}

int print_result_text(const double *roots, long long result_code)
{
    assert(roots != NULL);
    
    switch (result_code)
    {
        case RESULT_INFINITE_SOLUTIONS:
            printf("inf");
            break;
        case RESULT_ERROR_EQUATION:
            printf(COLOR_RED("There is error in equation, probably nan.")"\n");
            break;
        default:
            for (long long i = 0; i < result_code; ++i)
            {
                printf("%lg\n", roots[i]);
            }
            break;
    }
    return 0;
}

int print_result(const double *roots, long long result_code)
{
    if (is_output_terminal())
    {
        return print_result_color(roots, result_code);
    }
    else
    {
        return print_result_text(roots, result_code);
    }
}

