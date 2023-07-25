#include "common.h"

const int STRING_SIZE = 4096;

typedef struct flag_struct {
  bool b;
  bool E;
  bool n;
  bool s;
  bool T;
  bool v;
} t_flag;

t_flag parce_flag(t_flag _flag, char _current_flag);
void output_file(FILE *_file);
void output_modified_file(FILE *_file, t_flag _flag);
bool skip_repeated_empty_string(t_flag _flag, char _prev_symb, char _symb,
                                bool _two_EOS_appeared);