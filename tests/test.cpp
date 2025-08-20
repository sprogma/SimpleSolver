#include "stdio.h"
#include "assert.h"
#include "../solver.h"
#include "../float_compare.h"
#include "../common.h"


#define ASSERT_SOLUTION(number, a, b)



struct solve_square_equation_unit_test
{
    struct coefficients_t coeff;
    
    /* right results */
    enum solution_result_codes result;
    double roots[2];
};

struct solve_square_equation_unit_test
       solve_square_tests[] = {
    {{ 0,  0,  0}, RESULT_INFINITE_SOLUTIONS, {          }},
    {{ 2,  1,  0}, RESULT_1_SOLUTIONS,        {-2.0,     }},
    {{-2, -1,  1}, RESULT_2_SOLUTIONS,        {-1.0,  2.0}},
    {{ 1, -2,  1}, RESULT_1_SOLUTIONS,        { 1.0      }},
    {{ 1,  2,  3}, RESULT_0_SOLUTIONS,        {          }},
    {{ 3,  2,  1}, RESULT_0_SOLUTIONS,        {          }},
};


struct solve_linear_equation_unit_test
{
    struct coefficients_t coeff;
    
    /* right results */
    enum solution_result_codes result;
    double root;
};

struct solve_linear_equation_unit_test
       solve_linear_tests[] = {
    {{ 1,  2,  0}, RESULT_1_SOLUTIONS, -0.5},
    {{ 3,  0,  0}, RESULT_0_SOLUTIONS,  0.0},
};



int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    enum solution_result_codes res;

    double roots[2] = {};

    for (int i = 0; i < (int)arraylength(solve_square_tests); ++i)
    {
        res = solve_square_equation(&solve_square_tests[i].coeff, roots);

        assert(res == solve_square_tests[i].result);
        
        switch (res)
        {
            case RESULT_1_SOLUTIONS:
                assert(f_compare_eq(roots[0], solve_square_tests[i].roots[0]));
                break;
            case RESULT_2_SOLUTIONS:
                    assert((f_compare_eq(roots[0], solve_square_tests[i].roots[0]) && f_compare_eq(roots[1], solve_square_tests[i].roots[1])) || 
                           (f_compare_eq(roots[0], solve_square_tests[i].roots[1]) && f_compare_eq(roots[1], solve_square_tests[i].roots[0])));
                break;
            case RESULT_0_SOLUTIONS:
            case RESULT_INFINITE_SOLUTIONS:
            default:
                break;
        }
    }

    
    for (int i = 0; i < (int)arraylength(solve_linear_tests); ++i)
    {
        res = solve_linear_equation(&solve_linear_tests[i].coeff, roots);

        assert(res == solve_linear_tests[i].result);
        
        switch (res)
        {
            case RESULT_1_SOLUTIONS:
                assert(f_compare_eq(roots[0], solve_linear_tests[i].root));
                break;
            case RESULT_0_SOLUTIONS:
            case RESULT_2_SOLUTIONS:
            case RESULT_INFINITE_SOLUTIONS:
            default:
                break;
        }
    }
    return 0;
}
