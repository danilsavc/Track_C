#include "libmx.h"

char *mx_strnew(const int size) {
    char *bufer = NULL;
    int i = 0;
    if (size < 0) {
        return NULL;
    } 
    bufer = (char *)malloc((size + 1) * sizeof(char));
    while (i < size) {
        bufer[i] = '\0';
        i++;
    }
    bufer[i] = '\0';
    return bufer;
}

