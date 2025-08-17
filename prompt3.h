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


void generate_reflection_structure(struct coefficients_t *coeff, struct coefficients_t_reflection_table_t *array);


int read_coefficients_struct(struct coefficients_t *coefficients);


#endif

