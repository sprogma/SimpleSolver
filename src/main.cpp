#include "common.h"
#include "solver.h"
#include "interactive.h"
#include "solve_commandline_args.h"
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



void *read_coefficients(void *args, int *global_curr, int argc, const char **argv)
{
    if (args != NULL)
    {
        fprintf(stderr, "Found two arguments 'coeffs'. Ignore second one.\n");
        return args;
    }
    struct coefficients_t *coeffs = (struct coefficients_t *)calloc(sizeof(*coeffs), 1);

    int curr = *global_curr;
    double value = 0.0;
    size_t id = 0;
    while (curr < argc)
    {
        char *end_ptr = NULL;
        value = strtod(argv[curr], &end_ptr);
        
        while (isspace(*end_ptr)) { end_ptr++; }

        if (errno == ERANGE)
        {        
            fprintf(stderr, "Overflow/Underflow in command line arguments.\n");
            errno = 0;

            exit(1);
        }

        if (*end_ptr != 0)
        {
            break;
        }             

        switch (id)
        {
            case 0:
               coeffs->c = value;
               break;
            case 1:
               coeffs->b = coeffs->c;
               coeffs->c = value;
               break;
            case 2:
               coeffs->a = coeffs->b;
               coeffs->b = coeffs->c;
               coeffs->c = value;
               break;
            default:
                fprintf(stderr, "Warning: too many coefficients given. skip them.\n");
                break;
        }
        
        id++;
        curr++;
    }
    
    *global_curr = curr;
    return coeffs;
}



int parse_arguments(int argc, const char **argv)
{
    const char *coeff_names[] = {
        "--coeff",
        "-c",
    };
    struct commandline_parser_entry_t args[] = {
        {
            .type = COMMANDLINE_PARSER_ARGUMENT,
            .info = "coefficients to solve",
            .key_length = arraylength(coeff_names),
            .key = coeff_names,
            .value = NULL,
            .read_function = &read_coefficients,
            .set = 0,
        },
    };
    struct commandline_parser_t parser = {};
    int init_cmdarg_result = initializate_commandline_args(&parser, 
                                                           args, arraylength(args));

    if (init_cmdarg_result != 0)
    {
        return 1;
    }

    commandline_args_parse(&parser, argc - 1, argv + 1);


    /* is threre --coeff argument? */
    struct coefficients_t *coeff_arg;
    int coeff_set = commandline_args_get_value(&parser, "--coeff", (void **)&coeff_arg);


    /* call solvers */

    if (coeff_set)
    {
        assert(coeff_arg != NULL);
        return solve_command_line_coefficients(coeff_arg);
    }
    else
    {
        return run_interactive();
    }
}
