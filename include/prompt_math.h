#ifndef PROMPT_MATH
#define PROMPT_MATH

#include "common.h"
#include "solver.h"
#include "read_double.h"


/* 
 * @brief read input line and parse it in math form
 *
 * @param [out] coeff - return read coefficients here
 *
 * @return not zero on fail, zero on success, READ_COEFFICIENTS_EOF if read EOF.
 */
int read_coefficient_math_format(struct coefficients_t *coeff);


#endif
