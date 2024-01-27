#include "s21_grep.h"

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void grep_options(int argc, char *argv[], flags *flag);
void grep_proccess(char *argv[], flags *flag);
void f_flag(flags *flag);

int main(int argc, char *argv[]) {
  flags flag = {0};
  grep_options(argc, argv, &flag);
  while (optind < argc) {
    grep_proccess(argv, &flag);
    optind++;  // index of first element argv, not option
  }
  return 0;
}

void grep_options(int argc, char *argv[], flags *flag) {
  int opt;
  while ((opt = getopt_long(argc, argv, "e:ivclnhsf:o", NULL, 0)) != -1) {
    switch (opt) {
      case 'e':
        flag->e = 1;
        strcat(flag->argarray, optarg);
        strcat(flag->argarray, "|");
        break;
      case 'i':
        flag->i = 1;
        break;
      case 'v':
        flag->v = 1;
        break;
      case 'c':
        flag->c = 1;
        break;
      case 'l':
        flag->l = 1;
        break;
      case 'n':
        flag->n = 1;
        break;
      case 'h':
        flag->h = 1;
        break;
      case 's':
        flag->s = 1;
        break;
      case 'o':
        flag->o = 1;
        break;
      case 'f':
        flag->f = 1;
        strcpy(flag->namefile, optarg);
        f_flag(flag);
        break;
      default:

        break;
    }
    if (flag->v && flag->o) {
      flag->o = 0;
    }
  }
  if (!flag->e && !flag->f) {
    if (argc > optind) {
      strcat(flag->argarray, argv[optind]);
    }
    optind++;
  }
  if (flag->e || flag->f) {
    flag->argarray[strlen(flag->argarray) - 1] = '\0';
  }
  if (argc - optind > 1) flag->c_flag = 1;
}

void grep_proccess(char *argv[], flags *flag) {
  FILE *fp;
  regex_t regex;
  regmatch_t regmatch;
  int c_count = 0;
  int str_count = 0;
  int flag_i = REG_EXTENDED;
  if (flag->i) {
    flag_i = REG_EXTENDED | REG_ICASE;
  }
  regcomp(&regex, flag->argarray, flag_i);
  fp = fopen(argv[optind], "rb");
  if (fp != NULL) {
    while (fgets(flag->str, buff_size, fp) != NULL) {
      int dupl = regexec(&regex, flag->str, 1, &regmatch, 0);
      str_count++;
      if (flag->o) strcpy(flag->str_o, flag->str);
      if ((!dupl || flag->v) && flag->c_flag && !flag->l && !flag->h &&
          !flag->c && !flag->f)
        printf("%s:", argv[optind]);
      if (!dupl) c_count++;
      if (flag->v) dupl = !dupl;
      if (!dupl && !flag->l && !flag->c && !flag->n && !flag->o) {
        printf("%s", flag->str);
        if (flag->str[strlen(flag->str) - 1] != '\n') printf("\n");
      }
      if (!dupl && flag->n && !flag->c && !flag->l) {
        if (flag->o) {
          printf("%d:", str_count);
        } else {
          printf("%d:%s", str_count, flag->str);
          if (flag->str[strlen(flag->str) - 1] != '\n') printf("\n");
        }
      }
      if (!dupl && flag->o && !flag->l && !flag->c) {
        char *point = flag->str_o;
        while ((regexec(&regex, point, 1, &regmatch, 0) == 0)) {
          printf("%.*s\n", (int)(regmatch.rm_eo - regmatch.rm_so),
                 point + regmatch.rm_so);
          point += regmatch.rm_eo;
        }
      }
    }
    regfree(&regex);
    if (flag->l && c_count < 1 && flag->v) {
      printf("%s\n", argv[optind]);
    }
    if (flag->l && c_count > 0 && !flag->c) printf("%s\n", argv[optind]);
    if (flag->c && flag->c_flag && !flag->h) printf("%s:", argv[optind]);
    if (flag->c && !flag->l && !flag->v) printf("%d\n", c_count);
    if (flag->c && !flag->l && flag->v) printf("%d\n", str_count - c_count);
    if (flag->c && flag->l) {
      if (c_count > 0) {
        c_count = 1;
        printf("%d\n", c_count);
        printf("%s\n", argv[optind]);
      } else
        printf("%d\n", c_count);
    }
    fclose(fp);
  } else {
    regfree(&regex);
    if (!flag->s)
      fprintf(stderr, "grep: %s: No such fp or directory\n", argv[optind]);
  }
}

void f_flag(flags *flag) {
  FILE *file;
  file = fopen(flag->namefile, "rb");
  if (file != NULL) {
    while (!feof(file)) {
      if (fgets(flag->str, 1000, file) != NULL) {
        if (flag->str[strlen(flag->str) - 1] == '\n' &&
            strlen(flag->str) - 1 != 0)
          flag->str[strlen(flag->str) - 1] = '\0';
        strcat(flag->argarray, flag->str);
        strcat(flag->argarray, "|");
      }
    }
    fclose(file);
  }
}
