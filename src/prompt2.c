#include "common.h"
#include "prompt2.h"
#include "polinomial.h"
#include "read_double.h"


int read_coefficients(struct coefficients_t *coeff)
{
    assert(coeff != NULL);

    int power = 0, scanf_ret = 0;
    do
    {
        printf("Enter max power: ");
        scanf_ret = scanf("%d", &power);
        int c;
        while ((c = getchar()) && c != '\n' && c != EOF) {}
    }
    while (scanf_ret != 1 || power < 1);


    coeff_alloc(coeff, (size_t)power + 1ull);

    coeff->size = (size_t)power + 1;
    for (size_t i = 0; i < coeff->size; ++i)
    {
        int res = read_double(coeff->data + i, 
                              "Enter coefficient at x^%d > ", 
                              (int)i);
        if (res == READ_COEFFICIENTS_EOF) { return READ_COEFFICIENTS_EOF; }
        if (res != 0) { return 1; }
    }

    return 0;
}
