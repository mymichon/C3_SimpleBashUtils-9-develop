#define _GNU_SOURCE
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Options {
  int b;
  int n;
  int s;
  int t;
  int v;
  int E;
  int T;
} opt;

opt Parser(int argc, char **argv);
void OutputFile(opt *Options, int argc, char **argv);
void Outline(opt *Options, char *line, int n, int *CountRead,
             int *NotEmptyLineCount, int *EmptyLineCount);
int ForVOutput(int ch);
