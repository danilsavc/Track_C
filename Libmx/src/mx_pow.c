#include "libmx.h"

double mx_pow(double n, unsigned int pow) {
    double temp = 1;
    if (pow == 0) {
        return temp;
    }
    else if (pow > 0) {
        for (unsigned int i = 0; i < pow; i++ ) {
            temp *= n;
        }
    }
    
    return temp;
}

