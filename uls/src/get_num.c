#include "header.h"

int get_count_files(f_list *flist) {
    int count_words = 0;
    while (flist != NULL) {
        if (flist->fname[0] == '.') {
            flist = flist->next;
            continue;
        }
        count_words++;
        flist = flist->next;
    }
    return count_words;
}

int get_max_len_words(int argc, f_list *flist) {
    int max_length = 0;
    if (argc > 1) {
        while (flist != NULL) {
            if (flist->len_name > max_length) {
                max_length = flist->len_name;
            }
            flist = flist->next;
        }
    }
    else {
        while (flist != NULL) {
            if (flist->fname[0] == '.') {
                flist = flist->next;
                continue;
            }
            if (flist->len_name > max_length) {
                max_length = flist->len_name;
            }
            flist = flist->next;
        }
    }
    return max_length;
}

int get_max_gid(f_list *flist) {
    int max_res = 0;
    int n = 0;
    struct group gr;
    while (flist != NULL) {
        n = 0;
        if (getgrgid(flist->info.st_gid) == NULL) {
            n = mx_strlen(mx_itoa(flist->info.st_gid));
        }
        else {
            gr = *getgrgid(flist->info.st_gid);
            n = mx_strlen(gr.gr_name);
        }
        if (n > max_res) {
            max_res = n;
        }
        flist = flist->next;
    }

    return max_res;
}

int get_max_uname(f_list *flist) {
    int max_length = 0;
    struct passwd inf_PC;
    while (flist != NULL) {
        if (flist->fname[0] == '.') {
            flist = flist->next;
            continue;
        }
        inf_PC = *getpwuid(flist->info.st_uid);
        if (mx_strlen(inf_PC.pw_name) > max_length) {
            max_length = mx_strlen(inf_PC.pw_name);
        }
        flist = flist->next;
    }
    return max_length;
}

int max_num_st_link(f_list *flist) {
    f_list *head = flist;
    int max_nst_link = 0;
    while (flist != NULL) {
        if (flist->fname[0] == '.') {
            flist = flist->next;
            continue;
        }
        if (flist->info.st_nlink > max_nst_link) {
            max_nst_link = flist->info.st_nlink;
        }
        flist = flist->next;
    }
    flist = head;
    return max_nst_link;
}

int max_num_st_gid(f_list *flist) {
    f_list *head = flist;
    int max_nst_gid = 0;
    while (flist != NULL) {
        if (flist->fname[0] == '.') {
            flist = flist->next;
            continue;
        }
        if (flist->info.st_nlink > max_nst_gid) {
            max_nst_gid = flist->info.st_gid;
        }
        flist = flist->next;
    }
    flist = head;
    return max_nst_gid;
}

int max_num_st_size(f_list *flist) {
    f_list *head = flist;
    int max_nst_size = 0;
    while (flist != NULL) {
        if (flist->fname[0] == '.') {
            flist = flist->next;
            continue;
        }
        if (mx_strlen(mx_itoa(flist->info.st_size)) > max_nst_size) {
            max_nst_size = mx_strlen(mx_itoa(flist->info.st_size));
        }
        flist = flist->next;
    }
    flist = head;
    return max_nst_size;
}

int get_total(f_list *flist) {
    f_list *head = flist;
    int total = 0;
    while (flist != NULL) {
        if (flist->fname[0] == '.') {
            flist = flist->next;
            continue;
        }
        total += flist->info.st_blocks;
        flist = flist->next;
    }
    flist = head;
    return total;
}

int get_num_space(int max_length, int len_fname) {
    max_length += 8;
    int n = max_length - len_fname;
    return n;
}

int get_all_sym(int argc, f_list *flist, int count_files) {
    f_list *head = flist;
    int num = 0;
    int c_f = 0;
    int max_word = get_max_len_words(argc , flist);
    flist = head;
    while (flist != NULL) {
        if (flist->fname[0] == '.') {
            flist = flist->next;
            continue;
        }
        if (c_f == count_files) {
            num = num + flist->len_name;
        }
        else {
            num = num + flist->len_name + get_num_space(max_word, flist->len_name);
        }
        c_f++;
        flist = flist->next;
    }
    flist = head;
    return num;
}

int get_num_space_col(int max_length, int len_fname) {
    max_length += 3;
    int n = max_length - len_fname;
    return n;
}

int get_all_sym_col(f_list *flist) {
    f_list *head = flist;
    int res = 0;
    while (flist != NULL) {
        res = res + flist->len_name;
        flist = flist->next;
    }
    flist = head;
    return res;
}

int get_column(int term_width, int count_tab) {
    int res = term_width / (count_tab * 8);
    return res;
}

int get_row(int count_col, int count_files) {
    int count_row = 0;
    if (count_col != 0)
        count_row = count_files % count_col != 0 ? count_files/count_col + 1 : count_files/count_col;
    return count_row;
}



void get_space_col(int max_length, int len_fname) {
    max_length += 3;
    int n = max_length - len_fname;
    for (int i = 0; i < n; i++) {
        mx_printchar(' ');
    }
}

int get_max_st_mode(f_list *flist) {
    f_list *head = flist;
    int res = 0;
    while (flist != NULL) {
        if (mx_strlen(converter_mode(flist->info.st_mode, flist->fname)) > res) {
            res = mx_strlen(converter_mode(flist->info.st_mode, flist->fname));
        }
        flist = flist->next;
    }
    flist = head;
    return res;
}

void get_tab_space(int count_tab, int len) {
    for (int i = len; i < count_tab * 8; i += 8) {
        mx_printstr("\t");
    }
}

void get_tab_space1(int count_tab, int len_name) {
    for (int i = len_name; i < count_tab * 8; i += 8) {
        mx_printstr("\t");
    }
}

void get_nspaces(int max_length, int len_fname, int n_space) {
    int n = max_length - len_fname + n_space;
    for (int i = 0; i < n; i++) {
        mx_printchar(' ');
    }
}

int get_max_namefiles(int argc, char **arr_files, int count_files) {
    int max_length = 0;
    if (argc > 1 && count_files > 0) {
        for (int i = 0; i < count_files; i++) {
            if (mx_strlen(arr_files[i]) > max_length) {
                max_length = mx_strlen(arr_files[i]);
            }
        }
    }
    return max_length;
}

