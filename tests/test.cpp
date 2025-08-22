#include "stdio.h"
#include "assert.h"
#include "solver.h"
#include "float_compare.h"
#include "common.h"


void test_square_solver();
void test_linear_solver();


int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    test_square_solver();
    
    test_linear_solver();

    printf("Test end.\n");
    
    return 0;
}


void test_square_solver()
{
    FILE *file = fopen("tests/tests/square_solver.txt", "r");
    if (file == NULL)
    {
        fprintf(stderr, "file not found.\n");
        exit(1);
    }
    while (1)
    {
        struct coefficients_t coeff = {};
        enum solution_result_codes result = RESULT_0_SOLUTIONS;
        double roots[2] = {};
        enum solution_result_codes real_result = RESULT_0_SOLUTIONS;
        double real_roots[2] = {};

        /* read from file */
        int int_result;
        int scanned = fscanf(file, "%lg;%lg;%lg;%d;%lg;%lg", &coeff.a, &coeff.b, &coeff.c, 
                                                               &int_result, 
                                                               roots + 0, roots + 1);
        result = (enum solution_result_codes)int_result;
        
        if (scanned == EOF)
        {
            break;
        }
        else if (scanned != 6)
        {
            fprintf(stderr, "Wrong format in square_solver.txt file.\n");
            fclose(file);
            exit(1);
        }

        
        real_result = solve_square_equation(&coeff, real_roots);

        assert(real_result == result);
        
        switch (result)
        {
            case RESULT_1_SOLUTIONS:
                assert(f_compare_eq(real_roots[0], roots[0]));
                break;
            case RESULT_2_SOLUTIONS:
                    assert((f_compare_eq(real_roots[0], roots[0]) && f_compare_eq(real_roots[1], roots[1])) || 
                           (f_compare_eq(real_roots[0], roots[1]) && f_compare_eq(real_roots[1], roots[0])));
                break;
            case RESULT_0_SOLUTIONS:
            case RESULT_INFINITE_SOLUTIONS:
            default:
                break;
        }
    }
    fclose(file);
}


void test_linear_solver()
{
    FILE *file = fopen("tests/tests/linear_solver.txt", "r");
    if (file == NULL)
    {
        fprintf(stderr, "file not found.\n");
        exit(1);
    }
    while (1)
    {
        struct coefficients_t coeff = {};
        enum solution_result_codes result = RESULT_0_SOLUTIONS;
        double roots[2] = {};
        enum solution_result_codes real_result = RESULT_0_SOLUTIONS;
        double real_root = 0.0;

        /* read from file */
        int int_result;
        int scanned = fscanf(file, "%lg;%lg;%d;%lg\n", &coeff.b, &coeff.c, 
                                                       &int_result, 
                                                       roots + 0);
        result = (enum solution_result_codes)int_result;
       
        if (scanned == EOF)
        {
            break;
        }
        else if (scanned != 4)
        {
            fprintf(stderr, "Wrong format in linear_solver.txt file.\n");
            fclose(file);
            exit(1);
        }
        
        real_result = solve_linear_equation(&coeff, &real_root);

        assert(real_result == result);
        
        switch (result)
        {
            case RESULT_1_SOLUTIONS:
                assert(f_compare_eq(real_root, roots[0]));
                break;
            case RESULT_2_SOLUTIONS:
            case RESULT_0_SOLUTIONS:
            case RESULT_INFINITE_SOLUTIONS:
            default:
                break;
        }
    }
    fclose(file);
}
