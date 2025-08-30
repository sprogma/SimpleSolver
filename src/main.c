#include "common.h"
#include "interactive.h"
#include "solve_commandline_args.h"
#include "cmdarg_parser.h"
#include "polinomial.h"

#include "string.h"
#include "errno.h"
#include "stdlib.h"
#include "stdio.h"
#include "ctype.h"
#include "inttypes.h"


int parse_arguments(int argc, const char **argv);
void *read_math_flag(void *args, int *global_curr, int argc, const char **argv);
void *read_cmdarg_coefficients(void *args, int *global_curr, int argc, const char **argv);



int main(int argc, const char **argv)
{
    return parse_arguments(argc, argv);
}


void *read_math_flag(void *args, int *global_curr, int argc, const char **argv)
{
    (void)args;
    (void)global_curr;
    (void)argc;
    (void)argv;
    return NULL;
}

void *read_cmdarg_coefficients(void *args, int *global_curr, int argc, const char **argv)
{
    if (args != NULL)
    {
        fprintf(stderr, "Found two arguments 'coeffs'. Ignore second one.\n");
        return args;
    }
    struct coefficients_t *coeffs = (struct coefficients_t *)calloc(sizeof(*coeffs), 1);
    coeffs->alloc = 0;
    coeffs->size = 0;
    coeffs->data = NULL;

    int curr = *global_curr;
    size_t id = 0;
    while (curr < argc)
    {
        char *end_ptr = NULL;
        double value = strtod(argv[curr], &end_ptr);
        
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

        coeff_alloc(coeffs, coeffs->size + 1);
        for (size_t i = coeffs->size - 1; i < coeffs->size; ++i)
        {
            coeffs->data[i + 1] = coeffs->data[i];
        }
        coeffs->data[0] = value;
        
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
    const char *math_flag_names[] = {
        "--math",
        "-m",
    };
    struct commandline_parser_entry_t args[] = {
        {
            .type = COMMANDLINE_PARSER_ARGUMENT,
            .info = "coefficients to solve",
            .key_length = arraylength(coeff_names),
            .key = coeff_names,
            .value = NULL,
            .read_function = &read_cmdarg_coefficients,
            .set = 0,
        },
        {
            .type = COMMANDLINE_PARSER_ARGUMENT,
            .info = "if set, parsing input as expression and evaluates it.",
            .key_length = arraylength(math_flag_names),
            .key = math_flag_names,
            .value = NULL,
            .read_function = &read_math_flag,
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
    uint32_t coeff_set = commandline_args_get_value(&parser, "--coeff", (void **)&coeff_arg);

    int math_flag_value = 0;
    if (commandline_args_get_value(&parser, "--math", (void **)NULL))
    {
        math_flag_value = 1;
    }

    /* call solvers */

    if (coeff_set)
    {
        assert(coeff_arg != NULL);
        return solve_command_line_coefficients(coeff_arg);
    }
    else
    {
        return run_interactive(math_flag_value);
    }
}
