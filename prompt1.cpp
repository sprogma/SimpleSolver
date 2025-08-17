#include "common.h"
#include "prompt1.h"
#include "read_double.h"

/* v1 : copy */

int read_coefficients_copy(struct coefficients_t *coeff)
{
    int res = 0;

    const char * const format_string = "Enter coefficient at x^%d [%s] > ";
    
    res = read_double(&coeff->c, format_string, 2, "c");
    if (res == READ_COEFFICIENTS_EOF) 
    { 
        return READ_COEFFICIENTS_EOF; 
    }
    if (res != 0) 
    { 
        return 1; 
    }
    
    res = read_double(&coeff->b, format_string, 1, "b");
    if (res == READ_COEFFICIENTS_EOF) 
    { 
        return READ_COEFFICIENTS_EOF; 
    }
    if (res != 0) 
    { 
        return 1; 
    }
    
    res = read_double(&coeff->a, format_string, 0, "a");
    if (res == READ_COEFFICIENTS_EOF) 
    { 
        return READ_COEFFICIENTS_EOF; 
    }
    if (res != 0) 
    { 
        return 1; 
    }

    return 0;

}
