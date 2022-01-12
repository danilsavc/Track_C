#ifndef HEADER_H
#define HEADER_H

#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/xattr.h>
#include <sys/acl.h>
#include <limits.h>
#include "libmx.h"
#include <errno.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

typedef struct flags_list {
    bool flag_A; //+
    bool flag_B;
    bool flag_C;
    bool flag_F;
    bool flag_G;
    bool flag_H;
    bool flag_L;
    bool flag_O;
    bool flag_P;
    bool flag_R;
    bool flag_S;
    bool flag_T;
    bool flag_U;
    bool flag_W;
    bool flag_a; //+
    bool flag_b;
    bool flag_c;
    bool flag_d;
    bool flag_e;
    bool flag_f;
    bool flag_g;
    bool flag_h;
    bool flag_i;
    bool flag_k;
    bool flag_l; //+
    bool flag_m;
    bool flag_n;
    bool flag_o;
    bool flag_p;
    bool flag_q;
    bool flag_r;
    bool flag_s;
    bool flag_t;
    bool flag_u;
    bool flag_w;
    bool flag_x;
    bool flag_1;
}                   t_flags;

typedef struct file_list {
    int index;
    char *fname;
    char *full_fname;
    int len_name;
    struct stat info;
    struct file_list *next;
}                    f_list;

bool is_dir(char *directory);
f_list *Create_flist(char *name_files, int index, int length, char *full_name);
void Add_elem_end_flist(char *name_files, int index, int length, f_list *head, char *full_name);
f_list *Remove_all_flist(f_list *head);
f_list *ParsingF(char *directory);
int get_count_files(f_list *flist);
int get_max_len_words(int argc, f_list *flist);
int max_num_st_link(f_list *flist);
int max_num_st_gid(f_list *flist);
int max_num_st_size(f_list *flist);
char *converter_mode(mode_t perm, char *name);
int get_all_sym(int argc, f_list *flist, int count_files);
void print_result(int argc, f_list *flist, t_flags *flags, int cat_indicator, bool fl, int file_in);
t_flags *Check_flags(int argc, char *directory, int n_flags);
int get_total(f_list *flist);
int get_column(int term_width, int count_tab);
int get_row(int count_col, int count_files);
void get_space_col(int max_length, int len_fname);
char *find_files_index(int index, f_list *flist);
int get_max_st_mode(f_list *flist);
int Check_argv_dir(int argc, char *argv[]);
void get_tab_space(int count_tab, int len);
void get_nspaces(int max_length, int len_fname, int n_space);
bool check_on_flags(t_flags *flags);
char **fill_arr(char **arr_dir, int argc, char *argv[], int count_dir);
char **sort_arr(char **arr_dir, int count_dir);
int Check_argv_files(int argc, char *argv[]);
char **fill_arr_files(char **arr_files, char **arr_dir, int count_dir);
char **sort_arr_files(char **arr_files, int count_files);
void get_tab_space1(int count_tab, int len_name);
int get_max_namefiles(int argc, char **arr_files, int count_files);
char **fill_arr1(char **arr_dir1, int count_dir, char **arr_dir);
int get_all_sym_col(f_list *flist);
int get_num_space_col(int max_length, int len_fname);
int check_err(char *directory);
int check_error_files(int argc, char *argv[]);
int check_files_norm(int argc, char *argv[]);
f_list *parsing_file(char **arr_files, int count_files);
int get_max_uname(f_list *flist);
int get_max_gid(f_list *flist);

#endif

