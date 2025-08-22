#ifndef PARSE_COMMANDLINE_COEFFICIENTS
#define PARSE_COMMANDLINE_COEFFICIENTS


#include "solver.h"


/**
 * @brief print solvation of equation.
 *
 * @param[in] command line arguments
 * @param[in] command line arguments
 * @param[out] coeffitients to fill
 *
 * @return 0 if there is no error.
 */
int parse_commandline_coefficients(int argc, const char **argv, struct coefficients_t *coeffs);


#endif
