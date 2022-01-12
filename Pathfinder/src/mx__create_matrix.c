#include "pathfinder.h"

int i_numb_of_isl(temp_finder *find, char *island) {
    for (int i = 0; i < find->num_islands; i++) {
        if (mx_strcmp(island, find->unique_isl[i]) == 0) {
             return i;
        }
    }
    return 0;
}

void mx_create_matrix(temp_finder *find) {
    int i;
    int j;

    find->arr = (int **)malloc(sizeof(int *) * find->num_islands);
    find->primary = (int **)malloc(sizeof(int *) * find->num_islands);
    for (i = 0; i < find->num_islands; i++) {
        find->arr[i] = (int *)malloc(sizeof(int *) * find->num_islands);
        find->primary[i] = (int *)malloc(sizeof(int *) * find->num_islands);
        for (j = 0; j < find->num_islands; j++) {
            find->arr[i][j] = i != j ? INT_MAX : 0;
        }
    }
    for (int index = 1; index < find->words ; index += 3) {
        i = i_numb_of_isl(find, find->islands[index]);
        j = i_numb_of_isl(find, find->islands[index + 1]);
        find->arr[i][j] = mx_atoi(find->islands[index + 2]);
        find->arr[j][i] = mx_atoi(find->islands[index + 2]);
    }
    mx_del_strarr(&find->islands);
}


