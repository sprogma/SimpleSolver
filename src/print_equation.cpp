#include "common.h"
#include "solver.h"
#include "is_a_tty.h"
#include "print_equation.h"
#include "stdio.h"

int print_equation(const struct coefficients_t *coeffs)
{
    printf("Solving equation %lg*x^2 + %lg*x + %lg\n", coeffs->a, coeffs->b, coeffs->c);
    return 0;
}
