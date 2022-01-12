#include "header.h"

bool is_dir(char *directory) {
    DIR *d;
    d = opendir(directory);
    if (!d) {
        return false;
    }
    else {
        return true;
    }
}

int check_err(char *directory) {
    DIR *d;
    d = opendir(directory);
    if (!d) {
        if (errno == ENOENT) {
            return 0;
        }
        else if (errno == EACCES) {
            return 3;
        }
        else {
            return 2;
        }
    }
    else {
        return 1;
    }
}

int Check_argv_dir(int argc, char *argv[]) {
    int count_dir = 0;
    if (argc > 1) {
        if (argv[1][0] != '-') {
            count_dir++;
        }
        for (int i = 2; i < argc; i++) {
            count_dir++;
        }
    }
    else {
        count_dir = 0;
    }
    return count_dir;
}

int Check_argv_files(int argc, char *argv[]) {
    int count_files = 0;
    if (argc > 1) {
        if (argv[1][0] != '-' && !is_dir(argv[1])) {
            count_files++;
        }
        for (int i = 2; i < argc; i++) {
            if (!is_dir(argv[i])) {
                count_files++;
            }
        }
    }
    return count_files;
}

int check_error_files(int argc, char *argv[]) {
    int count_err_files = 0;
    if (argc > 1) {
        if ((argv[1][0] != '-' && check_err(argv[1]) == 0) || (argv[1][0] != '-' && check_err(argv[1]) == 3)) {
            count_err_files++;
        }
        for (int i = 2; i < argc; i++) {
            if (check_err(argv[i]) == 0 || check_err(argv[i]) == 3) {
                count_err_files++;
            }
        }
    }
    return count_err_files;
}


int check_files_norm(int argc, char *argv[]) {
    int count_files_norm = 0;
    if (argc > 1) {
        if (argv[1][0] != '-' && check_err(argv[1]) == 2) {
            count_files_norm++;
        }
        for (int i = 2; i < argc; i++) {
            if (check_err(argv[1]) == 2) {
                count_files_norm++;
            }
        }
    }
    return count_files_norm;
}

