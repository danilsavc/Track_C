#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "libmx.h"

#define INT_MAX 2147483647

typedef struct s_output {
    int length;
    int *route;

}              temp_output;

typedef struct s_finder {
    int **arr;
    int **primary;
    char *string;
    char **islands;
    char **unique_isl;
    int num_islands;
    int words;
}              temp_finder;


void mx_check_err(int argc, char *argv[], temp_finder *find);
void mx_invalid_islands(temp_finder *find);
void mx_create_matrix(temp_finder *find);
void mx_algoritmh_floyda(temp_finder *find);
void mx_output(temp_finder *find);

#endif

