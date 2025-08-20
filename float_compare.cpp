#include "common.h"
#include "float_compare.h"

#include "math.h"


int f_compare_eq(double a, double b)
{
    return fabs(a - b) < EPSILON;
}


int f_compare_lt(double a, double b)
{
    return a < b - EPSILON;
}


int f_compare_le(double a, double b)
{
    return a < b + EPSILON;
}
