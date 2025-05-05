#include "trap.h"
#include "file/bin_header.h"
#include "klib.h"

extern bin_header_t bin_header;

#define MEM_ADDR_START          0x0f000000 // 需要避免全局变量
// #define MEM_ADDR_END            (_stack_pointer-4*12) // 注意不能覆盖栈区域，预留部分栈变量
#define MEM_ADDR_END            (0x0f000400-4*12) // 注意不能覆盖栈区域，预留部分栈变量

#define PSRAM_ENABLE            1
#define PSRAM_ADDR_START        0x80000000
#define PSRAM_ADDR_END          0x80001000

int main() {
    // 简单测试，内存要求读写字节对齐
    uint8_t *pmem8 = (uint8_t *)bin_header.bss_end;
    uint16_t *pmem16 = (uint16_t *)bin_header.bss_end;
    uint32_t *pmem32 = (uint32_t *)bin_header.bss_end;
    // 非4字节对齐读测试
    pmem32[0] = 0x44434241;
    if (pmem32[0]!=0x44434241) halt(1);
    if (pmem8[0]!='A') halt(2);
    if (pmem8[1]!='B') halt(3);
    if (pmem8[2]!='C') halt(4);
    if (pmem8[3]!='D') halt(5);
    // 非4字节对齐写测试
    pmem8[0] = 'a';
    pmem8[1] = 'b';
    pmem8[2] = 'c';
    pmem8[3] = 'd';
    if (pmem32[0]!=0x64636261) halt(11);

    uint32_t test_cnt = 0;
    // 8bit test
    for (uint32_t i=0; i<(MEM_ADDR_END-MEM_ADDR_START+1); ++i,++test_cnt) {
        uint8_t data = (uint8_t)((uint8_t)(uintptr_t)&pmem8[i]);
        // asm volatile("mv a0, sp; ebreak;");
        pmem8[i] = data;
        if (pmem8[i] != data) {
            return test_cnt;
        }
    }
    
    // 16bit test
    for (uint32_t i=0; i<(MEM_ADDR_END-MEM_ADDR_START+1); ++i,++test_cnt) {
        uint16_t data = (uint16_t)((uint16_t)(uintptr_t)&pmem16[i]);
        // asm volatile("mv a0, sp; ebreak;");
        pmem16[i] = data;
        if (pmem16[i] != data) {
            return test_cnt;
        }
    }
    
    // 32bit test
    for (uint32_t i=0; i<(MEM_ADDR_END-MEM_ADDR_START+1); ++i,++test_cnt) {
        uint32_t data = (uint32_t)((uint32_t)(uintptr_t)&pmem32[i]);
        // asm volatile("mv a0, sp; ebreak;");
        pmem32[i] = data;
        if (pmem32[i] != data) {
            return test_cnt;
        }
    }

#if(PSRAM_ENABLE)
    printf("psram 8bit test ...");
    pmem8 = (uint8_t *)PSRAM_ADDR_START;
    for (uint32_t i=0; i<(PSRAM_ADDR_END-PSRAM_ADDR_START+1); ++i) {
        uint8_t data = (uint8_t)((uint8_t)(uintptr_t)&pmem8[i]);
        pmem8[i] = data;
        if (pmem8[i] != data) {
            printf(" failed, i=%d\n", i);
            halt(i);
        }
    }
    printf(" done\n");
    
    printf("psram 16bit test ...");
    pmem16 = (uint16_t *)PSRAM_ADDR_START;
    for (uint32_t i=0; i<(PSRAM_ADDR_END-PSRAM_ADDR_START+1); ++i) {
        uint16_t data = (uint16_t)((uint16_t)(uintptr_t)&pmem16[i]);
        pmem16[i] = data;
        if (pmem16[i] != data) {
            printf(" failed, i=%d\n", i);
            halt(i);
        }
    }
    printf(" done\n");
    
    printf("psram 32bit test ...");
    pmem32 = (uint32_t *)PSRAM_ADDR_START;
    for (uint32_t i=0; i<(PSRAM_ADDR_END-PSRAM_ADDR_START+1); ++i) {
        uint32_t data = (uint32_t)((uint32_t)(uintptr_t)&pmem32[i]);
        pmem32[i] = data;
        if (pmem32[i] != data) {
            printf(" failed, i=%d\n", i);
            halt(i);
        }
    }
    printf(" done\n");

    halt(0);
#endif

    return 0;
}