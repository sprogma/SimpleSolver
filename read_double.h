#ifndef SOLVER_READ_DOUBLE
#define SOLVER_READ_DOUBLE


#include "common.h"


const int READ_COEFFICIENTS_EOF = -1;
const int READ_COEFFICIENTS_FGETS_ERROR = 1;


/*
    read double value from stdin.
    validates input, also read entire line

    not validates input on nan/inf/denormalized

    return READ_COEFFICIENTS_EOF if read EOF,
    return 0 if there is no errors
*/
int read_double(double *result, const char *fmt, ...);

#endif

