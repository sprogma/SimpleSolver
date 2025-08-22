#ifndef SOLVER_PROMPT1
#define SOLVER_PROMPT1

#include "common.h"
#include "solver.h"


/*
    read user input using read_double into coefficients_t stucture;

    return READ_COEFFICIENTS_EOF if find EOF while reading
    return 0 if there is no errors
*/
int read_coefficients_copy(struct coefficients_t *coefficients);


#endif

