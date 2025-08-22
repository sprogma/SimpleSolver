#ifndef FLOAT_COMPARE
#define FLOAT_COMPARE



/**
 * @brief this function is used to compare floats. Implements operator ==
 *
 * @param[in] first double
 * @param[in] second double
 * @return 1 if a == b using defined EPSILON, else - 0.
 */
int f_compare_eq(double a, double b);


/**
 * @brief this function is used to compare floats. Implements operator <
 *
 * @param[in] first double
 * @param[in] second double
 * @return 1 if a < b using defined EPSILON, else - 0.
 */
int f_compare_lt(double a, double b);


/**
 * @brief this function is used to compare floats. Implements operator <=
 *
 * @param[in] first double
 * @param[in] second double
 * @return 1 if a <= b using defined EPSILON, else - 0.
 */
int f_compare_le(double a, double b);

#endif
