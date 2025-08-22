#ifndef PARSE_COMMANDLINE_COEFFICIENTS
#define PARSE_COMMANDLINE_COEFFICIENTS


#include "solver.h"


/*
    parse_commandline_coefficients returns 0 if there is no error.

    argc/argv - command line arguments

    curr_ptr - pointer on integer, which points on "--coeff" or "-c" flag
               there will be writed position of end of this argument.

    coeffs - coefficients to fill
*/
int parse_commandline_coefficients(int argc, const char **argv, int *curr_ptr, struct coefficients_t *coeffs);


#endif
