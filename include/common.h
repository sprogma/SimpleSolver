#ifndef SOLVER_COMMON
#define SOLVER_COMMON


#include "stddef.h"
#include "stdio.h"
#define ALWAYS_USE_BEST_ASSERT
#include "best_assert.h"


const int EQUATION_POWER = 2;
const int COEFF_LENGTH = 1;
const double EPSILON = 1e-7;


#define arraylength(x) (sizeof(x)/sizeof(*x))



#endif
