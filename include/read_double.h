#ifndef SOLVER_READ_DOUBLE
#define SOLVER_READ_DOUBLE


#include "common.h"


#define READ_COEFFICIENTS_EOF (-1)
#define READ_COEFFICIENTS_FGETS_ERROR 1


/**
 * @brief read double value from stdin.
 *        validates input, also read entire line
 *        not validates input on nan/inf/denormalized
 *
 * @param[out] double to read
 * @param[in] fmt - prompt format string.
 * @param[in] ... prompt arguments
 *
 * @return READ_COEFFICIENTS_EOF if read EOF, else - 0 if there was no errors.
 */
int read_double(double *result, const char *fmt, ...);

#endif

