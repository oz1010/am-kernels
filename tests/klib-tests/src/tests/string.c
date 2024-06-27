#include <klibtest.h>

void hello() {
  int i;
  for (i = 0; i < 3; i ++) {
    putstr("Hello, KLIB\n");
  }
  printf("hello test done, i=%d.\n", i);
}

void test_string() {
  // test strlen
  assert(strlen("") == 0);
  assert(strlen("hello world") == 11);

  // test strcpy
  {
    char const str0[32] = {""};
    char str1[32] = {};
    strcpy(str1, "");
    check_mem(str0, str1);
  }
  {
    char const str0[32] = {"hello"};
    char str1[32] = {};
    strcpy(str1, "hello");
    check_mem(str0, str1);
  }

  // test strncpy
  {
    char const str0[32] = {""};
    char str1[32] = {};
    strncpy(str1, "hello world", 0);
    check_mem(str0, str1);
  }
  {
    char const str0[32] = {"hello"};
    char str1[32] = {};
    strncpy(str1, "hello world", 5);
    check_mem(str0, str1);
  }

  // test strcat
  {
    char const str0[32] = {"hello world"};
    char str1[32] = {"hello"};
    strcat(str1, " world");
    check_mem(str0, str1);
  }
  {
    char const str0[32] = {" world"};
    char str1[32] = {""};
    strcat(str1, " world");
    check_mem(str0, str1);
  }

  // test strcmp
  check(strcmp("", "hello")<0);
  check(strcmp("hell", "hello")<0);
  check(strcmp("hello", "")>0);
  check(strcmp("hello", "hell")>0);
  check(strcmp("", "")==0);
  check(strcmp("hello", "hello")==0);
}
