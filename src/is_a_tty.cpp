#include "common.h"
#include "is_a_tty.h"


#ifdef _WIN32

    #include "io.h"

    int is_output_terminal()
    {
        return _isatty(1);
    }

    int is_input_terminal()
    {
        return _isatty(0);
    }
#else
    #include "unistd.h"

    int is_output_terminal()
    {
        return isatty(1);
    }

    int is_input_terminal()
    {
        return isatty(0);
    }

#endif
