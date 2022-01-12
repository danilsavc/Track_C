#include "header.h"

int main(int argc, char *argv[]) {
     struct winsize tsize;
     ioctl(STDOUT_FILENO, TIOCGWINSZ, &tsize);
     int cat_in = tsize.ws_col;
     int count_dir = Check_argv_dir(argc, argv);
     int count_files = Check_argv_files(argc, argv);
     int count_err_fl = check_error_files(argc, argv);

     char **arr_dir = (char**)malloc(sizeof(char*) * (count_dir + 1));
     char **arr_files = (char**)malloc(sizeof(char*) * (count_files + 1));
     char **arr_dir1 = (char**)malloc(sizeof(char*) * (count_dir - count_files + 1));
     
     arr_dir = fill_arr(arr_dir, argc, argv, count_dir);
     arr_dir = sort_arr(arr_dir, count_dir);
     arr_files = fill_arr_files(arr_files, arr_dir, count_dir);
     arr_files = sort_arr_files(arr_files, count_files);
     
     arr_dir1 = fill_arr1(arr_dir1, count_dir, arr_dir);
     
     int max_filesname = get_max_namefiles(argc, arr_files, count_files);
     int count_dir1 = count_dir - count_files;
     int count_tab = 1;
     for (int i = 8; i <= max_filesname; i += 8) {
          count_tab++;
     }
     int num_flags = 0;
     if (argc > 1) {
          num_flags = mx_strlen(argv[1]) - 1;
     }
     t_flags *flags = Check_flags(argc, argv[1], num_flags);
     bool fl = check_on_flags(flags);
     if (count_dir == 0 && count_files == 0) {
          f_list *flist = ParsingF(".");
          print_result(argc, flist, flags, cat_in, fl, 1);
     }
     else {
          if (count_files > 0) {
               if (flags->flag_l) {
                    f_list *flist_f = parsing_file(arr_files, count_files);
                    print_result(argc, flist_f, flags, cat_in, fl, 0);
                    if (count_dir1 > 0) {
                         mx_printchar('\n');
                    }
               }
               else {
                    int c_e = 0;
                    for (int i = 0; i < count_files; i++) {
                         if (cat_in == 0) {
                              if (check_err(arr_files[i]) == 0) {
                                   mx_printerr("uls: ");
                                   mx_printerr(arr_files[i]);
                                   mx_printerr(": No such file or directory\n");
                                   c_e++;
                              }
                              else if (check_err(arr_files[i]) == 3) {
                                   if (count_err_fl > 1) {
                                        mx_printstr(arr_files[i]);
                                        mx_printstr(": \n");
                                   }
                                   mx_printerr("uls: ");
                                   mx_printerr(arr_files[i]);
                                   mx_printerr(": Permission denied\n");
                                   if (count_err_fl > 1 && c_e < count_err_fl) {
                                        mx_printstr("\n");
                                   }
                                   c_e++;
                              }
                         }
                         else {
                              if (check_err(arr_files[i]) == 0) {
                                   mx_printerr("uls: ");
                                   mx_printerr(arr_files[i]);
                                   mx_printerr(": No such file or directory");
                                   c_e++;
                                   if (c_e <= count_err_fl && cat_in != 0) {
                                        mx_printchar('\n');
                                   }
                              }
                              else if (check_err(arr_files[i]) == 3) {
                                   if (count_err_fl > 1) {
                                        mx_printstr(arr_files[i]);
                                        mx_printstr(": \n");
                                   }
                                   mx_printerr("uls: ");
                                   mx_printerr(arr_files[i]);
                                   mx_printerr(": Permission denied");
                                   c_e++;
                                   if (c_e <= count_err_fl && cat_in != 0) {
                                        mx_printchar('\n');
                                   }
                                   if (c_e < count_err_fl) {
                                        mx_printchar('\n');
                                   }
                              }
                         }
                    }
                    int c_f = 0;
                    count_files = count_files - c_e;
                    if (count_files > 0) {
                         for (int i = 0; i < count_files; i++) {
                              if (check_err(arr_files[i]) == 0) {
                                   continue;
                              }
                              mx_printstr(arr_files[i]);
                              c_f++;
                              if (cat_in == 0) {
                                   mx_printchar('\n');
                              }
                              else {
                                   get_tab_space(count_tab, mx_strlen(arr_files[i]));
                              }
                         }
                    }
                    if ((c_f > 0 && cat_in != 0) || (count_dir1 > 0)) {
                         mx_printchar('\n');
                    }
                    /*if (count_dir1 > 0) {
                         mx_printchar('\n');
                    }*/
               }
          }
          for (int i = 0; i < count_dir1; i++) {
               if (count_dir1 > 1 ) {
                    mx_printstr(arr_dir1[i]);
                    mx_printstr(":\n");
               }
               else if (count_dir1 > 0 && count_files > 0) {
                    mx_printstr(arr_dir1[i]);
                    mx_printstr(":\n");
               }
               f_list *flist = ParsingF(arr_dir1[i]);
               print_result(argc, flist, flags, cat_in, fl, 1);
               if (i + 1 < count_dir1) {
                    mx_printchar('\n');
               }
          }
     }
     return 0;
}

