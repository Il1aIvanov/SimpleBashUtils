#ifndef S21_GREP_H_
#define S21_GREP_H_

#define buff_size 1024

typedef struct flag {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int o;
  int f;
  int c_flag;
  char str[buff_size];
  char str_o[buff_size];
  char namefile[buff_size];
  char argarray[buff_size];
} flags;

#endif