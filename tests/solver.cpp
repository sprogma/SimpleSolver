#include "stdio.h"
#include "assert.h"
#include "../solver.h"
#include "../float_compare.h"


#define ASSERT_SOLUTION(number, a, b)


int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    enum solution_result_codes res;

    double roots[2] = {};

    struct coefficients_t coeff;

    {
        coeff = (struct coefficients_t){0, 0, 0};

        res = solve_square_equation(&coeff, roots);

        assert(res == RESULT_INFINITE_SOLUTIONS);
    }

    {
        coeff = (struct coefficients_t){2, 1, 0};

        res = solve_square_equation(&coeff, roots);

        assert(res == RESULT_1_SOLUTIONS);
        assert(f_compare_eq(roots[0], -2.0));
    }

    {
        coeff = (struct coefficients_t){-2, -1, 1};

        res = solve_square_equation(&coeff, roots);

        assert(res == RESULT_2_SOLUTIONS);
        assert((f_compare_eq(roots[0], -1.0) && f_compare_eq(roots[1], 2.0)) || 
               (f_compare_eq(roots[1], -1.0) && f_compare_eq(roots[0], 2.0)));
    }

    {
        coeff = (struct coefficients_t){1, -2, 1};

        res = solve_square_equation(&coeff, roots);

        assert(res == RESULT_1_SOLUTIONS);
        assert(f_compare_eq(roots[0], 1.0));
    }

    {
        coeff = (struct coefficients_t){1, 2, 3};

        res = solve_square_equation(&coeff, roots);

        assert(res == RESULT_0_SOLUTIONS);
    }

    {
        coeff = (struct coefficients_t){3, 2, 1};

        res = solve_square_equation(&coeff, roots);

        assert(res == RESULT_0_SOLUTIONS);
    }

    {
        coeff = (struct coefficients_t){1, 2, 0};

        res = solve_linear_equation(&coeff, roots);

        assert(res == RESULT_1_SOLUTIONS);
        assert(f_compare_eq(roots[0], -0.5));
    }

    return 0;
}
