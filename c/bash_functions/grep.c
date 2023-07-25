#include "grep.h"

int main(int argc, char **argv) {
  char flag = 0;
  char flag_string[7] = "\0";
  char *flags_available = "eivcln";
  char *template;

  while ((flag = getopt(argc, argv, flags_available)) != -1) {
    concatenate_flag_string(flag_string, flag);
  }

  template = argv[optind];
  int current_file_index = optind + 1;
  bool multifile = (argc - (current_file_index) > 1) ? true : false;
  while (current_file_index < argc) {
    FILE *opened_file = fopen(argv[current_file_index], "rt");
    if (opened_file) {
      print_grep_strings(opened_file, argv[current_file_index], multifile,
                         flag_string, template);
      fclose(opened_file);
      current_file_index++;
    }
  }

  return 0;
}

void concatenate_flag_string(char *_flag_string, char _flag) {
  if (strchr(_flag_string, _flag) == NULL) {
    char temp[2] = "-";
    temp[0] = _flag;
    strcat(_flag_string, temp);
  }
}

void print_grep_strings(FILE *_file, char *_file_name, bool _multifile,
                        char *_flag_string, char *_template) {
  char file_string[2048];
  int string_number = 0;
  int output_string_number = 0;
  bool string_printed = false;
  bool no_l_c_flags = !strchr(_flag_string, 'l') && !strchr(_flag_string, 'c');
  bool flag_n = strchr(_flag_string, 'n');
  regex_t reg_ex;
  int reg_flag = (strchr(_flag_string, 'i')) ? REG_ICASE : REG_EXTENDED;
  bool reg_res = regcomp(&reg_ex, _template, reg_flag);

  while (fgets(file_string, 2048, _file) != NULL) {
    string_printed = false;
    string_number++;
    reg_res = (regexec(&reg_ex, file_string, 0, NULL, 0) == 0) ? true : false;
    if (strchr(_flag_string, 'v')) reg_res = !reg_res;

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

  if (strchr(_flag_string, 'c')) {
    if (output_string_number > 0 && strchr(_flag_string, 'l'))
      output_string_number = 1;
    if (_multifile)
      printf("%s:%d\n", _file_name, output_string_number);
    else
      printf("%d\n", output_string_number);
  }

  if (strchr(_flag_string, 'l')) {
    if (output_string_number > 0) printf("%s\n", _file_name);
  }

  regfree(&reg_ex);
}