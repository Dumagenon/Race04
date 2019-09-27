#include "mainhead.h"

void mx_printstr(const char *s) {
  int q = mx_strlen(s);
  write(1, s, q);
}
