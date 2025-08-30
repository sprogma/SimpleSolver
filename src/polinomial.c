#include "complex.h"
#include "math.h"
#include "solver.h"
#include "float_compare.h"


double coeff_get(const struct coefficients_t *x, double pos)
{
    double res = 0.0, curr = 1.0;
    for (size_t i = 0; i < x->size; ++i)
    {
        res += curr * x->data[i];
        curr *= pos;
    }
    return res;
}


int coeff_alloc(struct coefficients_t *x, size_t size)
{
    if (size > x->alloc)
    {
        size_t prev_size = x->alloc;
        if (!x->alloc)
        {
            x->alloc = 1;
        }
        while (size >= x->alloc)
        {
            x->alloc *= 2;
        }
        // TODO: 
        double *new_ptr = (double *)realloc(x->data, sizeof(*x->data) * x->alloc);
        if (new_ptr == NULL)
        {
            return 1;
        }
        x->data = new_ptr;
        memset(x->data + prev_size, 0, sizeof(*x->data) * (x->alloc - prev_size));
    }
    return 0;
}


int coeff_strip(struct coefficients_t *x)
{
    while (x->size > 1 && f_compare_eq(x->data[x->size - 1], 0.0))
    {
        x->size--;
    }
    return 0;
}


int coeff_add(struct coefficients_t *x, const struct coefficients_t *y)
{
    assert(x != NULL);
    assert(y != NULL);

    coeff_alloc(x, y->size);

    if (x->size < y->size)
    {
        x->size = y->size;
    }
    
    for (size_t i = 0; i < y->size; ++i)
    {
        x->data[i] += y->data[i];
    }

    coeff_strip(x);
    
    return 0;
}

int coeff_sub(struct coefficients_t *x, const struct coefficients_t *y)
{
    assert(x != NULL);
    assert(y != NULL);

    coeff_alloc(x, y->size);
    if (x->size < y->size)
    {
        x->size = y->size;
    }

    for (size_t i = 0; i < y->size; ++i)
    {
        x->data[i] -= y->data[i];
    }

    coeff_strip(x);
        
    return 0;
}

static size_t rev(size_t num, size_t lg_n) 
{
    size_t res = 0;
    for (size_t i = 0; i < lg_n; ++i)
    {
        if (num & (1ull << i))
        {
            res |= 1ull << (lg_n - 1ull - i);
        }
    }
        
    return res;
}

static void fft_calc(double complex *array, size_t size, int invert)
{
    size_t lg_n = 0;
    while ((1ull << lg_n) < size) 
    {
        ++lg_n;
    }
 
    for (size_t i = 0; i < size; ++i)
    {
        if (i < rev(i, lg_n))
        {
            double complex x = array[i];
            array[i] = array[rev(i, lg_n)];
            array[rev(i, lg_n)] = x;
        }
    }
 
    for (size_t len = 2; len <= size; len <<= 1) 
    {
        double ang = 2.0 * M_PI / (double)len * (invert ? -1 : 1);
        double complex wlen = cos(ang) + sin(ang) * I;
        for (size_t i = 0; i < size; i += len) 
        {
            double complex w = 1.0;
            for (size_t j = 0; j + j < len; ++j) 
            {
                double complex u = array[i + j], v = array[i + j + len / 2] * w;
                array[i + j] = u + v;
                array[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }
    
    if (invert)
    {
        double inv_n = 1.0 / (double)size;
        for (size_t i = 0; i < size; ++i)
        {
            array[i] *= inv_n;
        }
    }
}

int coeff_mul(struct coefficients_t *x, const struct coefficients_t *y)
{
    assert(x != NULL);
    assert(y != NULL);

    size_t total_size = 1ull;
    while (total_size <= x->size + y->size)
    {
        total_size <<= 1ull;
    }

    double complex *xdata = calloc(1, sizeof(*xdata) * total_size);
    double complex *ydata = calloc(1, sizeof(*ydata) * total_size);
    
    for (size_t i = 0; i < x->size; ++i)
    {
        xdata[i] = x->data[i];
    }
    for (size_t i = 0; i < y->size; ++i)
    {
        ydata[i] = y->data[i];
    }

    fft_calc(xdata, total_size, 0);
    fft_calc(ydata, total_size, 0);

    for (size_t i = 0; i < total_size; ++i)
    {
        xdata[i] *= ydata[i];
    }

    fft_calc(xdata, total_size, 1);

    coeff_alloc(x, x->size + y->size + 2);
    x->size = x->size + y->size + 2;
    for (size_t i = 0; i < x->size; ++i)
    {
        x->data[i] = creal(xdata[i]);
    }

    coeff_strip(x);

    return 0;
}

int coeff_div(struct coefficients_t *x, const struct coefficients_t *y)
{
    assert(x != NULL);
    assert(y != NULL);

    if (y->size == 0 || f_compare_eq(y->data[0], 0.0))
    {
        fprintf(stderr, "Disision on zero.\n");
        return 1;
    }

    for (size_t i = 1; i < y->size; ++i)
    {
        if (!f_compare_eq(y->data[i], 0.0))
        {
            fprintf(stderr, "Division on not scalar equation.\n");
            return 1;
        }
    }

    for (size_t i = 0; i < x->size; ++i)
    {
        x->data[i] /= y->data[0];
    }

    coeff_strip(x);
    
    return 0;
}
