#include "inttypes.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "stdarg.h"
#include "math.h"

#define arraylength(x) (sizeof(x)/sizeof(*x))

const int EQUATION_POWER = 2;
const int COEFF_LENGTH = 1;
const double EPSILON = 1e-7;

struct coefficients_t
{
    double c, b, a;
};


/* v1 : copy */



/* v2 : union */

const char * const coefficients_t_reflection_data[3] = {"c", "b", "a"};

union coefficients_converter_t
{
    struct coefficients_t coeff;
    double data[sizeof(struct coefficients_t) / sizeof(double)];
};







/* v3 : structure filled in runtime */

struct coefficients_t_reflection_table_t
{
    const char *name; 
    int power; 
    double *ptr;
};


void generate_reflection_structure(struct coefficients_t *coeff, struct coefficients_t_reflection_table_t *array)
{
    array[0] = (struct coefficients_t_reflection_table_t){.name = "c", .power = 0, .ptr = &coeff->c};
    array[1] = (struct coefficients_t_reflection_table_t){.name = "b", .power = 1, .ptr = &coeff->b};
    array[2] = (struct coefficients_t_reflection_table_t){.name = "a", .power = 2, .ptr = &coeff->a};
}






/* v4 : structure filled with macros at compilation time */

struct coefficients_t_global_reflection_table_line_t
{
    const char *name; 
    int power; 
    uintptr_t offset;
};

#define offset_of(type, field) ((uintptr_t)&(((type *)NULL)->field))

struct coefficients_t_global_reflection_table_line_t coefficients_t_reflection_table[] = {
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







int read_double(double *result, const char *fmt, ...);

int read_coefficients_copy(struct coefficients_t *coefficients);
int read_coefficients_union(struct coefficients_t *coefficients);
int read_coefficients_struct(struct coefficients_t *coefficients);
int read_coefficients_offsets(struct coefficients_t *coefficients);

/*  
    functions return count of writed roots, and
    will return RESULT_INFINITE_SOLUTIONS if there is infinite number of solutions.
*/
int solve_square_equation(const struct coefficients_t *coeff, double *roots);
int solve_linear_equation(const struct coefficients_t *coeff, double *roots);
const int RESULT_INFINITE_SOLUTIONS = -1;

int print_result(double *roots, int result_code);


int main(void)
{
    int return_code = -1;
    struct coefficients_t coeff = {};
    double roots[EQUATION_POWER] = {};

    return_code = read_coefficients_struct(&coeff);
    if (return_code != 0)
    {
        fprintf(stderr, "read_coefficients failed with code %d.\n", return_code);
        return 1;
    }



    int result_code = solve_square_equation(&coeff, roots);
    
    if (result_code == RESULT_INFINITE_SOLUTIONS)
    {
        fprintf(stderr, "This equation has an infinite number of solutions.\n");
        printf("inf\n");
    }

    return_code = print_result(roots, result_code);
    
    return 0;
}




int print_result(double *roots, int result_code)
{
    switch (result_code)
    {
        case 0:
            fprintf(stderr, "There is no solutions.\n");
            break;
        case 1:
            fprintf(stderr, "the only solution is:\n");
            fprintf(stdout, "%g\n", roots[0]);
            break;
        case 2:
            fprintf(stderr, "the solutions is both\n");
            fprintf(stdout, "%g\n", roots[0]);
            fprintf(stderr, "and\n");
            fprintf(stdout, "%g\n", roots[1]);
            break;
        case RESULT_INFINITE_SOLUTIONS:
            fprintf(stderr, "any number is solution.\n");
            fprintf(stdout, "inf\n");
            break;
        default:
            fprintf(stderr, "Wrong result code.\n");
            return 1;
    }
    return 0;
}





int read_double(double *result, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    
    int ch;
    *result = 0.0;
    while (1)
    {
        vfprintf(stderr, fmt, args);
        if (scanf("%lg", result) == 1)
        {
            break;
        }
        do { ch = getchar(); } 
        while (ch != EOF && ch != '\n');
    }
    va_end(args);
    return 0;
}




/* v1 : copy */

int read_coefficients_copy(struct coefficients_t *coeff)
{
    int res = 0;

    const char * const format_string = "Enter coefficient at x^%d [%s] > ";
    
    res = read_double(&coeff->c, format_string, 2, "c");
    if (res != 0) { return 1; }
    res = read_double(&coeff->b, format_string, 1, "b");
    if (res != 0) { return 1; }
    res = read_double(&coeff->a, format_string, 0, "a");
    if (res != 0) { return 1; }

    return 0;
}



/* v2 : union */

int read_coefficients_union(struct coefficients_t *coeff)
{
    int res;
    union coefficients_converter_t *converter = (union coefficients_converter_t *)coeff;

    for (int i = 0; i < (int)arraylength(converter->data); ++i)
    {
        res = read_double(converter->data + i, 
                          "Enter coefficient at x^%d [%s] > ", 
                          i, coefficients_t_reflection_data[i]);
        if (res != 0) { return 1; }
    }

    return 0;
}



/* v3 : runtime filling */

int read_coefficients_struct(struct coefficients_t *coeff)
{
    int res = 0;


    struct coefficients_t_reflection_table_t reflection_data[sizeof(*coeff) / sizeof(double)] = {};
    generate_reflection_structure(coeff, reflection_data);
    

    for (int i = 0; i < (int)arraylength(reflection_data); ++i)
    {
        res = read_double(reflection_data[i].ptr, 
                          "Enter coefficient at x^%d [%s] > ", 
                          reflection_data[i].power,
                          reflection_data[i].name);
        if (res != 0) { return 1; }
    }

    return 0;
}




/* v4 : offsets */

int read_coefficients_offsets(struct coefficients_t *coeff)
{
    int res = 0;


    for (int i = 0; i < (int)arraylength(coefficients_t_reflection_table); ++i)
    {
        res = read_double((double *)((char *)coeff + coefficients_t_reflection_table[i].offset), 
                          "Enter coefficient at x^%d [%s] > ", 
                          coefficients_t_reflection_table[i].power,
                          coefficients_t_reflection_table[i].name);
        if (res != 0) { return 1; }
    }

    return 0;
}




/* solvers */

int solve_square_equation(const struct coefficients_t *coeff, double *roots)
{
    if (fabs(coeff->a) < EPSILON)
    {
        return solve_linear_equation(coeff, roots);
    }

    double d = coeff->b * coeff->b - 4.0 * coeff->a * coeff->c;

    if (d < -EPSILON)
    {
        return 0;
    }

    if (d < EPSILON)
    {
        roots[0] = -coeff->b * 0.5 / coeff->a;
        return 1;
    }

    double sqrt_d = sqrt(d);

    roots[0] = (-coeff->b - sqrt_d) * 0.5 / coeff->a;
    roots[1] = (-coeff->b + sqrt_d) * 0.5 / coeff->a;

    return 2;
}

int solve_linear_equation(const struct coefficients_t *coeff, double *roots)
{        
    if (fabs(coeff->b) < EPSILON)
    {
        return (fabs(coeff->c) < EPSILON ? RESULT_INFINITE_SOLUTIONS : 0);
    }

    roots[0] = -coeff->c / coeff->b;
    
    return 1;
}
