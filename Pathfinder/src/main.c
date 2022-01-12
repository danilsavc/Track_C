#include "pathfinder.h"

int main(int argc, char *argv[]) {
    temp_finder *find = (temp_finder *)malloc(sizeof(temp_finder));

    mx_check_err(argc, argv, find);
    mx_create_matrix(find);
    mx_algoritmh_floyda(find);
    mx_output(find);
    return 0;
}
