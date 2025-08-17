#include "common.h"
#include "solver.h"
#include "output.h"

#include "stdio.h"

#include "color.h"


int print_result(double *roots, enum solution_result_codes result_code)
{
    if (is_out_terminal())
    {
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
    }
    else
    {
        switch (result_code)
        {
            case RESULT_0_SOLUTIONS:
                break;
            case RESULT_1_SOLUTIONS:
                printf("%g\n", roots[0]);
                break;
            case RESULT_2_SOLUTIONS:
                printf("%g\n%g\n", roots[0], roots[1]);
                break;
            case RESULT_INFINITE_SOLUTIONS:
                printf("inf");
                break;
            default:
                return 1;
        }
    }

    return 0;
}

