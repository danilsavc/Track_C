#include "header.h"

f_list *parsing_file(char **arr_files, int count_files) {
    f_list *tmp = NULL;
    int index = 0;
    for (int i = 0; i < count_files; i++) {
        if (check_err(arr_files[i]) == 0) {
            mx_printerr("uls: ");
            mx_printerr(arr_files[i]);
            mx_printerr(": No such file or directory\n");
            continue;
        }
        if (check_err(arr_files[i]) == 3) {
            mx_printerr("uls: ");
            mx_printerr(arr_files[i]);
            mx_printerr(": Permission denied\n");
            continue;
        }
        if (index == 0) {
            tmp = Create_flist(arr_files[i], i + 1, mx_strlen(arr_files[i]), arr_files[i]);
            index++;
            continue;
        }
        Add_elem_end_flist(arr_files[i], index + 1, mx_strlen(arr_files[i]), tmp, arr_files[i]);
        index++;
    }
    return(tmp);
}

f_list *ParsingF(char *directory) {
    f_list *tmp = NULL;
    int i = 0;
    DIR *d;
    struct dirent *dir;
    char *full_name = NULL;

    d = opendir(directory);
    if (d) {
        int count_files = 0;
        while((dir = readdir(d)) != NULL) {
            count_files++;
        }
        closedir(d);
        d = opendir(directory);
        i = 0;
        char **arr_files = (char**)malloc(sizeof(char*) * (count_files + 1));
        while((dir = readdir(d)) != NULL) {
            arr_files[i] = mx_strdup(dir->d_name);
            i++;
        }
        arr_files = sort_arr_files(arr_files, count_files);
        closedir(d);
        for (int i = 0; i < count_files; i++) {
            full_name = mx_strdup(directory);
            full_name = mx_strjoin(full_name, "/");
            full_name = mx_strjoin(full_name, arr_files[i]);
            if (i == 0) {
                tmp = Create_flist(arr_files[i], i + 1, mx_strlen(arr_files[i]), full_name);
                continue;
            }
            Add_elem_end_flist(arr_files[i], i + 1, mx_strlen(arr_files[i]), tmp, full_name);
        }
    }
    else if (!d) {
        if (errno == ENOENT) {
            mx_printerr("uls: ");
            mx_printerr(directory);
            mx_printerr(": No such file or directory\n");
            exit(0);
        }
        if (errno == EACCES) {
            mx_printerr("uls: ");
            mx_printerr(directory);
            mx_printerr(": Permission denied\n");
            exit(0);
        }
    }
    return(tmp);
}

