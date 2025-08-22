#include "common.h"
#include "solver.h"
#include "interactive.h"
#include "solve_commandline_args.h"
#include "parse_commandline_coefficients.h"
#include "cmdarg_parser.h"

#include "string.h"
#include "errno.h"
#include "stdlib.h"
#include "stdio.h"
#include "ctype.h"
#include "inttypes.h"


int parse_arguments(int argc, const char **argv);


int main(int argc, const char **argv)
{
    return parse_arguments(argc, argv);
}



int parse_arguments(int argc, const char **argv)
{
    const char *coeff_names[] = {
        "--coeff",
        "-c",
    };
    struct commandline_argument_t args[] = {
        {
            .info = "coefficients to solve",
            .key_length = arraylength(coeff_names),
            .key = coeff_names,
            .value = {},
        },
    };
    struct commandline_parser_t parser = {};
    int init_cmdarg_result = initializate_commandline_args(&parser, 
                                                           NULL, 0, 
                                                           args, arraylength(args));

    commandline_args_parse(&parser, argc - 1, argv + 1);


    /* is threre --coeff argument? */
    struct commandline_argument_value_t coeff_arg;
    int coeff_set = commandline_args_get_value(&parser, "--coeff", &coeff_arg);

    /* call solvers */

    if (coeff_set)
    {
        struct coefficients_t coeffs = {};
        int res = parse_commandline_coefficients(coeff_arg.value_length, coeff_arg.value, &coeffs);
        if (res != 0)
        {
            fprintf(stderr, "Error while parse commandline coefficients.\n");
            return res;
        }
        return solve_command_line_coefficients(&coeffs);
    }
    else
    {
        return run_interactive();
    }
}
