#include "header.h"

char **fill_arr(char **arr_dir, int argc, char *argv[], int count_dir) {
    char *buff;
    if (argc > 1) {
        for (int i = 0; i < count_dir; i++) {
            buff = NULL;
            if (argv[1][0] == '-') {
                buff = mx_strdup(argv[i + 2]);
            }
            else {
                buff = mx_strdup(argv[i + 1]);
            }
            arr_dir[i] = mx_strdup(buff);
        }
    }
    return arr_dir;
}

char **fill_arr1(char **arr_dir1, int count_dir, char **arr_dir) {
    int j = 0;
    for (int i = 0; i < count_dir; i++) {
        if (!is_dir(arr_dir[i])) {
            continue;
        }
        else {
            arr_dir1[j] = mx_strdup(arr_dir[i]);
            j++;
        }
    }
    return arr_dir1;
}

char **fill_arr_files(char **arr_files, char **arr_dir, int count_dir) {
    char *buff;
    int j = 0;
    for (int i = 0; i < count_dir; i++) {
        buff = NULL;
        if (!is_dir(arr_dir[i])) {
            arr_files[j] = mx_strdup(arr_dir[i]);
            j++;
        }
    }
    return arr_files;
}

char **sort_arr(char **arr_dir, int count_dir) {
    char *buff;
    for (int i = 0; i < count_dir; i++) {
        for (int j = 0; j < count_dir; j++) {
            if (mx_strcmp(arr_dir[i], arr_dir[j]) > 0) {
                buff = mx_strdup(arr_dir[i]);
                arr_dir[i] = mx_strdup(arr_dir[j]);
                arr_dir[j] = mx_strdup(buff);
            }
        }
    }
    for (int i = 0; i < count_dir/2; i++) {
        buff = mx_strdup(arr_dir[i]);
        arr_dir[i] = mx_strdup(arr_dir[count_dir - 1 - i]);
        arr_dir[count_dir - 1 - i] = mx_strdup(buff);
    }
    return arr_dir;
}

char **sort_arr_files(char **arr_files, int count_files) {
    char *buff;
    if (count_files > 1) {
        for (int i = 0; i < count_files; i++) {
            for (int j = 0; j < count_files; j++) {
                if (mx_strcmp(arr_files[i], arr_files[j]) > 0) {
                    buff = mx_strdup(arr_files[i]);
                    arr_files[i] = mx_strdup(arr_files[j]);
                    arr_files[j] = mx_strdup(buff);
                }
            }
        }
        for (int i = 0; i < count_files/2; i++) {
            buff = mx_strdup(arr_files[i]);
            arr_files[i] = mx_strdup(arr_files[count_files - 1 - i]);
            arr_files[count_files - 1 - i] = mx_strdup(buff);
        }
    }
    return arr_files;
}

