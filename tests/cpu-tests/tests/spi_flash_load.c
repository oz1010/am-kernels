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

void jump_to_address(uint32_t addr) {
    __asm__ volatile (
        "mv a0, %0\n"        // 将 addr 移入 a0
        "jr a0\n"            // 无条件跳转到 a0 地址处
        :
        : "r"(addr)
        : "a0"
    );
    __builtin_unreachable(); // 告诉编译器不会返回
}

int main()
{
    test_intf_switch_flash(2);
    flash_init();

    uint32_t code;
    for (uint32_t idx=0; idx<8; ++idx) {
        code = flash_read(4*idx);
        new_code_mem[idx] = code;
    }
    // jump_to_address(NEW_CODE_ENTRY);
    // asm volatile(
    //         "b ;"
    //         "ebreak;"
    //     );
    // halt(new_code_mem[2]);
    new_code_entry();
    // flash_read(0x4);
    // flash_init();
    // CHECK_DATA(flash_read(0x0), 0x33323130);
    // CHECK_DATA(flash_read(0x1), 0x34333231);
    // CHECK_DATA(flash_read(0x2), 0x35343332);
    // CHECK_DATA(flash_read(0x3), 0x36353433);
    // CHECK_DATA(flash_read(0x4), 0x37363534);
    // CHECK_DATA(flash_read(0x5), 0x38373635);
    return 0;
}