#include "common.h"
#include "solver.h"
#include "output.h"

#include "stdio.h"

#include "is_a_tty.h"
#include "color.h"


int print_result_color(const double *roots, enum solution_result_codes result_code);
int print_result_text(const double *roots, enum solution_result_codes result_code);

int print_result_color(const double *roots, enum solution_result_codes result_code)
{
    assert(roots != NULL);
    
    switch (result_code)
    {
        case RESULT_0_SOLUTIONS:
            printf(COLOR_RED("There is no solutions.") "\n" );
            break;
        case RESULT_1_SOLUTIONS:
            printf(COLOR_GREEN("The only solution is: %g") "\n", roots[0]);
            break;
        case RESULT_2_SOLUTIONS:
            printf(COLOR_GREEN("The solutions is both %g and %g")"\n", roots[0], roots[1]);
            break;
        case RESULT_INFINITE_SOLUTIONS:
            printf(COLOR_YELLOW("Any number is solution")"\n");
            break;
        default:
            printf(COLOR_RED("Wrong result code.")"\n");
            return 1;
    }
    return 0;
}

int print_result_text(const double *roots, enum solution_result_codes result_code)
{
    assert(roots != NULL);
    
    switch (result_code)
    {
        case RESULT_0_SOLUTIONS:
            break;
        case RESULT_1_SOLUTIONS:
            printf("%.20g\n", roots[0]);
            break;
        case RESULT_2_SOLUTIONS:
            printf("%.20g\n%.20g\n", roots[0], roots[1]);
            break;
        case RESULT_INFINITE_SOLUTIONS:
            printf("inf");
            break;
        default:
            return 1;
    }
    return 0;
}

int print_result(const double *roots, enum solution_result_codes result_code)
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

