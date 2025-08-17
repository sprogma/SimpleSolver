#ifndef SOLVER_PROMPT2
#define SOLVER_PROMPT2

#include "common.h"
#include "solver.h"


extern const char * const coefficients_t_reflection_data[3];


union coefficients_converter_t
{
    struct coefficients_t coeff;
    double data[sizeof(struct coefficients_t) / sizeof(double)];
};


int read_coefficients_union(struct coefficients_t *coefficients);


#endif

