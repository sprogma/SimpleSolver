#ifndef SOLVER_PROMPT3
#define SOLVER_PROMPT3


#include "common.h"
#include "solver.h"


struct coefficients_t_reflection_table_t
{
    const char *name; 
    int power; 
    double *ptr;
};


/*
    fill given reflection table using structure coefficients_t.
*/
void generate_reflection_structure(struct coefficients_t *coeff, struct coefficients_t_reflection_table_t *array);


/*
    read user input using read_double into coefficients_t stucture;

    return READ_COEFFICIENTS_EOF if find EOF while reading
    return 0 if there is no errors
*/
int read_coefficients_struct(struct coefficients_t *coefficients);


#endif

