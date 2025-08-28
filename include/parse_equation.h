#ifndef PARSE_EQATION
#define PARSE_EQATION

#include "solver.h"

/*
 * @brief read coefficients from equation
 *
 * @param [in] equation - string to parse
 * @param [out] coefficients - fill coefficients to here
 *
 * @return 0 on success
 */
int parse_equation(const char *equation, struct coefficients_t *coefficients);


#endif
