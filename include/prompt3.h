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


/**
 * @brief fill given reflection table using structure coefficients_t.
 *
 * @param[in] coeffitients to fill from
 * @param[out] table to fill
 *
 */
void generate_reflection_structure(struct coefficients_t *coeff, struct coefficients_t_reflection_table_t *array);



/**
 * @brief read user input using read_double into coefficients_t stucture;
 *
 * @param[out] coeffitients to fill
 *
 * @return 0 if there was no errors.
 */
int read_coefficients_struct(struct coefficients_t *coefficients);


#endif

