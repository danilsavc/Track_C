#include "pathfinder.h"

void mx_algoritmh_floyda(temp_finder *find) {
    int sum;

    for (int i = 0; i < find->num_islands; i++) {
        for (int j = i; j < find->num_islands; j++) {
            find->primary[i][j] = find->arr[i][j];
            find->primary[j][i] = find->arr[j][i];
        }
    }
    for (int k = 0; k < find->num_islands; k++) {
        for (int i = 0; i < find->num_islands; i++) {
            for (int j = i + 1; j < find->num_islands; j++) {
                sum = find->arr[i][k] + find->arr[k][j];
                find->arr[k][j] != INT_MAX && find->arr[i][k] != INT_MAX && sum < find->arr[i][j] ? find->arr[i][j] = sum, find->arr[j][i] = sum : i;
            }
        }
    }
}
