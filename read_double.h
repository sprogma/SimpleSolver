#ifndef SOLVER_READ_DOUBLE
#define SOLVER_READ_DOUBLE


#include "common.h"


const int READ_COEFFICIENTS_EOF = -1;
const int READ_COEFFICIENTS_FGETS_ERROR = 1;


int read_double(double *result, const char *fmt, ...);

#endif

