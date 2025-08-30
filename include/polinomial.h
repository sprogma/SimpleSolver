#ifndef POLINOMIAL
#define POLINOMIAL

#include "solver.h"

struct coefficients_t
{
    size_t size;
    size_t alloc;
    double *data;
};

double coeff_get(const struct coefficients_t *x, double pos);
int coeff_alloc(struct coefficients_t *x, size_t size);
int coeff_strip(struct coefficients_t *x);
int coeff_add(struct coefficients_t *x, const struct coefficients_t *y);
int coeff_sub(struct coefficients_t *x, const struct coefficients_t *y);
int coeff_mul(struct coefficients_t *x, const struct coefficients_t *y);
int coeff_div(struct coefficients_t *x, const struct coefficients_t *y);

#endif
