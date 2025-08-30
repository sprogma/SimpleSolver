#include "common.h"
#include "output.h"
#include "solve_commandline_args.h"

#include "stdio.h"
#include "stdlib.h"


int solve_command_line_coefficients(struct coefficients_t *coeff)
{
    assert(coeff != NULL);

    int return_code = -1;
    double *roots = NULL;

    long long result_code = solve_equation(coeff, &roots);

    return_code = print_result(roots, result_code);
    if (return_code != 0)
    {
        fprintf(stderr, "Error in printing answer.\n");
        return 1;
    }
    
    return 0;
}
