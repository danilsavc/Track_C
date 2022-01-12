#include <unistd.h>

void mx_printchar(char c) {
    char* chch = &c;
    write (1, chch, 1);
}

