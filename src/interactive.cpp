#include "common.h"
#include "solver.h"
#include "output.h"
#include "color.h"
#include "read_double.h"
#include "is_a_tty.h"
#include "print_equation.h"
#include "interactive.h"

#include "prompt1.h"
#include "prompt2.h"
#include "prompt3.h"
#include "prompt4.h"
#include "prompt_math.h"


#include "string.h"
#include "stdlib.h"
#include "stdio.h"


int run_interactive(int math_input)
{    
    do
    {
        int return_code = -1;
        struct coefficients_t coeff = {};
        double roots[EQUATION_POWER] = {};

        if (math_input)
        {
            return_code = read_coefficient_math_format(&coeff);
            if (return_code == READ_COEFFICIENTS_EOF)
            {
                return 0;
            }
            if (return_code != 0)
            {
                fprintf(stderr, "read_coefficients failed with code %d.\n", return_code);
                return 1;
            }
        }
        else
        {
            return_code = read_coefficients_union(&coeff);
            if (return_code == READ_COEFFICIENTS_EOF)
            {
                return 0;
            }
            if (return_code != 0)
            {
                fprintf(stderr, "read_coefficients failed with code %d.\n", return_code);
                return 1;
            }
        }


        int print_code = print_equation(&coeff);
        if (print_code != 0)
        {
            fprintf(stderr, "Error in printing equation.\n");
            return 1;
        }

        enum solution_result_codes result_code = solve_square_equation(&coeff, roots);

        return_code = print_result(roots, result_code);
        if (return_code != 0)
        {
            fprintf(stderr, "Error in printing answer.\n");
            return 1;
        }
    }
    while (1);
    
    return 0;
}
