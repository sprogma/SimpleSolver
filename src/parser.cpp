#include "common.h"
#include "cmdarg_parser.h"

#include "stdio.h"
#include "stdlib.h"
#include "stdarg.h"
#include "string.h"


int initializate_commandline_args(struct commandline_parser_t *parser, 
                                  struct commandline_parser_entry_t *entries, 
                                  int entries_length)
{
    assert(parser);
    assert(entries != NULL || !entries_length);

    parser->entries_length = entries_length;

    parser->entries = entries;

    for (int i = 0; i < parser->entries_length; ++i)
    {
        parser->entries[i].set = 0;
    }
    
    return 0;
}


static struct commandline_parser_entry_t *commandline_args_get_entry_obj(struct commandline_parser_t *parser, const char *key)
{
    assert(parser != NULL);
    assert(key != NULL);
    
    for (int i = 0; i < parser->entries_length; ++i)
    {
        for (int name_id = 0; name_id < parser->entries[i].key_length; ++name_id)
        {
            if (!strcmp(parser->entries[i].key[name_id], key))
            {
                return parser->entries + i;
            }
        }
    }
    return NULL;
}


static void print_help(struct commandline_parser_t *parser)
{
    assert(parser != NULL);
    
    printf("Help on %s\n", parser->title);
    printf("Usage:\n%s\n", parser->usage);
    
    for (int i = 0; i < parser->entries_length; ++i)
    {
        switch (parser->entries[i].type)
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
        for (int name_id = 0; name_id < parser->entries[i].key_length; ++name_id)
        {
            printf(" %s", parser->entries[i].key[name_id]);
        }
        printf(":\n");
        printf("    info: %s\n", parser->entries[i].info);
    }
    
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

        /* is object? */
        struct commandline_parser_entry_t *entry = commandline_args_get_entry_obj(parser, argv[curr]);
        if (entry != NULL)
        {
            int start = curr;
            curr++;

            entry->value = entry->read_function(entry->value, &curr, argc, argv);
            entry->set = 1;

            curr--;

            assert(curr >= start);
            
            continue;
        }

        fprintf(stderr, "Error: Unknown flag: %s\n", argv[curr]);
    }

    return 0;
}

int commandline_args_get_value(struct commandline_parser_t *parser, const char *key, void **value)
{
    assert(parser != NULL);
    assert(key != NULL);

    struct commandline_parser_entry_t *entry = commandline_args_get_entry_obj(parser, key);
    
    if (entry == NULL)
    {
        return 0;
    }
    
    *value = entry->value;
    
    return entry->set;
}
