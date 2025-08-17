#ifndef SOLVER_SOLVER
#define SOLVER_SOLVER


#include "common.h"


struct coefficients_t
{
    double c, b, a;
};


enum solution_result_codes
{
    RESULT_INFINITE_SOLUTIONS = -1,
    RESULT_0_SOLUTIONS = 0,
    RESULT_1_SOLUTIONS = 1,
    RESULT_2_SOLUTIONS = 2,
};


/*  
    functions return count of writed roots, and
    will return RESULT_INFINITE_SOLUTIONS if there is infinite number of solutions.
*/
enum solution_result_codes solve_square_equation(const struct coefficients_t *coeff, double *roots);
enum solution_result_codes solve_linear_equation(const struct coefficients_t *coeff, double *roots);



#endif
