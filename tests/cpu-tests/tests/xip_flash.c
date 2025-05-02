#include "trap.h"
#include "peripheral/flash.h"
#include "peripheral/test_intf.h"

static inline uint8_t  inb(uintptr_t addr) { return *(volatile uint8_t  *)addr; }
static inline uint16_t inw(uintptr_t addr) { return *(volatile uint16_t *)addr; }
static inline uint32_t inl(uintptr_t addr) { return *(volatile uint32_t *)addr; }
static inline uint64_t inll(uintptr_t addr) { return *(volatile uint64_t *)addr; }

// #define CHECK_DATA(a,b) do{if((a)!=(b)) halt((int)b);}while(0)
#define CHECK_DATA(a,b) do{uint32_t test=(a); if(test!=(b)) halt((int)test);}while(0)

int main()
{
    test_intf_switch_flash(1);

    CHECK_DATA(inl(0x30000000), 0x33323130);
    CHECK_DATA(inl(0x30000004), 0x37363534);
    CHECK_DATA(inl(0x30000008), 0x3b3a3938);

    return 0;
}
