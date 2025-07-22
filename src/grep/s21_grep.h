#define _GNU_SOURCE
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct arg {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
  char pattern[1024];
  int lenPattern;
} arguments;

arguments Parser(int argc, char **argv);
void Output(arguments arg, int argc, char **argv);
void AddPaternInE(arguments *arg, char *patern);
void OutputWithFlags(arguments arg, char *path, regex_t *reg);
void OutputLine(char *line, int n);
void PrintPatternO(regex_t *re, char *line);
void AddPatternF(arguments *arg, char *filepath);
