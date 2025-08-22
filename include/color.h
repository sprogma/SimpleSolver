#ifndef SOLVER_COLOR
#define SOLVER_COLOR


/**
 * #COLOR_RED(string)
 * @brief this is macros to color text in RED color.
 *
 * @param[in] compile time string literal to color.
 * @return compile time string literal, but colored.
 */
#define COLOR_RED(string)    "\x1B[31m" string "\x1B[0m"

/**
 * #COLOR_GREEN(string)
 * @brief this is macros to color text in GREEN color.
 *
 * @param[in] compile time string literal to color.
 * @return compile time string literal, but colored.
 */
#define COLOR_GREEN(string)  "\x1B[32m" string "\x1B[0m"

/**
 * #COLOR_YELLOW(string)
 * @brief this is macros to color text in YELLOW color.
 *
 * @param[in] compile time string literal to color.
 * @return compile time string literal, but colored.
 */
#define COLOR_YELLOW(string) "\x1B[33m" string "\x1B[0m"


#endif
