#include "libmx.h"

char *mx_strndup(const char *s1, size_t n) {
    char *temp = NULL;
    size_t length = mx_strlen(s1);

    if (n < length) length = n;

    temp = mx_strnew(length);
    mx_strncpy(temp, s1, length);
    
    return temp;
}

