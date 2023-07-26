#include "grep.h"

int main(int argc, char **argv) {
  t_flag flag = {0};
  char current_flag = 0;
  char *flags_available = "eivcln";
  char *template = "\0";
  int current_file_index = 0;
  bool multifile = false;

  while ((current_flag = getopt(argc, argv, flags_available)) != -1) {
    flag = parse_flag(flag, current_flag);
  }

  template = argv[optind];
  current_file_index = optind + 1;
  multifile = (argc - (current_file_index) > 1) ? true : false;

  while (current_file_index < argc) {
    FILE *opened_file = fopen(argv[current_file_index], "rt");
    if (opened_file) {
      print_grep_strings(opened_file, argv[current_file_index], multifile,
                         flag, template);
      fclose(opened_file);
      current_file_index++;
    }
  }

  return 0;
}

t_flag parse_flag(t_flag _flag, char _current_flag) {
  switch (_current_flag) {
    case 'e':
      _flag.e = true;
      break;
    case 'i':
      _flag.i = true;
      break;
    case 'v':
      _flag.v = true;
      break;
    case 'c':
      _flag.c = true;
      break;
    case 'l':
      _flag.l = true;
      break;
    case 'n':
      _flag.n = true;
      break;
    default:
      break;
  }

  return _flag;
}

void print_grep_strings(FILE *_file, char *_file_name, bool _multifile,
                        t_flag _flag, char *_template) {
  char file_string[2048];
  int string_number = 0;
  int output_string_number = 0;
  bool string_printed = false;
  bool no_l_c_flags = !_flag.l && !_flag.c;
  bool flag_n = _flag.n;
  regex_t reg_ex;
  int reg_flag = (_flag.i) ? REG_ICASE : REG_EXTENDED;
  bool reg_res = regcomp(&reg_ex, _template, reg_flag);

  while (fgets(file_string, 2048, _file) != NULL) {
    string_printed = false;
    string_number++;
    reg_res = (regexec(&reg_ex, file_string, 0, NULL, 0) == 0) ? true : false;
    if (_flag.v) reg_res = !reg_res;

    if (reg_res) {
      if (no_l_c_flags) {
        if (_multifile) printf("%s:", _file_name);
        if (flag_n) printf("%d:", string_number);
        printf("%s", file_string);
        string_printed = true;
      } else {
        output_string_number++;
      }
    }
  }

  if (string_printed) {
    printf("\n");
  }

  if (_flag.c) {
    if (output_string_number > 0 && _flag.l)
      output_string_number = 1;
    if (_multifile)
      printf("%s:%d\n", _file_name, output_string_number);
    else
      printf("%d\n", output_string_number);
  }

  if (_flag.l) {
    if (output_string_number > 0) printf("%s\n", _file_name);
  }

  regfree(&reg_ex);
}