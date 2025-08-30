#include "common.h"
#include "solver.h"
#include "output.h"
#include "color.h"
#include "read_double.h"
#include "is_a_tty.h"
#include "print_equation.h"
#include "interactive.h"

#include "prompt2.h"
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
        double *roots = NULL;

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
            return_code = read_coefficients(&coeff);
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

        coeff_strip(&coeff);
        
        int print_code = print_equation(&coeff);
        if (print_code != 0)
        {
            fprintf(stderr, "Error in printing equation.\n");
            return 1;
        }

        long long result_code = solve_equation(&coeff, &roots);

        return_code = print_result(roots, result_code);
        if (return_code != 0)
        {
            fprintf(stderr, "Error in printing answer.\n");
            return 1;
        }

        free(roots);

        if (math_input)
        {
            exit(0);
        }
    }
    while (1);
    
    return 0;
}
