#include "common.h"
#include "solver.h"

#include "math.h"


#define F_COMPARE_LT(a, b) ((a) < (b) - EPSILON)
#define F_COMPARE_LE(a, b) ((a) < (b) + EPSILON)
#define F_COMPARE_EQ(a, b) (fabs((a) - (b)) < EPSILON)



enum solution_result_codes solve_square_equation(const struct coefficients_t *coeff, double *roots)
{
    if (F_COMPARE_EQ(coeff->a, 0.0))
    {
        return solve_linear_equation(coeff, roots);
    }

    double d = coeff->b * coeff->b - 4.0 * coeff->a * coeff->c;

    if (F_COMPARE_LT(d, 0.0))
    {
        return RESULT_0_SOLUTIONS;
    }

    if (F_COMPARE_LE(d, 0.0))
    {
        roots[0] = -coeff->b * 0.5 / coeff->a;
        return RESULT_1_SOLUTIONS;
    }

    double sqrt_d = sqrt(d);

    roots[0] = (-coeff->b - sqrt_d) * 0.5 / coeff->a;
    roots[1] = (-coeff->b + sqrt_d) * 0.5 / coeff->a;

    return RESULT_2_SOLUTIONS;
}


enum solution_result_codes solve_linear_equation(const struct coefficients_t *coeff, double *roots)
{        
    if (F_COMPARE_EQ(coeff->b, 0.0))
    {
        return (F_COMPARE_EQ(coeff->c, 0.0) ? RESULT_INFINITE_SOLUTIONS : RESULT_0_SOLUTIONS);
    }

    roots[0] = -coeff->c / coeff->b;
    
    return RESULT_1_SOLUTIONS;
}
