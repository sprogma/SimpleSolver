#ifndef SOLVER_SOLVER
#define SOLVER_SOLVER


#include "common.h"
#include "polinomial.h"


#define RESULT_ERROR_EQUATION -2
#define RESULT_INFINITE_SOLUTIONS -1


/**
 * @brief function to solve linear equation
 *
 * @param[in] coefficients to solve
 * @param[out] returns roots - allocated array with roots
 *
 * @return RESULT_ERROR_EQUATION if given error equation, 
 *         RESULT_INFINITE_SOLUTIONS if there is infinite number of solutions - or other enum member.
 */
long long solve_equation(const struct coefficients_t *coeff, double **roots);;



#endif
