#include "pathfinder.h"

void delete_arr(int **arr, temp_finder *find) {
    if (arr) {
        for (int i = 0; i < find->num_islands; i++) {
            free(arr[i]);
        }  
        free(arr);
    }
}

void mx_clean_memory(temp_finder *find) {
    mx_del_strarr(&find->unique_isl);
    delete_arr(find->arr, find);
    delete_arr(find->primary, find);
    free(find);
}

void printemp_output_distance(temp_finder *find, temp_output *run) {
    int sum = 0;
    
    mx_printstr("Distance: ");
    for (int i = 1; i < run->length; i++) {
        mx_printint(find->primary[run->route[i]][run->route[i + 1]]);
        sum += find->primary[run->route[i]][run->route[i + 1]];

        if (i < run->length - 1) {
            mx_printstr(" + ");
        }

        else if (i > 1) {
            mx_printstr(" = ");
            mx_printint(sum);
        }
    }
    mx_printstr("\n");
    mx_printstr("========================================\n");
}

void printemp_output_route(temp_finder *find, temp_output *run) {
    mx_printstr("========================================\n");
    mx_printstr("Path: ");
    mx_printstr(find->unique_isl[run->route[1]]);
    mx_printstr(" -> ");
    mx_printstr(find->unique_isl[run->route[0]]);
    mx_printstr("\n"); 
    mx_printstr("Route: ");
        for (int i = 1; i < run->length + 1;) {
            mx_printstr(find->unique_isl[run->route[i]]); 
            if (++i < run->length + 1) {
                mx_printstr(" -> ");
            }
        }
    mx_printstr("\n");
}

void shortest_route(temp_finder *find, temp_output *run) {
    int i = run->route[run->length];
    int j = run->route[0];

    for (int k = 0; k < find->num_islands; k++) {
        if (k != run->route[run->length]
            && (find->primary[i][k] == find->arr[i][j] - find->arr[k][j])) {
            run->length++;
            run->route[run->length] = k;
            shortest_route(find, run);
            run->length--;
        }
    }
    if (run->route[run->length] != run->route[0]) {
        return;
    }
        
    printemp_output_route(find, run);
    printemp_output_distance(find, run);
}

void mx_output(temp_finder *find) {
    temp_output *run = (temp_output *)malloc(sizeof(temp_output));

    run->route = (int *)malloc(sizeof(int) * (find->num_islands + 1));
    for (int i = 0; i < find->num_islands; i++) {
        for ( int j = i + 1; j < find->num_islands; j++) {
            run->length = 1;
            run->route[0] = j;
            run->route[1] = i;
            shortest_route(find, run);
        }
    }
    free(run->route);
    free(run);
    mx_clean_memory(find);
}


