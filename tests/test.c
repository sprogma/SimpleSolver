#include "stdio.h"
#include "assert.h"
#include "solver.h"
#include "float_compare.h"
#include "common.h"


int test_square_solver();
int test_linear_solver();


int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    int error = 0;
    
    error |= test_square_solver();
    
    error |= test_linear_solver();

    if (error)
    {
        printf("Some tests was failed.\n");
    }
    else
    {
        printf("Test end.\n");
    }
    
    return error;
}


int test_square_solver()
{
    int error = 0;
    FILE *file = fopen("tests/tests/square_solver.txt", "r");
    if (file == NULL)
    {
        fprintf(stderr, "file not found.\n");
        exit(1);
    }
    int test_id = 0;
    while (1)
    {
        test_id++;
        struct coefficients_t coeff = {};
        enum solution_result_codes result = RESULT_0_SOLUTIONS;
        double roots[2] = {};
        enum solution_result_codes real_result = RESULT_0_SOLUTIONS;
        double real_roots[2] = {};

        /* read from file */
        int int_result = 0;
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

        if (real_result != result)
        {
            printf("ERROR: result != real_result : at test square %d.\n", test_id);
            error = 1;
            continue;
        }
        
        switch (result)
        {
            case RESULT_1_SOLUTIONS:
                if (!f_compare_eq(real_roots[0], roots[0]))
                {
                    printf("ERROR: root is wrong : at test square %d.\n", test_id);
                    error = 1;
                }
                break;
            case RESULT_2_SOLUTIONS:
                if (!((f_compare_eq(real_roots[0], roots[0]) && f_compare_eq(real_roots[1], roots[1])) || 
                           (f_compare_eq(real_roots[0], roots[1]) && f_compare_eq(real_roots[1], roots[0]))))
               {            
                    printf("ERROR: roots is wrong : at test square %d.\n", test_id);
                    error = 1;
               }
                break;
            case RESULT_0_SOLUTIONS:
            case RESULT_INFINITE_SOLUTIONS:
            case RESULT_ERROR_EQUATION:
            default:
                break;
        }
    }
    fclose(file);

    return error;
}


int test_linear_solver()
{
    int error = 0;
    FILE *file = fopen("tests/tests/linear_solver.txt", "r");
    if (file == NULL)
    {
        fprintf(stderr, "file not found.\n");
        exit(1);
    }
    int test_id = 0;
    while (1)
    {
        test_id++;
        struct coefficients_t coeff = {};
        enum solution_result_codes result = RESULT_0_SOLUTIONS;
        double roots[2] = {};
        enum solution_result_codes real_result = RESULT_0_SOLUTIONS;
        double real_root = 0.0;

        /* read from file */
        int int_result = 0;
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

        if (real_result != result)
        {
            printf("ERROR: result != real_result : at test linear %d.\n", test_id);
            error = 1;
            continue;
        }
        
        assert(real_result == result);
        
        switch (result)
        {
            case RESULT_1_SOLUTIONS:
                if (!f_compare_eq(real_root, roots[0]))
                {
                    printf("ERROR: root is wrong : at test linear %d.\n", test_id);
                    error = 1;
                }
                break;
            case RESULT_2_SOLUTIONS:
            case RESULT_0_SOLUTIONS:
            case RESULT_INFINITE_SOLUTIONS:
            case RESULT_ERROR_EQUATION:
            default:
                break;
        }
    }
    fclose(file);
    return error;
}
