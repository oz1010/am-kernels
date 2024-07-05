#include <am.h>
#include <klib-macros.h>
#include <stdio.h>

int main(const char *args) {
  const char *fmt =
    "Hello, AbstractMachine!\n"
    "mainargs = '%'.\n";

  for (const char *p = fmt; *p; p++) {
    (*p == '%') ? putstr(args) : putch(*p);
  }

  printf("This from printf %s\nOK?\n", args);

  return 0;
}
