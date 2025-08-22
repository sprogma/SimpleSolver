#ifndef SOLVER_COLOR
#define SOLVER_COLOR


#define COLOR_RED(string)    "\x1B[31m" string "\x1B[0m"
#define COLOR_GREEN(string)  "\x1B[32m" string "\x1B[0m"
#define COLOR_YELLOW(string) "\x1B[33m" string "\x1B[0m"


/* 
    returns boolean - is output / input stream a terminal
*/
int is_out_terminal();
int is_input_terminal();


#endif
