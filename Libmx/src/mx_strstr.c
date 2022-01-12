#include "libmx.h"

char *mx_strstr(const char *haystack, const char *needle) {
    int SizeX = mx_strlen(needle);      
    int SizeY = mx_strlen(haystack);

    for (int count = 0; count < SizeY; haystack++, count++) {
        char *temp = mx_strchr(haystack, haystack[0]);

        if(mx_strncmp(temp,needle,SizeX)==0)
            return (char*)haystack;
    }
    return NULL;
}

