#include "help.h"
#include "stdio.h"


int print_help()
{
        char buff[16] = {};
    FILE *file = fopen("help.txt", "r");
    if (file == NULL)
    {
            fprintf(stderr, "No help file detected.\n");
        return 1;
    }
    while (!feof(file))
    {
            size_t count = fread(buff, 1, sizeof(buff), file);
        fwrite(buff, 1, count, stdout);
    }

    return 0;
}
