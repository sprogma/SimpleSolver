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



/**
 * @brief read user input using read_double into coefficients_t stucture;
 *
 * @param[out] coeffitients to fill
 *
 * @return 0 if there was no errors.
 */
int read_coefficients_union(struct coefficients_t *coefficients);


#endif

