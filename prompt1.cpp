#include "common.h"
#include "prompt1.h"
#include "read_double.h"


#define CHECK_RETURN_VALUE(result_code) \
    do { \
        if (res == READ_COEFFICIENTS_EOF) \
        { \
            return READ_COEFFICIENTS_EOF; \
        } \
        if (res != 0) \
        { \
            return 1; \
        }\
    } while (0)


/* v1 : copy */

int read_coefficients_copy(struct coefficients_t *coeff)
{
    int res = 0;

    const char * const format_string = "Enter coefficient at x^%d [%s] > ";
    
    res = read_double(&coeff->c, format_string, 2, "c");
    CHECK_RETURN_VALUE(res);
    
    res = read_double(&coeff->b, format_string, 1, "b");
    CHECK_RETURN_VALUE(res);
    
    res = read_double(&coeff->a, format_string, 0, "a");
    CHECK_RETURN_VALUE(res);

    return 0;

}
