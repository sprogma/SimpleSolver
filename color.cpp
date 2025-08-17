#include "common.h"
#include "color.h"


#ifdef _WIN32

    #include "io.h"

    int is_out_terminal()
    {
        return _isatty(1);
    }

    int is_in_terminal()
    {
        return _isatty(0);
    }
#else
    #include "unistd.h"

    int is_out_terminal()
    {
        return isatty(1);
    }

    int is_in_terminal()
    {
        return isatty(0);
    }

#endif
