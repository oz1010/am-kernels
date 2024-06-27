#include <klibtest.h>

#define TEST_CASE_SNPRINTF(fmt, num, check_str) do{\
    char str[64] = {0};\
    snprintf(str, sizeof(str), #num " | %" #fmt "\n", num);\
    check_mem(check_str, str);\
  }while(0)

void test_print() {
  // 打印整数
  TEST_CASE_SNPRINTF(d, INT32_MAX, "INT32_MAX | 2147483647\n");
  TEST_CASE_SNPRINTF(d, INT32_MIN, "INT32_MIN | -2147483648\n");
  TEST_CASE_SNPRINTF(d, 0, "0 | 0\n");
  TEST_CASE_SNPRINTF(d, -1, "-1 | -1\n");
  TEST_CASE_SNPRINTF(d, 1, "1 | 1\n");
  TEST_CASE_SNPRINTF(d, -15, "-15 | -15\n");
  TEST_CASE_SNPRINTF(d, 15, "15 | 15\n");
  TEST_CASE_SNPRINTF(d, -16, "-16 | -16\n");
  TEST_CASE_SNPRINTF(d, 16, "16 | 16\n");
  TEST_CASE_SNPRINTF(d, -256, "-256 | -256\n");
  TEST_CASE_SNPRINTF(d, 256, "256 | 256\n");

  // 打印十六进制数
  TEST_CASE_SNPRINTF(x, 0x0, "0x0 | 0\n");
  TEST_CASE_SNPRINTF(x, 0x10, "0x10 | 10\n");
  TEST_CASE_SNPRINTF(x, 0x32, "0x32 | 32\n");
  TEST_CASE_SNPRINTF(x, 0x54, "0x54 | 54\n");
  TEST_CASE_SNPRINTF(x, 0x76, "0x76 | 76\n");
  TEST_CASE_SNPRINTF(x, 0x98, "0x98 | 98\n");
  TEST_CASE_SNPRINTF(x, 0xba, "0xba | ba\n");
  TEST_CASE_SNPRINTF(x, 0xdc, "0xdc | dc\n");
  TEST_CASE_SNPRINTF(x, 0xfe, "0xfe | fe\n");
  TEST_CASE_SNPRINTF(x, 0xfedcba98, "0xfedcba98 | fedcba98\n");
  TEST_CASE_SNPRINTF(x, 0x78654321, "0x78654321 | 78654321\n");
}
