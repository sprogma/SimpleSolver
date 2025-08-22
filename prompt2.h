#ifndef SOLVER_PROMPT2
#define SOLVER_PROMPT2

#include "common.h"
#include "solver.h"


const char * const coefficients_t_reflection_data[3] = {"c", "b", "a"};


union coefficients_converter_t
{
    struct coefficients_t coeff;
    double data[sizeof(struct coefficients_t) / sizeof(double)];
};



/*
    read user input using read_double into coefficients_t stucture;

    return READ_COEFFICIENTS_EOF if find EOF while reading
    return 0 if there is no errors
*/
int read_coefficients_union(struct coefficients_t *coefficients);


#endif

