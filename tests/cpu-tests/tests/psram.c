#include "trap.h"
#include "peripheral/test_intf.h"

static inline uint8_t  inb(uintptr_t addr) { return *(volatile uint8_t  *)addr; }
static inline uint16_t inw(uintptr_t addr) { return *(volatile uint16_t *)addr; }
static inline uint32_t inl(uintptr_t addr) { return *(volatile uint32_t *)addr; }
static inline uint64_t inll(uintptr_t addr) { return *(volatile uint64_t *)addr; }

#define CHECK_DATA(a,b) do{if((a)!=(b)) halt((int)b);}while(0)

int main() {
    test_intf_switch_psram(1);

    CHECK_DATA(inl(0x80000000), 0x33323130);
    CHECK_DATA(inl(0x80000001), 0x34333231);
    CHECK_DATA(inl(0x80000002), 0x35343332);
    CHECK_DATA(inl(0x80000003), 0x36353433);
    CHECK_DATA(inl(0x80000004), 0x37363534);
    CHECK_DATA(inl(0x80000005), 0x38373635);

    return 0;
}
