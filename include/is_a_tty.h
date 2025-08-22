#ifndef IS_A_TTY
#define IS_A_TTY



/**
 * @brief check if stdout is terminal, or is redirected
 *
 * @return 1 if stdout is terminal, else - 0.
 */
int is_output_terminal();

/**
 * @brief check if stdin is terminal, or is redirected
 *
 * @return 1 if stdin is terminal, else - 0.
 */
int is_input_terminal();


#endif
