#include "header.h"

char *converter_mode(mode_t perm, char *name) {
    char *mode_convert_num = malloc(sizeof(char) * 11 + 1);
    mode_convert_num[0] = (perm & S_IFDIR) ? 'd' : '-';
    mode_convert_num[1] = (perm & S_IRUSR) ? 'r' : '-';
    mode_convert_num[2] = (perm & S_IWUSR) ? 'w' : '-';
    mode_convert_num[3] = (perm & S_IXUSR) ? 'x' : '-';
    mode_convert_num[4] = (perm & S_IRGRP) ? 'r' : '-';
    mode_convert_num[5] = (perm & S_IWGRP) ? 'w' : '-';
    mode_convert_num[6] = (perm & S_IXGRP) ? 'x' : '-';
    mode_convert_num[7] = (perm & S_IROTH) ? 'r' : '-';
    mode_convert_num[8] = (perm & S_IWOTH) ? 'w' : '-';
    mode_convert_num[9] = (perm & S_IXOTH) ? 'x' : '-';
    if (listxattr(name, NULL, 0, XATTR_NOFOLLOW) > 1) {
        mode_convert_num[10] = '@';
    }
    else if (acl_get_file(name , ACL_TYPE_EXTENDED)) {
        mode_convert_num[10] = '+';
    }
    else {
        mode_convert_num[10] = ' ';
    }
    if(S_ISLNK(perm)) {
        mode_convert_num[0] = 'l';
    }
    if (perm & S_ISVTX) {
        mode_convert_num[9] = 't';
    }
    mode_convert_num[11] = '\0';
    return mode_convert_num;
}

char *find_files_index(int index, f_list *flist) {
    f_list *head = flist;
    char *res;
    while (flist != NULL) {
        if (index == flist->index) {
            res = flist->fname;
            flist = head;
            return res;
        }
        flist = flist->next;
    }
    flist = head;
    return NULL;
} 

void print_result(int argc, f_list *flist, t_flags *flags, int cat_indicator, bool fl, int file_in) {
    f_list *head_flist = flist;
    struct winsize tsize;
    struct passwd inf_PC;
    struct group gr;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &tsize);
    int max_len_fname = get_max_len_words(argc, flist);
    int max_nlink = max_num_st_link(flist);
    int max_nsize = max_num_st_size(flist);
    int total = get_total(flist);
    int term_width = tsize.ws_col;
    int max_uname = get_max_uname(flist);
    int max_gid = get_max_gid(flist);
    
    int count_files = get_count_files(flist);
    int all_sym_files = get_all_sym(argc, flist, count_files);
    char *time_buff = NULL;
    char *time_buffer = NULL;
    int max_st_mode = get_max_st_mode(flist);
    int count_tab = 1;
    int i = 0;
    for (int i = 8; i <= max_len_fname; i += 8) {
        count_tab++;
    }
    int count_col = get_column(term_width, count_tab);
    int count_row = get_row(count_col, count_files);
    
    if (count_files > 0) {
        int count_hidden_file = 0;
        while (flist != NULL) {
            if (flist->fname[0] == '.') {
                count_hidden_file++;
            }
            flist = flist->next;
        }
        flist = head_flist;
        if (fl) {
            if (cat_indicator == 0 && !flags->flag_l) {
                while (flist != NULL) {
                    if (i != 0) {
                        mx_printstr("\n");
                    }
                    if (flist->fname[0] == '.') {
                        flist = flist->next;
                        continue;
                    }
                    mx_printstr(flist->fname);
                    flist = flist->next;
                    i++;
                }
                mx_printstr("\n");
                flist = head_flist;
            }
            else {
                if (flags->flag_l && file_in == 1) {
                    mx_printstr("total ");
                    mx_printint(total);
                    mx_printchar('\n');
                }
                while (flist != NULL) {
                    if (flags->flag_A && !flags->flag_a && !flags->flag_l) {
                        if ((flist->fname[0] == '.' && flist->fname[1] == '\0') || (flist->fname[0] == '.' && flist->fname[1] == '.')) {
                            flist = flist->next;
                            continue;
                        }
                    }
                    if (!flags->flag_a && !flags->flag_A && !flags->flag_l) {
                        if (flist->fname[0] == '.') {
                            flist = flist->next;
                            continue;
                        }
                    }
                    if (flags->flag_l) {
                        if (flags->flag_A && !flags->flag_a) {
                            if ((flist->fname[0] == '.' && flist->fname[1] == '\0') || (flist->fname[0] == '.' && flist->fname[1] == '.')) {
                                flist = flist->next;
                                continue;
                            }
                        }
                        if (!flags->flag_a && !flags->flag_A) {
                            if (flist->fname[0] == '.') {
                                flist = flist->next;
                                continue;
                            }
                        }
                        inf_PC = *getpwuid(flist->info.st_uid);
                        time_buff = 4 + ctime((time_t *)&flist->info.st_mtime);
                        if (time(NULL) - flist->info.st_mtime > 15811200) {
                            time_buffer = mx_strndup(time_buff, mx_strlen(time_buff) - 14);
                            time_buffer = mx_strjoin(time_buffer, mx_strndup(19 + ctime((time_t *)&flist->info.st_mtime), 5));
                        }
                        else {
                            time_buffer = mx_strndup(time_buff, mx_strlen(time_buff) - 9);
                        }
                        mx_printstr(converter_mode(flist->info.st_mode, flist->full_fname));
                        get_nspaces(max_st_mode, mx_strlen(converter_mode(flist->info.st_mode, flist->full_fname)), 1);
                        get_nspaces(mx_strlen(mx_itoa(max_nlink)), mx_strlen(mx_itoa(flist->info.st_nlink)), 0);
                        mx_printint(flist->info.st_nlink);
                        mx_printchar(' ');
                        mx_printstr(inf_PC.pw_name);
                        get_nspaces(max_uname, mx_strlen(inf_PC.pw_name), 2);
                        if (getgrgid(flist->info.st_gid) == NULL) {
                            mx_printint(flist->info.st_gid);
                            get_nspaces(max_gid, mx_strlen(mx_itoa(flist->info.st_gid)), 2);
                        }
                        else {
                            gr = *getgrgid(flist->info.st_gid);
                            mx_printstr(gr.gr_name);
                            get_nspaces(max_gid, mx_strlen(gr.gr_name), 2);
                        }
                        get_nspaces(max_nsize, mx_strlen(mx_itoa(flist->info.st_size)), 0);
                        mx_printint(flist->info.st_size);
                        mx_printchar(' ');
                        mx_printstr(time_buffer);
                        mx_printchar(' ');
                    }
                    mx_printstr(flist->fname);
                    if (!flags->flag_l) {
                        get_nspaces(max_len_fname, flist->len_name, 8);
                    }
                    else if (flags->flag_l) {
                        mx_printstr("\n");
                    }
                    flist = flist->next;
                }
            }
            
        }
        else {
            if (cat_indicator == 0) {
                while (flist != NULL) {
                    if (i != 0) {
                        mx_printstr("\n");
                    }
                    if (flist->fname[0] == '.') {
                        flist = flist->next;
                        continue;
                    }
                    mx_printstr(flist->fname);
                    flist = flist->next;
                    i++;
                }
                mx_printstr("\n");
                flist = head_flist;
            }
            else {
                if (all_sym_files >= term_width) {
                    for (int i = 0; i < count_row; i++) {
                        int k = count_hidden_file + 1;
                        for (int j = 1; j <= count_col; j++) {
                            if (count_row * j + i - count_row >= count_files) {
                                break;
                            }
                            mx_printstr(find_files_index(k + i, flist));
                            if (j < count_col) {
                                get_tab_space(count_tab, mx_strlen(find_files_index(k + i, flist)));
                            }
                            k += count_row;
                        }
                        mx_printstr("\n");
                    }
                    flist = head_flist;
                }
                else {
                    while (flist != NULL) {
                        if (flist->fname[0] == '.') {
                            flist = flist->next;
                            continue;
                        }
                        mx_printstr(flist->fname);
                        get_tab_space(count_tab, flist->len_name);
                        flist = flist->next;
                    }
                    mx_printstr("\n");
                    flist = head_flist;
                }
            }
        }
    }
    
}

