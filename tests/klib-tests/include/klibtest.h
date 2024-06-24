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

#endif
