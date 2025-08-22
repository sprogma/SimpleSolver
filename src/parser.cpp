#include "common.h"
#include "cmdarg_parser.h"

#include "stdio.h"
#include "stdlib.h"
#include "stdarg.h"
#include "string.h"


int initializate_commandline_args(struct commandline_parser_t *parser, 
                                  struct commandline_flag_t *flags_layout, 
                                  int flags_layout_length,
                                  struct commandline_argument_t *arguments,
                                  int arguments_length)
{
    assert(parser);
    assert(flags_layout != NULL || !flags_layout_length);
    assert(arguments != NULL || !arguments_length);
    
    parser->flags = 0;

    parser->flags_layout_length = flags_layout_length;
    parser->arguments_length = arguments_length;

    parser->flags_layout = flags_layout;
    parser->arguments = arguments;

    for (int i = 0; i < parser->arguments_length; ++i)
    {
        parser->arguments[i].value.value_length = 0;
        parser->arguments[i].value.value_alloc = 1;
        parser->arguments[i].value.value = (const char **)
                                           calloc(sizeof(*parser->arguments[i].value.value), parser->arguments[i].value.value_alloc);
    }
    
    return 0;
}


static struct commandline_parser_entry_t *commandline_args_get_entry_obj(struct commandline_parser_t *parser, const char *key, 
                                                                         struct commandline_parser_entry_t *entries, 
                                                                         size_t offset, int entries_length)
{
    assert(parser != NULL);
    assert(entries != NULL);
    assert(key != NULL);
    
    for (int i = 0; i < entries_length; ++i)
    {
        for (int name_id = 0; name_id < entries->key_length; ++name_id)
        {
            if (!strcmp(entries->key[name_id], key))
            {
                return entries;
            }
        }
        
        /* move to next array value */
        entries = (struct commandline_parser_entry_t *)(((char *)entries) + offset);
    }
    return NULL;
}


static struct commandline_argument_t *commandline_args_get_argument_obj(struct commandline_parser_t *parser, const char *key)
{
    assert(parser != NULL);
    assert(key != NULL);

    return (struct commandline_argument_t *)
           commandline_args_get_entry_obj(parser, key, 
                                          (struct commandline_parser_entry_t *)parser->arguments, 
                                          sizeof(*parser->arguments), 
                                          parser->arguments_length);
}


static struct commandline_flag_t *commandline_args_get_flag_obj(struct commandline_parser_t *parser, const char *key)
{
    assert(parser != NULL);
    assert(key != NULL);

    return (struct commandline_flag_t *)
           commandline_args_get_entry_obj(parser, key, 
                                          (struct commandline_parser_entry_t *)parser->flags_layout, 
                                          sizeof(*parser->flags_layout), 
                                          parser->flags_layout_length);
}


static int commandline_args_increase_value(struct commandline_argument_t *argument, const char *value)
{
    assert(argument != NULL);
    assert(value != NULL);

    if (argument->value.value_alloc <= argument->value.value_length)
    {
        /* double size + add 1, if it was 0 */
        argument->value.value_alloc = 2 * argument->value.value_alloc + (!argument->value.value_alloc);

        const char **new_ptr = (const char **)realloc(argument->value.value, sizeof(*argument->value.value) * argument->value.value_alloc);
        if (new_ptr == NULL)
        {
            fprintf(stderr, "No more memory.\n");
            return 1;
        }
        argument->value.value = new_ptr;
    }

    argument->value.value[argument->value.value_length++] = value;
    
    return 0;
}


static void print_help_arg_printer(struct commandline_parser_t *parser, struct commandline_parser_entry_t *entries, size_t offset, int entries_length)
{
    for (int i = 0; i < entries_length; ++i)
    {
        switch (entries->type)
        {
            case COMMANDLINE_PARSER_FLAG:
                printf("Flag");
                break;
            case COMMANDLINE_PARSER_ARGUMENT:
                printf("Argument");
                break;
            default:
                printf("Unknown type");
                break;
        }
        for (int name_id = 0; name_id < entries->key_length; ++name_id)
        {
            printf(" %s", entries->key[name_id]);
        }
        printf(":\n");
        printf("    info: %s\n", entries->info);
        
        /* move to next array value */
        entries = (struct commandline_parser_entry_t *)(((char *)entries) + offset);
    }
}


static void print_help(struct commandline_parser_t *parser)
{
    assert(parser != NULL);

    printf("Help on %s\n", parser->title);
    printf("Usage:\n%s\n", parser->usage);

    print_help_arg_printer(parser, (struct commandline_parser_entry_t *)parser->arguments, 
                                   sizeof(*parser->arguments), parser->arguments_length);
    print_help_arg_printer(parser, (struct commandline_parser_entry_t *)parser->flags_layout, 
                                   sizeof(*parser->flags_layout), parser->flags_layout_length);
    
    exit(0);
}


int commandline_args_parse(struct commandline_parser_t *parser, int argc, const char **argv)
{
    assert(parser != NULL);
    assert(argv != NULL);

    for (int curr = 0; curr < argc; ++curr)
    {
        if (!strcmp(argv[curr], "--"))
        {
            break;
        }
        
        if (!strcmp(argv[curr], "--help"))
        {
            print_help(parser);
        }
    
        /* is flag */
        struct commandline_flag_t *flag = commandline_args_get_flag_obj(parser, argv[curr]);
        if (flag != NULL)
        {
            parser->flags |= flag->flag;
            continue;
        }

        /* is object? */
        struct commandline_argument_t *argument = commandline_args_get_argument_obj(parser, argv[curr]);
        if (argument != NULL)
        {
            curr++;
            int start = curr;
            
            /* read untill find next known flag/argument */

            while (curr < argc &&
                   commandline_args_get_flag_obj(parser, argv[curr]) == NULL && 
                   commandline_args_get_argument_obj(parser, argv[curr]) == NULL &&
                   strcmp(argv[curr], "--") != 0 &&
                   strcmp(argv[curr], "--help") != 0)
            {
                commandline_args_increase_value(argument, argv[curr]);
                curr++;
            }

            if (curr == start)
            {
                fprintf(stderr, "Error: %s is not flag, no content found.\n", argv[start - 1]);
            }

            /* need to parse this new flag, so decrease curr */
            curr--;
            continue;
        }

        fprintf(stderr, "Error: Unknown flag: %s\n", argv[curr]);
    }

    return 0;
}

int commandline_args_get_value(struct commandline_parser_t *parser, const char *key, struct commandline_argument_value_t *value)
{
    assert(parser != NULL);
    assert(key != NULL);

    struct commandline_argument_t *argument = commandline_args_get_argument_obj(parser, key);
    
    if (argument == NULL)
    {
        return 0;
    }
    
    *value = argument->value;
    
    return value->value_length > 0;
}

uint64_t commandline_args_get_flag(struct commandline_parser_t *parser, const char *key)
{
    assert(parser != NULL);
    assert(key != NULL);

    struct commandline_flag_t *flag = commandline_args_get_flag_obj(parser, key);
    if (flag == NULL)
    {
        return 0;
    } 
    return parser->flags & flag->flag;
}
