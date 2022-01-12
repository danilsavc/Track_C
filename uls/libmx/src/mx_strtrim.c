#include "libmx.h"

char *mx_strtrim(const char *str) {
    if (!str)
        return NULL;

    while (mx_isspace(*str))
        str++;

    int lens = mx_strlen(str);

    while (mx_isspace(str[lens - 1]))
        lens--;

    return mx_strndup(str, lens);
}

