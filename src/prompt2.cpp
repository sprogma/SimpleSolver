#include "common.h"
#include "prompt2.h"
#include "read_double.h"


int read_coefficients_union(struct coefficients_t *coeff)
{
    assert(coeff != NULL);
    
    union coefficients_converter_t *converter = (union coefficients_converter_t *)coeff;

    for (int i = 0; i < (int)arraylength(converter->data); ++i)
    {
        int res = read_double(converter->data + i, 
                              "Enter coefficient at x^%d [%s] > ", 
                              i, coefficients_t_reflection_data[i]);
        if (res == READ_COEFFICIENTS_EOF) { return READ_COEFFICIENTS_EOF; }
        if (res != 0) { return 1; }
    }

    return 0;
}
