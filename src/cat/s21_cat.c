#include "s21_cat.h"

int main(int argc, char **argv) {
  opt Options = Parser(argc, argv);
  OutputFile(&Options, argc, argv);
  return 0;
}

opt Parser(int argc, char **argv) {
  opt Options = {0};
  int opt = 0;
  int OptionIndex = 0;
  struct option LongOptions[] = {{"number", 0, NULL, 'n'},
                                 {"number-nonblank", 0, NULL, 'b'},
                                 {"squeeze-blank", 0, NULL, 's'},
                                 {0, 0, 0, 0}};
  while ((opt = getopt_long(argc, argv, "benstvTE", LongOptions,
                            &OptionIndex)) != -1) {
    switch (opt) {
      case 'b':
        Options.b = 1;
        break;

      case 'e':
        Options.E = 1;
        Options.v = 1;
        break;

      case 'E':
        Options.E = 1;
        break;

      case 'n':
        Options.n = 1;
        break;

      case 's':
        Options.s = 1;
        break;

      case 't':
        Options.T = 1;
        Options.v = 1;
        break;

      case 'T':
        Options.T = 1;
        break;

      case '?':
        perror("Error: option not found!\n");
        exit(1);
        break;

      default:
        perror("Error: option not found!\n");
        exit(1);
        break;
    }
  }
  return Options;
}

int ForVOutput(int ch) {
  if (ch == '\n' || ch == '\t') return ch;
  if (ch < 0 && ch > -127) {
    printf("M-^@");
    ch = ch & 0x74;
  }
  if (ch > 0 && ch <= 31) {
    putchar('^');
    ch = ch + 64;
  } else if (ch == 127) {
    putchar('^');
    ch = '?';
  }
  return ch;
}

void Outline(opt *Options, char *line, int k, int *CountRead,
             int *NotEmptyLineCount, int *EmptyLineCount) {
  for (int i = 0; i < k; i++) {
    if (!((Options->s) && (line[0] == '\n') &&
          (*EmptyLineCount > 1))) {  // s - сжатие смежных пустых строк
      if (Options->b) {  // b - нумерация непустых строк
        Options->n = 0;
        if ((i == 0) && (line[0] != '\n')) printf("%6d\t", *NotEmptyLineCount);
        if ((line[0] == '\n') && Options->s) printf("      \t");
      }
      if ((Options->n) && (i == 0)) {  // n - нумерация всех строк
        printf("%6d\t", *CountRead);
      }
      if ((Options->E) && (line[k - 1] == '\n') &&
          (i == k - 1)) {  // e - символ $ в конец каждой строки
        putchar('$');
      }
      if ((Options->t || Options->T) &&
          (line[i] == '\t')) {  // t - отображение TAB как ^I
        line[i] = 'I';
        putchar('^');
      }
      if (Options->v) {  // v - отображение невидимых символов
        line[i] = ForVOutput(line[i]);
      }
      putchar(line[i]);
    }
  }
}

void OutputFile(opt *Options, int argc, char **argv) {
  for (int i = optind; i < argc; i++) {
    FILE *fp = fopen(argv[i], "r");
    char *line = NULL;
    size_t len = 0;
    int LineCount = 0;          // счетчик всех строк
    int NotEmptyLineCount = 0;  // счетчик НЕпустых строк
    int EmptyLineCount = 0;  // счетчик смежных пустых строк
    int read = 0;
    if (fp == NULL) {
      printf("Error: File not found");
      exit(1);
    }

    while ((read = getline(&line, &len, fp)) != -1) {
      LineCount++;
      if (read > 1) {
        NotEmptyLineCount++;
      }
      if (read == 1) {
        if (Options->s && Options->n && EmptyLineCount >= 1) {
          LineCount = LineCount - 1;
        }
        EmptyLineCount++;
      } else {
        EmptyLineCount = 0;
      }
      Outline(Options, line, read, &LineCount, &NotEmptyLineCount,
              &EmptyLineCount);
    }
    free(line);
    fclose(fp);
  }
}