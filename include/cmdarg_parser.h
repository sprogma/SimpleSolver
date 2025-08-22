#ifndef CMDARG_PARSER
#define CMDARG_PARSER

#include "stdio.h"
#include "inttypes.h"

enum commandline_parser_entry_type_t
{
    COMMANDLINE_PARSER_FLAG,
    COMMANDLINE_PARSER_ARGUMENT,
};

struct commandline_parser_entry_t
{
    enum commandline_parser_entry_type_t type;
    const char *info;
    int key_length;
    const char **key;
};

struct commandline_argument_value_t
{
    int value_length;
    int value_alloc;
    const char **value;
};

struct commandline_argument_t
{
    struct commandline_parser_entry_t base;
    struct commandline_argument_value_t value;
};

struct commandline_flag_t
{
    struct commandline_parser_entry_t base;
    uint64_t flag;
};

struct commandline_parser_t
{
    /* help text fillers */
    const char *title;
    const char *usage;

    /* arguments */
    uint64_t flags;
    
    int flags_layout_length;
    int arguments_length;
    
    struct commandline_flag_t *flags_layout;
    struct commandline_argument_t *arguments;
};




/**
 * @brief This function creates commandline arguments parser object
 *
 * @param[out] args - structure to create
 * @param[in] layout of flags
 * @param[in] it's length
 * @param[in] layout of arguments
 * @param[in] it's length
 *
 * @note you can not give full argc/argv, but (argc - 1, argv + 1) to remove self file name.
 *
 * @return 0 if there was no errors.
 */
int initializate_commandline_args(struct commandline_parser_t *parser, 
                                  struct commandline_flag_t *flags_layout, 
                                  int flags_layout_length,
                                  struct commandline_argument_t *arguments,
                                  int arguments_length);


/**
 * @brief This function fills parser data from commandline arguments
 *
 * @param[in] args - structure to fill
 * @param[in] argc [as main arguments]
 * @param[in] argv [as main arguments]
 *
 * @return 0 if there was no errors.
 */
int commandline_args_parse(struct commandline_parser_t *parser, int argc, const char **argv);

/**
 * @brief This function gets value by key
 *
 * @param[in] args - structure where to find
 * @param[in] key to find
 * @param[out] place to write found value.
 *
 * @return 1 if key was specified, or 0 if there is no such key.
 */
int commandline_args_get_value(struct commandline_parser_t *parser, const char *key, struct commandline_argument_value_t *value);


/**
 * @brief This function gets flag by key
 *
 * @param[in] args - structure where to find
 * @param[in] key to find
 *
 * @return flag, or 0 if there wasn't such flag.
 */
uint64_t commandline_args_get_flag(struct commandline_parser_t *parser, const char *key);


#endif
