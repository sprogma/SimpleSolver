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



/**
 * @brief function to solve linear equation
 *
 * @param[in] coefficients to solve
 * @param[out] roots to save solvation
 *
 * @return RESULT_INFINITE_SOLUTIONS if there is infinite number of solutions - or other enum member.
 */
enum solution_result_codes solve_square_equation(const struct coefficients_t *coeff, double *roots);
/**
 * @brief function to solve linear equation
 *
 * @param[in] coefficients to solve
 * @param[out] roots to save solvation
 *
 * @return RESULT_INFINITE_SOLUTIONS if there is infinite number of solutions - or other enum member.
 */
enum solution_result_codes solve_linear_equation(const struct coefficients_t *coeff, double *roots);



#endif
