#include "common.h"
#include "solver.h"
#include "is_a_tty.h"
#include "print_equation.h"
#include "float_compare.h"
#include "inttypes.h"
#include "stdio.h"

int print_equation(const struct coefficients_t *coeffs)
{
    int printed = 0;
    printf("Solving equation of power %d:\n", ((int)coeffs->size) - 1);
    for (size_t i = coeffs->size - 1; i < coeffs->size; --i)
    {
        if (!f_compare_eq(coeffs->data[i], 0.0))
        {
            if (printed)
            {
                printf(" + ");
            }
            printf("%lg", coeffs->data[i]);
            if (i != 0)
            {
                printf("*x^%d", (int)i);
            }
            printed = 1;
        }
    }
    if (!printed)
    {
        printf("0\n");
    }
    printf("\n");
    
    return 0;
}
