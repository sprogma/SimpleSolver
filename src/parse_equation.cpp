#include "stdio.h"
#include "errno.h"
#include "string.h"
#include "solver.h"
#include "float_compare.h"
#include "parser_api.h"


#define RETURN_IF_ERR(call) \
            do { int err = (call); if (err) { return err; } } while (0)


int coeff_add(struct coefficients_t *x, const struct coefficients_t *y);
int coeff_sub(struct coefficients_t *x, const struct coefficients_t *y);
int coeff_mul(struct coefficients_t *x, const struct coefficients_t *y);
int coeff_div(struct coefficients_t *x, const struct coefficients_t *y);


int evaluate_node(struct node_t *node, struct coefficients_t *coefficients);
int parse_equation(const char *equation, struct coefficients_t *coefficients);


int coeff_add(struct coefficients_t *x, const struct coefficients_t *y)
{
    assert(x != NULL);
    assert(y != NULL);
    x->a += y->a;
    x->b += y->b;
    x->c += y->c;
    return 0;
}

int coeff_sub(struct coefficients_t *x, const struct coefficients_t *y)
{
    assert(x != NULL);
    assert(y != NULL);
    x->a -= y->a;
    x->b -= y->b;
    x->c -= y->c;
    return 0;
}

int coeff_mul(struct coefficients_t *x, const struct coefficients_t *y)
{
    assert(x != NULL);
    assert(y != NULL);
    
    if (!f_compare_eq(x->a * y->a, 0.0) || 
        !f_compare_eq(x->a * y->b, 0.0) ||
        !f_compare_eq(x->b * y->a, 0.0))
    {
        fprintf(stderr, "Polinomial multiplication overflow. (may be appears x^3 or x^4)\n");
        return 1;
    }
    double a = x->a * y->c + x->b * y->b + x->c * y->a;
    double b = x->b * y->c + x->c * y->b;
    double c = x->c * y->c;
    x->a = a;
    x->b = b;
    x->c = c;
    return 0;
}

int coeff_div(struct coefficients_t *x, const struct coefficients_t *y)
{
    assert(x != NULL);
    assert(y != NULL);

    if (!f_compare_eq(y->a, 0.0) || 
        !f_compare_eq(y->b, 0.0))
    {
        fprintf(stderr, "Division on not scalar equation.\n");
        return 1;
    }

    x->a /= y->c;
    x->b /= y->c;
    x->c /= y->c;
    return 0;
}


int evaluate_node(struct node_t *node, struct coefficients_t *coefficients)
{   
    assert(node != NULL);
    assert(coefficients != NULL);
    
    memset(coefficients, 0, sizeof(*coefficients));
    
    switch (node->type)
    {
        case NODE_TYPE_NULL:
            fprintf(stderr, "not allowed: NULL identifer.\n");
            return 1;
        case NODE_TYPE_ADDSUB:
            {
                RETURN_IF_ERR(evaluate_node(node->childs[0], coefficients));
                for (size_t i = 1; i + 1 < node->childs_length; i += 2)
                {
                    struct coefficients_t child = {};
                    RETURN_IF_ERR(evaluate_node(node->childs[i + 1], &child));

                    #pragma GCC diagnostic push
                    #pragma GCC diagnostic ignored "-Wswitch-enum"
                    switch (node->childs[i]->type)
                    {
                        case NODE_TYPE_OP_ADD:
                            RETURN_IF_ERR(coeff_add(coefficients, &child));
                            break;
                        case NODE_TYPE_OP_SUB:
                            RETURN_IF_ERR(coeff_sub(coefficients, &child));
                            break;
                        default:
                            fprintf(stderr, "Unknown operation child in ADDSUB identifer : %d (%.*s)\n", node->childs[i]->type, (int)(node->childs[i]->end - node->childs[i]->start), node->childs[i]->start);
                            return 1;
                    }
                    #pragma GCC diagnostic pop
                }
                return 0;
            }
        case NODE_TYPE_OP_ADD:
            fprintf(stderr, "not allowed: ADD identifer.\n");
            return 1;
        case NODE_TYPE_OP_SUB:
            fprintf(stderr, "not allowed: SUB identifer.\n");
            return 1;
        case NODE_TYPE_MULDIV:
            {    
                RETURN_IF_ERR(evaluate_node(node->childs[0], coefficients));
                for (size_t i = 1; i < node->childs_length; i += 2)
                {
                    struct coefficients_t child = {};
                    RETURN_IF_ERR(evaluate_node(node->childs[i + 1], &child));
                    
                    #pragma GCC diagnostic push
                    #pragma GCC diagnostic ignored "-Wswitch-enum"
                    switch (node->childs[i]->type)
                    {
                        case NODE_TYPE_OP_MUL:
                            RETURN_IF_ERR(coeff_mul(coefficients, &child));
                            break;
                        case NODE_TYPE_OP_DIV:
                            RETURN_IF_ERR(coeff_div(coefficients, &child));
                            break;
                        default:
                            fprintf(stderr, "Unknown child in MULDIV identifer.\n");
                            return 1;
                    }
                    #pragma GCC diagnostic pop
                }
                return 0;
            }
        case NODE_TYPE_OP_MUL:
            fprintf(stderr, "not allowed: MUL identifer.\n");
            return 1;
        case NODE_TYPE_OP_DIV:
            fprintf(stderr, "not allowed: DIV identifer.\n");
            return 1;
        case NODE_TYPE_BRACES:
            if (node->childs_length > 1)
            {
                fprintf(stderr, "not allowed: BRACES node has more than 1 child.\n");
            }
            return evaluate_node(node->childs[0], coefficients);
        case NODE_TYPE_FLOAT:
            {
                char *end;
                double value = strtod(node->start, &end);
                if (end != node->end)
                {
                    if (errno == ERANGE)
                    {
                        fprintf(stderr, "not allowed: FLOAT identifer overflow, in (%.*s).\n", (int)(node->end - node->start), node->start);
                        return 1;
                    }
                    fprintf(stderr, "not allowed: FLOAT identifer is not float, have (%.*s).\n", (int)(node->end - node->start), node->start);
                    return 1;
                }
                coefficients->c = value;
                return 0;
            }
        case NODE_TYPE_IDENTIFER:
            coefficients->b = 1.0;
            if (strncmp(node->start, "x", node->end - node->start) != 0)
            {
                fprintf(stderr, "not allowed: IDENTIFER not 'x', have (%.*s).\n", (int)(node->end - node->start), node->start);
                return 1;
            }
            return 0;
        default:
            fprintf(stderr, "Unknown identifer %d.\n", (int)node->type);
            return 1;
    }
    return 0;
}


int parse_equation(const char *equation, struct coefficients_t *coefficients)
{
    assert(equation != NULL);
    assert(coefficients != NULL);
    struct parse_result_t result = parse_all(equation);

    if (result.rest == NULL)
    {
        fprintf(stderr, "Parsing error. [Syntax]\n");
        return 1;
    }

    memset(coefficients, 0, sizeof(*coefficients));
    int err = evaluate_node(result.node, coefficients);
    if (err != 0)
    {
        fprintf(stderr, "Calculation failed.\n");
        return 1;
    }

    return 0;
}

