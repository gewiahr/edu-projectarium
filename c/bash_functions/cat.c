#include "cat.h"

int main(int argc, char **argv) {
  t_flag flag = {0};
  char current_flag = 0;
  int flag_count = 0;
  char *flags_available = "beEnsTtv";

  while ((current_flag = getopt(argc, argv, flags_available)) != -1) {
    flag = parce_flag(flag, current_flag);
    flag_count++;
  }

  int current_file = optind;
  while (current_file < argc) {
    FILE *opened_file = fopen(argv[current_file], "rt");
    if (!opened_file) {
      break;
    } else {
      if (flag_count == 0)
        output_file(opened_file);
      else
        output_modified_file(opened_file, flag);
      fclose(opened_file);
      current_file++;
    }
  }

  return 0;
}

t_flag parce_flag(t_flag _flag, char _current_flag) {
  switch (_current_flag) {
    case 'b':
      _flag.b = true;
      break;
    case 'E':
      _flag.E = true;
      break;
    case 'e':
      _flag.E = true;
      _flag.v = true;
      break;
    case 'n':
      _flag.n = true;
      break;
    case 's':
      _flag.s = true;
      break;
    case 'T':
      _flag.T = true;
      break;
    case 't':
      _flag.T = true;
      _flag.v = true;
      break;
    case 'v':
      _flag.v = true;
      break;
    default:
      break;
  }

  return _flag;
}

void output_file(FILE *_file) {
  char buffer[STRING_SIZE];
  while (fgets(buffer, STRING_SIZE, _file)) {
    fputs(buffer, stdout);
  }
}

void output_modified_file(FILE *_file, t_flag _flag) {
  bool two_EOS_appeared = false;
  int symbol = fgetc(_file);
  int previous_symbol = '\n';
  int string_number = 1;

  while (symbol != EOF) {
    if (!skip_repeated_empty_string(_flag, previous_symbol, symbol,
                                    two_EOS_appeared)) {
      if (((_flag.n && !_flag.b) || (_flag.b && symbol != '\n')) &&
          (previous_symbol == '\n')) {
        printf("%6d\t", string_number);
        string_number++;
      }

      if (previous_symbol == '\n' && symbol == '\n')
        two_EOS_appeared = true;
      else
        two_EOS_appeared = false;

      if (symbol == '\n' && _flag.E) {
        fputc('$', stdout);
      }

      if (symbol == '\t' && _flag.T) {
        fputc('^', stdout);
        symbol += 64;
      }

      if (_flag.v && symbol >= 0 && symbol <= 31 && symbol != '\n' &&
          symbol != '\t') {
        fputc('^', stdout);
        symbol += 64;
      }

      fputc(symbol, stdout);
      previous_symbol = symbol;
    }
    symbol = fgetc(_file);
  }
}

bool skip_repeated_empty_string(t_flag _flag, char _prev_symb, char _symb,
                                bool _two_EOS_appeared) {
  bool skip = false;
  if (_flag.s && _prev_symb == '\n' && _symb == '\n' && _two_EOS_appeared)
    skip = true;
  return skip;
}
