#include "pathfinder.h"

void mx_print_err_isl() {
    mx_printerr("error: invalid number of islands\n");
    exit(1);
}

void mx_print_errline(int line) {
    char *buf = mx_itoa(line);
    mx_printerr("error: line ");
    mx_printerr(buf); 
    mx_printerr(" is not valid\n");
    exit(2);
}

void mx_error_empty_file(char *argv[], temp_finder *find) {
    int fd = open(argv[1], O_RDONLY);
    char *buf = mx_strnew(1);
    int reading = read(fd, buf, 1);

    if (reading == 0) {
        mx_printerr("error: file ");
        mx_printerr(argv[1]);
        mx_printerr(" is empty\n");
        free(find);
        exit(3);
        close(fd);
    }
    mx_strdel(&buf);
    find->string = mx_file_to_str(argv[1]);
}

void mx_invalid_argc_or_file(int argc, char *argv[], temp_finder *find) {
    int fd = open(argv[1], O_RDONLY);

    if (argc != 2) {
        mx_printerr("usage: ./findfinder [filename]\n");
        exit(4);
    }

    if (fd < 0) {
        mx_printerr("error: file ");
        mx_printerr(argv[1]);
        mx_printerr(" does not exist\n");
        free(find);
        exit(5);
    }
    close(fd);
}

void count_islands(temp_finder *find) {
    int counter = 1;

    find->unique_isl = (char **)malloc(sizeof(char *) * find->words);
    find->unique_isl[0] = mx_strdup(find->islands[1]);
    for (int i = 1; i < find->words; i++) {
        if (mx_isdigit(find->islands[i][0])) {
            continue;
        } 
        for (int j = 0; j < counter; j++) {
            if (!mx_strcmp(find->unique_isl[j], find->islands[i])) {
                break;
            } 
            if (j == counter - 1) {
                find->unique_isl[counter++] = mx_strdup(find->islands[i]);
            }
        }
    }
    if (counter != find->num_islands) {
        mx_print_err_isl();
    }
}

void duplicate_islands(temp_finder *find) {
    int line = 2;
    
    for (int i = 1; i < find->words; i +=3) {
        if (!mx_strcmp(find->islands[i + 1], find->islands[i])) {
            mx_print_errline(line);
        }
        line++;
    }
}

void duplicate_bridges(temp_finder *find) {
    for (int i = 1; i < find->words; i +=3) {
        for (int j = i + 3; j < find->words; j+=3) {
            if (!mx_strcmp(find->islands[i], find->islands[j]) || !mx_strcmp(find->islands[i], find->islands[j + 1])) {
                if (!mx_strcmp(find->islands[i + 1], find->islands[j + 1]) || !mx_strcmp(find->islands[i + 1], find->islands[j])) {
                mx_printerr("error: duplicate bridges\n");
                exit(6);
                }
            }
        }
    }
}

void sum_bridges(temp_finder *find) {
    long sum = 0;

    for (int i = 1; i < find->words; i++) {
        if (mx_isdigit(find->islands[i][0])) {
            sum += mx_atoi(find->islands[i]);
        }
        if (sum > INT_MAX) {
            mx_printerr("error: sum of bridges lengths is too big\n");
            exit(7);
        }
    }
}

void mx_invalid_islands(temp_finder *find) {
    char *buffer = mx_strdup(find->string);

    find->num_islands = mx_atoi(buffer);
    if (find->num_islands < 2) {
        mx_print_err_isl();
    }
        
    for (int i = 0; buffer[i] != '\0'; i++) {
        buffer[i] == ',' || buffer[i] == '\n' ? (buffer[i] = '-') : buffer[i];
    } 
    find->words = mx_count_words(buffer,'-');
    find->islands = mx_strsplit(buffer,'-');
    count_islands(find);
    duplicate_islands(find);
    duplicate_bridges(find);
    sum_bridges(find);
    free(buffer);
    free(find->string);
}

void before_type(temp_finder *find, int line) {
    if (*find->string == '-' && !mx_isalpha(*(find->string - 1)) && !mx_isalpha(*(find->string + 1)))
        mx_print_errline(line);
        find->string++;
    for ( ; *find->string != ','; find->string++) {
        if (!mx_isalpha(*find->string)) {
            mx_print_errline(line);
        }
    }
        
            
    if (*find->string == ',' && !mx_isalpha(*(find->string - 1)) && !mx_isdigit(*(find->string + 1)))
        mx_print_errline(line);
        find->string++;
}

void mx_line_next_validation(temp_finder *find) {
    for (int line = 2; *find->string != '\0'; find->string++) {
        for ( ; *find->string != '-'; find->string++) {
            if (!mx_isalpha(*find->string)) {
                mx_print_errline(line);
            }     
        }
            
        before_type(find, line);
        for ( ; *find->string != '\n'; find->string++) {
            if (!mx_isdigit(*find->string) || mx_atol(find->string) > INT_MAX) {
                 mx_print_errline(line);
            }
        }
            line++;
    }
}

void mx_line1_validation(temp_finder *find) {
    for ( ; *find->string != '\n'; find->string++) {
        if (!mx_isdigit(*find->string)) {
            mx_print_errline(1);
        }
    }
    find->string++;
}



void mx_check_err(int argc, char *argv[], temp_finder *find) {
    char *buf;

    mx_invalid_argc_or_file(argc, argv, find);
    mx_error_empty_file(argv, find);
    buf = find->string;
    mx_line1_validation(find);
    mx_line_next_validation(find);
    find->string = buf;
    mx_invalid_islands(find);
}

