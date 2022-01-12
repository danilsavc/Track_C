#include "header.h"

f_list *Create_flist(char *name_files, int index, int length, char *full_name) {
    f_list *tmp = (f_list*)malloc(sizeof(f_list));
    struct stat inf;
    tmp->fname = name_files;
    tmp->index = index;
    tmp->len_name = length;
    lstat(full_name, &inf);
    tmp->full_fname = full_name;
    tmp->info = inf;
    tmp->next = NULL;
    return(tmp);
}

void Add_elem_end_flist(char *name_files, int index, int length, f_list *head, char *full_name) {
    f_list *tmp = (f_list*)malloc(sizeof(f_list));
    struct stat inf;
    tmp->fname = name_files;
    tmp->index = index;
    tmp->len_name = length;
    lstat(full_name, &inf);
    tmp->full_fname = full_name;
    tmp->info = inf;
    tmp->next = NULL;
    f_list *p = head;
    
    while (p->next != NULL)
        p = p->next;
    p->next = tmp;
}

f_list *Remove_all_flist(f_list *head) {
    while (head != NULL) {
        f_list *p = head;
        head = head->next;
        free(p);
    }
    return NULL;
}

