#ifndef POLINOMIAL
#define POLINOMIAL

#include "solver.h"

int coeff_add(struct coefficients_t *x, const struct coefficients_t *y);
int coeff_sub(struct coefficients_t *x, const struct coefficients_t *y);
int coeff_mul(struct coefficients_t *x, const struct coefficients_t *y);
int coeff_div(struct coefficients_t *x, const struct coefficients_t *y);

#endif
