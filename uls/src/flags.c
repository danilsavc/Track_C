#include "header.h"

void mx_printerr1(const char *s) {
    write(STDERR_FILENO, s, 1);
}

t_flags *Check_flags(int argc, char *directory, int n_flags) {
    t_flags *flags = (t_flags *)malloc(sizeof(t_flags));
    flags->flag_A = false;
    flags->flag_a = false;
    flags->flag_l = false;
    if (argc > 1) {
        if (directory[0] == '-') {
            for (int i = 0; i < n_flags; i++) {
                if (directory[i + 1] == 'a') {
                    flags->flag_a = true;
                }
                else if (directory[i + 1] == 'A') {
                    flags->flag_A = true;
                }
                else if (directory[i + 1] == 'l') {
                    flags->flag_l = true;
                }
                else {
                    mx_printerr("uls: illegal option -- ");
                    mx_printerr1(&directory[i + 1]);
                    mx_printerr("\nusage: uls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]\n");
                    exit(0);
                }
            }
        }
    }
    return flags;
}

bool check_on_flags(t_flags *flags) {
    bool f = false;
    if (flags->flag_A || flags->flag_a || flags->flag_l) {
        f = true;
    }
    return f;
}

