#ifndef __KLIB_TEST_H__
#define __KLIB_TEST_H__

#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

extern void (*entry)();
#define CASE(id, entry_, ...) \
  case id: { \
    void entry_(); \
    entry = entry_; \
    __VA_ARGS__; \
    entry_(); \
    break; \
  }

// 不满足条件时，停住
#define check(cond) \
  do{\
    if (!(cond)){\
      printf("[%s %s:%d] check failed: " #cond ,__FILE__, __FUNCTION__, __LINE__);\
      halt(1);\
    }\
  }while(0)

// 检查[l,r)区间中的值是否依次为val, val + 1, val + 2...
#define check_seq(_L,_R,_VAL) \
  do{\
    int i;\
    int l = _L;\
    int r = _R;\
    int val = _VAL;\
    for (i=l;i<r;++i) {\
      check(data[i]==val+i-1);\
    }\
  }while(0)

// 检查[l,r)区间中的值是否均为val
#define check_eq(_L,_R,_VAL) \
  do{\
    int i;\
    int l = _L;\
    int r = _R;\
    int val = _VAL;\
    for (i=l;i<r;++i) {\
      check(data[i]==val);\
    }\
  }while(0)

// 检查两个内存区间数据是否一致
#define check_mem(A,B) \
  do{\
    int i;\
    for(i=0;i<(sizeof(A)/sizeof(A[0]));++i) {\
      if(A[i]!=B[i]) {\
        printf("dismatched %d: %#x %#x\n", i, A[i], B[i]);\
        check(A[i]==B[i]);\
      }\
    }\
  }while(0)

#endif
