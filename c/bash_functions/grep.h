#include <regex.h>

#include "common.h"

void print_grep_strings(FILE *_file, char *_file_name, bool _multifile,
                        char *_flag_string, char *_template);
void concatenate_flag_string(char *_flag_string, char _flag);