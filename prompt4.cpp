#include "common.h"
#include "prompt4.h"
#include "read_double.h"
#include "stddef.h"


int read_coefficients_offsets(struct coefficients_t *coeff)
{
    int res = 0;


    for (int i = 0; i < (int)arraylength(coefficients_t_reflection_table); ++i)
    {
        res = read_double((double *)((char *)coeff + coefficients_t_reflection_table[i].offset), 
                          "Enter coefficient at x^%d [%s] > ", 
                          coefficients_t_reflection_table[i].power,
                          coefficients_t_reflection_table[i].name);
        if (res == READ_COEFFICIENTS_EOF) { return READ_COEFFICIENTS_EOF; }
        if (res != 0) { return 1; }
    }

    return 0;
}
