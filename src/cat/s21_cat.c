#include "s21_cat.h"

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cat_options(int argc, char *argv[], flags *flag);
void cat_proccess(char *argv[], flags *flag);

int main(int argc, char *argv[]) {
  flags flag = {
      .b = 0,
      .e = 0,
      .n = 0,
      .s = 0,
      .v = 0,
      .t = 0,
  };
  cat_options(argc, argv, &flag);
  while (optind < argc) {
    cat_proccess(argv, &flag);
    optind++;
  }
  return 0;
}

void cat_options(int argc, char *argv[], flags *flag) {
  int opt;
  static struct option options[] = {{"number-nonblank", 0, 0, 'b'},
                                    {"number", 0, 0, 'n'},
                                    {"squeeze-blank", 0, 0, 's'},
                                    {0, 0, 0, 0}};

  while ((opt = getopt_long(argc, argv, "+bEnsTvet", options, NULL)) != -1) {
    switch (opt) {
      case 'b':
        flag->b = 1;
        break;
      case 'E':
        flag->e = 1;
        break;
      case 'n':
        flag->n = 1;
        break;
      case 's':
        flag->s = 1;
        break;
      case 'T':
        flag->t = 1;
        break;
      case 'v':
        flag->v = 1;
        break;
      case 'e':
        flag->e = 1;
        flag->v = 1;
        break;
      case 't':
        flag->t = 1;
        flag->v = 1;
        break;
      default:
        printf("usage: ./s21_cat [-benstuv] [file ...]\n");
        break;
    }
    if (flag->b && flag->n) flag->n = 0;
  }
}

void cat_proccess(char *argv[], flags *flag) {
  FILE *file;
  file = fopen(argv[optind], "r");
  if (file != NULL) {
    int count_str = 1;
    int count_emp_str = 0;
    int last_char = '\n';
    while (!feof(file)) {
      int ch = fgetc(file);
      if (ch == EOF) break;
      if (((flag->b && ch != '\n') || flag->n) && last_char == '\n')
        printf("%6d\t", count_str++);
      if (flag->e && ch == '\n') printf("$");
      if (flag->s && ch == '\n' && last_char == '\n') {
        count_emp_str++;
        if (count_emp_str > 1) {
          continue;
        }
      } else {
        count_emp_str = 0;
      }
      if (flag->t && ch == '\t') {
        printf("^");
        ch = 'I';
      }
      if (flag->v) {
        if ((ch >= 0 && ch < 9) || (ch > 10 && ch < 32) ||
            (ch > 126 && ch < 160)) {
          printf("^");
          if (ch > 126) {
            ch -= 64;
          } else {
            ch += 64;
          }
        }
      }
      printf("%c", ch);
      last_char = ch;
    }
    fclose(file);
  } else {
    printf("cat: %s: No such file or directory\n", argv[optind]);
    exit(1);
  }
}
