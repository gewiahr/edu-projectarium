#include <regex.h>

#include "common.h"

typedef struct flag_struct {
  bool e;
  bool i;
  bool v;
  bool c;
  bool l;
  bool n;
} t_flag;

t_flag parse_flag(t_flag _flag, char _current_flag);
void print_grep_strings(FILE *_file, char *_file_name, bool _multifile,
                        t_flag _flag, char *_template);