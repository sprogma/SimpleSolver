#ifndef SOLVER_PROMPT2
#define SOLVER_PROMPT2

#include "common.h"
#include "solver.h"


/**
 * @brief read user input using read_double into coefficients_t stucture;
 *
 * @param[out] coeffitients to fill
 *
 * @return 0 if there was no errors.
 */
int read_coefficients(struct coefficients_t *coefficients);


#endif

