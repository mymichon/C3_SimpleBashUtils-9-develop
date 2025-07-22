#include "s21_grep.h"

int main(int argc, char **argv) {
  arguments arg = Parser(argc, argv);
  Output(arg, argc, argv);
  return 0;
}

arguments Parser(int argc, char **argv) {
  arguments arg = {0};
  int opt = 0;
  while ((opt = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    switch (opt) {
      case 'e':  // e - позволяет явно указать один и несколько шаблонов поиска
                 // для поиска строк. Полезно, если есть запрос на поиск
                 // нескольких конкретных шаблонов Явно требует аргумент в виде
                 // паттерна
        arg.e = 1;
        AddPaternInE(&arg, optarg);
        break;

        // Если разобрана опция с аргументом, то указатель на аргумент в массиве
        //  argv кладётся в переменную optarg

      case 'i':
        arg.i = REG_ICASE;  // Обеспечивает регистронезависимый поиск
        break;

      case 'v':
        arg.v = 1;  // v - выводит строки, в которых совпадение не обнаружено
        break;

      case 'c':
        arg.c = 1;  // c - Ищет кол-во совпадений с паттерном
        break;

      case 'n':
        arg.n = 1;  // n - выводит строки, в кот найдено совпадение +
                    // прописывает номер найденной строки
        break;

      case 'h':
        arg.h = 1;  // h - cкрывает имена файлов при выводе результатов поиска
        break;

      case 'l':
        arg.l = 1;  // l - выводит имя файла в кот найдено совпадение
        break;

      case 's':
        arg.s = 1;  // s - Скрывает сообщения об ошибках ввода/вывода
        break;

      case 'f':
        arg.f = 1;  // f - Позволяет указать файл чтоб использовать его
                    // содержимое как паттерн для поиска
                    //  Облегчает выполнение поиска с несколькими шаблонами или
                    //  с шаблонами, кот могут быть
                    // слишком длинными или сложными
        AddPatternF(&arg, optarg);
        break;

      case 'o':
        arg.o = 1;  // о - Выводит только сами паттерны которые удалось найти

        break;

      case '?':
        if (!(arg.s)) {
          perror("Error: option not found!\n");
        }
        exit(1);
        break;

      default:
        if (!(arg.s)) {
          perror("Error: option not found!\n");
        }
        exit(1);
        break;
    }
  }
  if (arg.lenPattern == 0) {
    AddPaternInE(&arg, argv[optind]);
    optind++;
  }
  if (argc - optind == 1) {  // кол-во тхт поданых на вход
    arg.h = 1;
  }
  return arg;
}

void Output(arguments arg, int argc, char **argv) {
  regex_t re;
  int error = regcomp(&re, arg.pattern, REG_EXTENDED | arg.i);
  if (error) {
    if (!(arg.s)) {
      perror("Error");
    }
    exit(1);
  }
  for (int i = optind; i < argc; i++) {
    OutputWithFlags(arg, argv[i], &re);
  }
  regfree(&re);
}

void OutputWithFlags(arguments arg, char *path, regex_t *reg) {
  FILE *fp = fopen(path, "r");
  if (fp == NULL) {
    if (!(arg.s)) {
      perror(path);
    }
    exit(1);
  }

  char *line = NULL;
  size_t len = 0;
  int StringLength = getline(&line, &len, fp);
  int count = 0;
  int c = 0;  // счетчик для флага -с(выводит кол-во совпадений)
  while (StringLength != -1) {
    count++;
    int result = regexec(reg, line, 0, NULL, 0);
    if (((result == 0) && !arg.v) || (arg.v && (result != 0))) {
      if (!arg.c && !arg.l) {
        if (!arg.h) {
          printf("%s:", path);
        }
        if (arg.n) {
          printf("%d:", count);
        }
        if (arg.o) {
          PrintPatternO(reg, line);
        }
        if (!arg.o) {
          OutputLine(line, StringLength);
        }
        if (arg.o && arg.v && result != 0) {
          OutputLine(line, StringLength);
        }
      }
      c++;
    }
    StringLength = getline(&line, &len, fp);
  }

  if (arg.c && !arg.l) {
    if (!arg.h) {
      printf("%s:", path);
    }
    printf("%d\n", c);
  }
  if (arg.l && !arg.c) {
    if (c > 0) {
      printf("%s\n", path);
    }
  }
  if (arg.c && arg.l) {
    if (!arg.h) {
      printf("%s:", path);
    }
    if (arg.v) {
      printf("1\n");
    } else {
      printf("%d\n", c);
    }
    if (c > 0) {
      printf("%s\n", path);
    }
  }
  free(line);
  fclose(fp);
}

void AddPaternInE(arguments *arg, char *patern) {
  if (arg->lenPattern != 0) {
    strcat(arg->pattern + arg->lenPattern, "|");
    arg->lenPattern++;
  }
  arg->lenPattern += sprintf(arg->pattern + arg->lenPattern, "(%s)", patern);
}

void OutputLine(char *line, int n) {
  for (int i = 0; i < n; i++) {
    putchar(line[i]);
  }
  if (line[n - 1] != '\n') {
    putchar('\n');
  }
}

void PrintPatternO(regex_t *re, char *line) {
  regmatch_t N;
  int offset = 0;  // сдвиг
  while (1) {
    int result = regexec(re, line + offset, 1, &N, 0);
    if (result != 0) {
      break;
    }
    for (int i = N.rm_so; i < N.rm_eo; i++) {
      putchar(line[i]);
    }
    putchar('\n');
    offset += N.rm_eo;
  }
}

void AddPatternF(arguments *arg, char *filepath) {
  FILE *fp = fopen(filepath, "r");
  if (fp == NULL) {
    if (!arg->s) {
      perror(filepath);
    }
    exit(1);
  }
  char *line = NULL;
  size_t memlen = 0;
  int StringLength;
  StringLength = getline(&line, &memlen, fp);

  while (StringLength != -1) {
    if (line[StringLength - 1] == '\n') {
      line[StringLength - 1] = '\0';
    }
    AddPaternInE(arg, line);
    StringLength = getline(&line, &memlen, fp);
  }
  free(line);
  fclose(fp);
}