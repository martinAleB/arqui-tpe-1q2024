//#include <nanoshell_functions.h>
#include <libasm.h>
#include <stdlib.h>

void changeFontSize() {
    syscall(8, NULL, NULL, NULL); //Syscall clear 
    syscall(10, NULL, NULL, NULL); //Syscall change_font_size
}

