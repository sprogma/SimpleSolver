#include "common.h"
#include "prompt3.h"
#include "read_double.h"


void generate_reflection_structure(struct coefficients_t *coeff, struct coefficients_t_reflection_table_t *array)
{
    array[0] = (struct coefficients_t_reflection_table_t){.name = "c", .power = 0, .ptr = &coeff->c};
    array[1] = (struct coefficients_t_reflection_table_t){.name = "b", .power = 1, .ptr = &coeff->b};
    array[2] = (struct coefficients_t_reflection_table_t){.name = "a", .power = 2, .ptr = &coeff->a};
}



int read_coefficients_struct(struct coefficients_t *coeff)
{
    assert(coeff != NULL);


    struct coefficients_t_reflection_table_t reflection_data[sizeof(*coeff) / sizeof(double)] = {};
    generate_reflection_structure(coeff, reflection_data);
    

    for (int i = 0; i < (int)arraylength(reflection_data); ++i)
    {
        int res = read_double(reflection_data[i].ptr, 
                              "Enter coefficient at x^%d [%s] > ", 
                              reflection_data[i].power,
                              reflection_data[i].name);
        if (res == READ_COEFFICIENTS_EOF) { return READ_COEFFICIENTS_EOF; }
        if (res != 0) { return 1; }
    }

    return 0;
}
