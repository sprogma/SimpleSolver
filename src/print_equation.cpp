#include "common.h"
#include "solver.h"
#include "is_a_tty.h"
#include "print_equation.h"
#include "stdio.h"

int print_equation(const struct coefficients_t *coeffs)
{
    printf("Solving equation %lf*x^2 + %lf*x + %lf\n", coeffs->a, coeffs->b, coeffs->c);
    return 0;
}
