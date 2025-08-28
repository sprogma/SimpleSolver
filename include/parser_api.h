#ifndef PARSE_MATH
#define PARSE_MATH

#include "inttypes.h"

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef NO_PARSE_DLL_LIB
    #ifdef PARSE_DLL_BUILD
        #define EXPORT __declspec(dllexport)
    #else
        #define EXPORT __declspec(dllimport)
    #endif
#else
    #define EXPORT
#endif
    

enum node_type_t
{
    NODE_TYPE_NULL,
    NODE_TYPE_ADDSUB,
    NODE_TYPE_OP_ADD,
    NODE_TYPE_OP_SUB,
    NODE_TYPE_MULDIV,
    NODE_TYPE_OP_MUL,
    NODE_TYPE_OP_DIV,
    NODE_TYPE_BRACES,
    NODE_TYPE_FLOAT,
    NODE_TYPE_IDENTIFER,
};


struct node_t
{
    enum node_type_t type;
    size_t childs_length;
    size_t childs_alloc;
    struct node_t **childs;
    const char *start;
    const char * end;
};


struct parse_result_t
{
    const char *rest;
    struct node_t *node;
};


EXPORT struct parse_result_t parse_all(const char *code);

#ifdef __cplusplus
}
#endif


#endif
