#include "complex.h"
#include "math.h"
#include "solver.h"
#include "float_compare.h"



int coeff_add(struct coefficients_t *x, const struct coefficients_t *y)
{
    assert(x != NULL);
    assert(y != NULL);
    x->a += y->a;
    x->b += y->b;
    x->c += y->c;
    return 0;
}

int coeff_sub(struct coefficients_t *x, const struct coefficients_t *y)
{
    assert(x != NULL);
    assert(y != NULL);
    x->a -= y->a;
    x->b -= y->b;
    x->c -= y->c;
    return 0;
}

int coeff_mul(struct coefficients_t *x, const struct coefficients_t *y)
{
    assert(x != NULL);
    assert(y != NULL);
    
    if (!f_compare_eq(x->a * y->a, 0.0) || 
        !f_compare_eq(x->a * y->b, 0.0) ||
        !f_compare_eq(x->b * y->a, 0.0))
    {
        fprintf(stderr, "Polinomial multiplication overflow. (may be appears x^3 or x^4)\n");
        return 1;
    }
    double a = x->a * y->c + x->b * y->b + x->c * y->a;
    double b = x->b * y->c + x->c * y->b;
    double c = x->c * y->c;
    x->a = a;
    x->b = b;
    x->c = c;
    return 0;
}

int coeff_div(struct coefficients_t *x, const struct coefficients_t *y)
{
    assert(x != NULL);
    assert(y != NULL);

    if (!f_compare_eq(y->a, 0.0) || 
        !f_compare_eq(y->b, 0.0))
    {
        fprintf(stderr, "Division on not scalar equation.\n");
        return 1;
    }

    x->a /= y->c;
    x->b /= y->c;
    x->c /= y->c;
    return 0;
}
