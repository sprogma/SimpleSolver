#include "inttypes.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "math.h"


const int EQUATION_POWER = 2;
const int COEFF_LENGTH = 1;
const double EPSILON = 1e-7;


int read_coefficients(double *coefficients);

/*  
    functions return count of writed roots, and
    will return -1 if there is infinite number of solutions.
*/
int solve_square_equation(const double *coeff, double *roots);
int solve_linear_equation(const double *coeff, double *roots);


int main(void)
{
    int result_code = -1;
    double coeff[COEFF_LENGTH] = {};
    double roots[EQUATION_POWER] = {};

    result_code = read_coefficients(coeff);
    if (result_code != 0)
    {
        fprintf(stderr, "read_coefficients failed with code %d.\n", result_code);
        return 1;
    }



    result_code = solve_square_equation(coeff, roots);
    
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


int read_coefficients(double *coefficients)
{
    int ch;
    int id = 0;
    
    while (id < COEFF_LENGTH)
    {
        coefficients[id] = 0.0;
        while (1)
        {
            fprintf(stderr, "Enter coefficient at x^%d >", id);
            if (scanf("%lg", coefficients + id) == 1)
            {
                break;
            }
            do { ch = getchar(); } 
            while (ch != EOF && ch != '\n');
        }
        id++;
    }

    return 0;
}


int solve_square_equation(const double *coeff, double *roots)
{
    double a = coeff[2];
    double b = coeff[1];
    double c = coeff[0];
    
    if (fabs(a) < EPSILON)
    {
        return solve_linear_equation(coeff, roots);
    }

    double d = b * b - 4.0 * c * a;

    if (d < -EPSILON)
    {
        return 0;
    }

    if (d < EPSILON)
    {
        roots[0] = -b * 0.5 / a;
        return 1;
    }

    double sqrt_d = sqrt(d);

    roots[0] = (-b - sqrt_d) * 0.5 / a;
    roots[1] = (-b + sqrt_d) * 0.5 / a;

    return 2;
}

int solve_linear_equation(const double *coeff, double *roots)
{
    double a = coeff[2];
    double b = coeff[1];
        
    if (fabs(a) < EPSILON)
    {
        return (fabs(b) < EPSILON ? -1 : 0);
    }

    roots[0] = -b / a;
    
    return 1;
}
