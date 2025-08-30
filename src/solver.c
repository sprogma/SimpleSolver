#include "common.h"
#include "solver.h"
#include "float_compare.h"

#include "math.h"


static long long solve_equation_recursive(const struct coefficients_t *coeff, double **roots);
static long long solve_square_equation(const struct coefficients_t *coeff, double **roots);
static long long solve_linear_equation(const struct coefficients_t *coeff, double **roots);


long long solve_equation(const struct coefficients_t *coeff, double **roots)
{
    long long count = solve_equation_recursive(coeff, roots);
    switch (count)
    {
        case RESULT_ERROR_EQUATION:
            return RESULT_ERROR_EQUATION;
        case RESULT_INFINITE_SOLUTIONS:
            return RESULT_INFINITE_SOLUTIONS;
        default:
           break; 
    }
    /* remove  */
    return count;
}

static long long solve_equation_recursive(const struct coefficients_t *coeff, double **roots)
{
    switch (coeff->size)
    {
        case 0:
        case 1:
        case 2:
        case 3:
            return solve_square_equation(coeff, roots);
        default:
        {
            struct coefficients_t dydx = {};
            double *dydx_roots = NULL;

            coeff_alloc(&dydx, coeff->size - 1);
            dydx.size = coeff->size - 1;
            for (size_t i = 1; i < coeff->size; ++i)
            {
                dydx.data[i - 1] = coeff->data[i] * (double)i;
            }

            long long count = solve_equation(&dydx, &dydx_roots);

            printf("READ %d ROOTS\n", (int)count);

            switch (count)
            {
                case RESULT_ERROR_EQUATION:
                    return RESULT_ERROR_EQUATION;
                case RESULT_INFINITE_SOLUTIONS:
                    *roots = NULL;
                    return (f_compare_eq(coeff->data[0], 0.0) ? RESULT_INFINITE_SOLUTIONS : 0);
                default:
                {   
                    long long root_id = 0;
                    *roots = malloc(sizeof(**roots) * coeff->size);
                    /* for each segment: find root on it */
                    double total_left = 0.0, total_right = 0.0;
                    {
                        total_left = dydx_roots[0];
                        total_right = dydx_roots[count - 1];

                        {
                            double start_sign = copysign(1.0, coeff_get(coeff, total_left)), value = 1.0;
                            while (total_left - value > -1e200 && copysign(1.0, coeff_get(coeff, total_left - value)) == start_sign)
                            {
                                value *= 2.0;
                            }
                            total_left -= value;
                        }
                        {
                            double start_sign = copysign(1.0, coeff_get(coeff, total_right)), value = 1.0;
                            while (total_right + value < 1e200 && copysign(1.0, coeff_get(coeff, total_right + value)) == start_sign)
                            {
                                value *= 2.0;
                            }
                            total_right += value;
                        }   
                    }
                    for (long long left = -1, right = 0; right <= count; ++left, ++right)
                    {   
                        double pos_left = (left == -1 ? total_left : dydx_roots[left]);
                        double pos_right = (right == count ? total_right : dydx_roots[right]);
                        double a = coeff_get(coeff, pos_left);
                        double b = coeff_get(coeff, pos_right);
                        printf("Search on %lg --- %lg\n", pos_left, pos_right);
                        if (fabs(a) < fabs(coeff_get(&dydx, pos_left)) * 1e-5)
                        {
                            (*roots)[root_id++] = pos_left;
                            printf("left is root %lg:\n", pos_left);
                        }
                        if (fabs(b) < fabs(coeff_get(&dydx, pos_right)) * 1e-5)
                        {
                            if (right == count)
                            {
                                (*roots)[root_id++] = pos_right;
                                printf("right is root %lg:\n", pos_left);
                            }
                            continue;
                        }
                        if (a > b)
                        {
                            double tmp = pos_right;
                            pos_right = pos_left;
                            pos_left = tmp;
                            tmp = b;
                            b = a;
                            a = tmp;
                        }
                        if ((a < 0 && b < 0) || (a > 0 && b > 0) || isinf(a) || isinf(b))
                        {
                            continue;
                        }
                        double mid = 0.0;
                        while (fabs(pos_right - pos_left) > 1e-10)
                        {
                            mid = (pos_left + pos_right) * 0.5;
                            if (coeff_get(coeff, mid) < 0)
                            {
                                pos_left = mid;
                            }
                            else
                            {
                                pos_right = mid;
                            }
                        }
                        mid = (pos_left + pos_right) * 0.5;
                        if (fabs(coeff_get(coeff, mid)) < fabs(coeff_get(&dydx, mid)) * 1e-5)
                        {
                            (*roots)[root_id++] = mid;
                            printf("find root %lg: %lg < %lg\n", mid, fabs(coeff_get(coeff, mid)), fabs(coeff_get(&dydx, mid)) * 1e-5);
                        }
                    }
                    printf("FOR POWER %d RETURN:\n", (int)coeff->size - 1);
                    for (long long i = 0; i < root_id; ++i)
                    {
                        printf("  %lg", (*roots)[i]);
                    }
                    printf("\n");
                    return root_id;
                }
            }                
        }
    }
}

static long long solve_square_equation(const struct coefficients_t *coeff, double **roots)
{
    assert(coeff != NULL);
    assert(roots != NULL);


    for (size_t i = 0; i < coeff->size; ++i)
    {
        if (isnan(coeff->data[i]))
        {
            return RESULT_ERROR_EQUATION;
        }
    }
    
    if (f_compare_eq(coeff->data[2], 0.0))
    {
        return solve_linear_equation(coeff, roots);
    }
    
    *roots = malloc(sizeof(**roots) * 2);

    double d = coeff->data[1] * coeff->data[1] - 4.0 * coeff->data[2] * coeff->data[0];

    if (f_compare_lt(d, 0.0))
    {
        return 0;
    }

    if (f_compare_le(d, 0.0))
    {
        (*roots)[0] = -coeff->data[1] * 0.5 / coeff->data[2];
        return 1;
    }

    double sqrt_d = sqrt(d);

    (*roots)[0] = (-coeff->data[1] - sqrt_d) * 0.5 / coeff->data[2];
    (*roots)[1] = (-coeff->data[1] + sqrt_d) * 0.5 / coeff->data[2];

    return 2;
}


static long long solve_linear_equation(const struct coefficients_t *coeff, double **roots)
{        
    assert(coeff != NULL);
    assert(roots != NULL);

    *roots = malloc(sizeof(**roots) * 2);
    
    if (f_compare_eq(coeff->data[1], 0.0))
    {
        return (f_compare_eq(coeff->data[0], 0.0) ? RESULT_INFINITE_SOLUTIONS : 0);
    }

    (*roots)[0] = -coeff->data[0] / coeff->data[1];
    
    return 1;
}
