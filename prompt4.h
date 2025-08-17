#ifndef SOLVER_PROMPT4
#define SOLVER_PROMPT4


#include "common.h"
#include "solver.h"

#include "inttypes.h"



struct coefficients_t_global_reflection_table_line_t
{
    const char *name; 
    int power; 
    uintptr_t offset;
};

#define offset_of(type, field) ((uintptr_t)&(((type *)NULL)->field))

const struct coefficients_t_global_reflection_table_line_t coefficients_t_reflection_table[] = {
    {.name = "c", .power = 0, .offset = offset_of(struct coefficients_t, c)},
    {.name = "b", .power = 1, .offset = offset_of(struct coefficients_t, b)},
    {.name = "a", .power = 2, .offset = offset_of(struct coefficients_t, a)},
};

/* or use more macroses:

#define table_entry(type, field, _power) \
    {.name = (# field), .power = _power, .offset = ((uintptr_t)&(((type *)NULL)->field))}

struct coefficients_t_global_reflection_table_line_t coefficients_t_reflection_table[] = {
    table_entry(struct coefficients_t, c, 0),
    table_entry(struct coefficients_t, b, 1),
    table_entry(struct coefficients_t, a, 2),
};

*/


int read_coefficients_offsets(struct coefficients_t *coefficients);


#endif

