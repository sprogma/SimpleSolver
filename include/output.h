#ifndef SOLVER_OUTPUT
#define SOLVER_OUTPUT


#include "common.h"
#include "solver.h"



/**
 * @brief print solvation of equation.
 *
 * @param[in] roots to print (get them from solve* function)
 * @param[in] result_code from one of solve* functions.
 *
 * @return 0 on success.
 */
int print_result(const double* roots, enum solution_result_codes result_code);


#endif

