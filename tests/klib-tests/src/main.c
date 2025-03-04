#include <klibtest.h>

void (*entry)() = NULL; // mp entry

static const char *tests[256] = {
  ['h'] = "hello",
  ['s'] = "test_string",
  ['p'] = "test_print",
};

int main(const char *args) {
  switch (args[0]) {
    CASE('h', hello);
    CASE('s', test_string);
    CASE('p', test_print);
    case 'H':
    default:
      printf("Usage: make run mainargs=*\n");
      for (int ch = 0; ch < 256; ch++) {
        if (tests[ch]) {
          printf("  %c: %s\n", ch, tests[ch]);
        }
      }
      return -1;
  }
  return 0;
}
