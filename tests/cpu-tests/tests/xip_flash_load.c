#include "trap.h"
#include "peripheral/flash.h"
#include "peripheral/test_intf.h"

#define CHECK_DATA(a,b) do{if((a)!=(b)) halt((int)b);}while(0)
// 通过找到当前代码段使用大小，4字节对齐后，使用后面部分即可，hexdump -C <bin>
#define NEW_CODE_ENTRY      ((0x0f000000+0x268))
// 使用前面的数据可以
// #define NEW_CODE_ENTRY      ((0x0f000000+0x0))

static void (*new_code_entry) (void) = (void *)NEW_CODE_ENTRY;
static volatile uint32_t *new_code_mem = (void *)NEW_CODE_ENTRY;

int main()
{
    test_intf_switch_flash(2);

    uint32_t code;
    for (uint32_t idx=0; idx<8; ++idx) {
        code = *(volatile uint32_t*)(TEST_INIF_FLASH_BASEADDR + 4*idx);
        new_code_mem[idx] = code;
    }
    new_code_entry();
    return 0;
}