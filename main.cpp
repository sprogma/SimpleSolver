#include "common.h"
#include "solver.h"
#include "output.h"
#include "color.h"
#include "read_double.h"

#include "prompt1.h"
#include "prompt2.h"
#include "prompt3.h"
#include "prompt4.h"


#include "string.h"
#include "stdlib.h"
#include "stdio.h"


int main(void)
{
    do
    {
        int return_code = -1;
        struct coefficients_t coeff = {};
        double roots[EQUATION_POWER] = {};

        return_code = read_coefficients_struct(&coeff);
        if (return_code == READ_COEFFICIENTS_EOF)
        {
            return 0;
        }
        if (return_code != 0)
        {
            fprintf(stderr, "read_coefficients failed with code %d.\n", return_code);
            return 1;
        }


        enum solution_result_codes result_code = solve_square_equation(&coeff, roots);
        
        if (result_code == RESULT_INFINITE_SOLUTIONS)
        {
            fprintf(stderr, "This equation has an infinite number of solutions.\n");
            printf("inf\n");
        }

        return_code = print_result(roots, result_code);
    }
    while (is_in_terminal());
    return 0;
}
