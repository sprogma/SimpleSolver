#include "common.h"
#include "parse_equation.h"
#include "prompt_math.h"
#include "is_a_tty.h"
#include "solver.h"
#include "stdio.h"


int read_coefficient_math_format(struct coefficients_t *coeff)
{
    while (1)
    {
        if (is_input_terminal())
        {
            fprintf(stderr, "Enter equation in math form\n");
        }
        char s[1024];
        char *result = fgets(s, sizeof(s), stdin);
        if (result == NULL)
        {
            if (feof(stdin))
            {
                return READ_COEFFICIENTS_EOF;
            }
            fprintf(stderr, "Unknown error in fgets.\n");
            return 1;
        }

        int parse_code = parse_equation(s, coeff);
        if (parse_code == 0)
        {
            break;
        }
        fprintf(stderr, "Error in input.\n");
    }

    return 0;
}
