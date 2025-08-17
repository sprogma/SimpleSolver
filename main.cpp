#include "inttypes.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "math.h"


const int EQUATION_POWER = 2;
const int COEFF_LENGTH = 1;
const double EPSILON = 1e-7;


struct coefficients_t
{
    double a, b, c;
};


int read_double(double *result, const char *text);
int read_coefficients(struct coefficients_t *coefficients);

/*  
    functions return count of writed roots, and
    will return -1 if there is infinite number of solutions.
*/
int solve_square_equation(const struct coefficients_t *coeff, double *roots);
int solve_linear_equation(const struct coefficients_t *coeff, double *roots);


int main(void)
{
    int result_code = -1;
    struct coefficients_t coeff = {};
    double roots[EQUATION_POWER] = {};

    result_code = read_coefficients(&coeff);
    if (result_code != 0)
    {
        fprintf(stderr, "read_coefficients failed with code %d.\n", result_code);
        return 1;
    }



    result_code = solve_square_equation(&coeff, roots);
    
    if (result_code == -1)
    {
        fprintf(stderr, "This equation has an infinite number of solutions.\n");
        printf("inf\n");
    }
    
    fprintf(stderr, "Found %d roots%c\n", result_code, (result_code ? ':' : '.'));
    for (int i = 0; i < result_code; ++i)
    {
        printf("%g\n", roots[i]);
    }    
    
    return 0;
}


int read_double(double *result, const char *text)
{
    int ch;
    *result = 0.0;
    while (1)
    {
        fprintf(stderr, text);
        if (scanf("%lg", result) == 1)
        {
            break;
        }
        do { ch = getchar(); } 
        while (ch != EOF && ch != '\n');
    }
    return 0;
}



int read_coefficients(struct coefficients_t *coeff)
{
    int res = 0;

    res = read_double(&coeff->c, "Enter coefficient at x^0 [c] > ");
    if (res != 0) { return 1; }
    
    res = read_double(&coeff->b, "Enter coefficient at x^1 [b] > ");
    if (res != 0) { return 1; }
    
    res = read_double(&coeff->a, "Enter coefficient at x^2 [a] > ");
    if (res != 0) { return 1; }

    return 0;
}


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
        return (fabs(coeff->c) < EPSILON ? -1 : 0);
    }

    roots[0] = -coeff->c / coeff->b;
    
    return 1;
}
