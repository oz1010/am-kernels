#include "trap.h"
#include "peripheral/test_intf.h"

static inline uint8_t  inb(uintptr_t addr) { return *(volatile uint8_t  *)addr; }
static inline uint16_t inw(uintptr_t addr) { return *(volatile uint16_t *)addr; }
static inline uint32_t inl(uintptr_t addr) { return *(volatile uint32_t *)addr; }
static inline uint64_t inll(uintptr_t addr) { return *(volatile uint64_t *)addr; }
static inline void outb(uintptr_t addr, uint8_t data) { *(volatile uint8_t *)addr = data; }
static inline void outw(uintptr_t addr, uint16_t data) { *(volatile uint16_t *)addr = data; }
static inline void outl(uintptr_t addr, uint32_t data) { *(volatile uint32_t *)addr = data; }

#define CHECK_DATA(a,b) do{if((a)!=(b)) halt((int)b);}while(0)

int main() {
    test_intf_switch_psram(1);

    CHECK_DATA(inb(0x80000000), 0x30);
    CHECK_DATA(inb(0x80000001), 0x31);
    CHECK_DATA(inb(0x80000002), 0x32);
    CHECK_DATA(inb(0x80000003), 0x33);
    CHECK_DATA(inb(0x80000004), 0x34);
    CHECK_DATA(inb(0x80000005), 0x35);
    
    CHECK_DATA(inw(0x80000000), 0x3130);
    CHECK_DATA(inw(0x80000001), 0x3231);
    CHECK_DATA(inw(0x80000002), 0x3332);
    CHECK_DATA(inw(0x80000003), 0x3433);
    CHECK_DATA(inw(0x80000004), 0x3534);
    CHECK_DATA(inw(0x80000005), 0x3635);

    CHECK_DATA(inl(0x80000000), 0x33323130);
    CHECK_DATA(inl(0x80000001), 0x34333231);
    CHECK_DATA(inl(0x80000002), 0x35343332);
    CHECK_DATA(inl(0x80000003), 0x36353433);
    CHECK_DATA(inl(0x80000004), 0x37363534);
    CHECK_DATA(inl(0x80000005), 0x38373635);
    
    outb(0x80000000, 0x50);
    outb(0x80000001, 0x51);
    outb(0x80000002, 0x52);
    outb(0x80000003, 0x53);
    CHECK_DATA(inl(0x80000000), 0x53525150);
    
    outb(0x80000004, 0x54);
    outb(0x80000005, 0x55);
    outb(0x80000006, 0x56);
    outb(0x80000007, 0x57);
    CHECK_DATA(inl(0x80000004), 0x57565554);
    
    outw(0x80000000, 0x5150);
    outw(0x80000002, 0x5352);
    CHECK_DATA(inl(0x80000000), 0x53525150);
    
    outw(0x80000001, 0x5251);
    outw(0x80000003, 0x5453);
    CHECK_DATA(inl(0x80000001), 0x54535251);
    
    outw(0x80000002, 0x5352);
    outw(0x80000004, 0x5554);
    CHECK_DATA(inl(0x80000002), 0x55545352);
    
    outw(0x80000003, 0x5453);
    outw(0x80000005, 0x5655);
    CHECK_DATA(inl(0x80000003), 0x56555453);

    outl(0x80000000, 0x53525150);
    CHECK_DATA(inb(0x80000000), 0x50);
    CHECK_DATA(inb(0x80000001), 0x51);
    CHECK_DATA(inb(0x80000002), 0x52);
    CHECK_DATA(inb(0x80000003), 0x53);

    outl(0x80000001, 0x54535251);
    CHECK_DATA(inb(0x80000001), 0x51);
    CHECK_DATA(inb(0x80000002), 0x52);
    CHECK_DATA(inb(0x80000003), 0x53);
    CHECK_DATA(inb(0x80000004), 0x54);

    outl(0x80000002, 0x55545352);
    CHECK_DATA(inb(0x80000002), 0x52);
    CHECK_DATA(inb(0x80000003), 0x53);
    CHECK_DATA(inb(0x80000004), 0x54);
    CHECK_DATA(inb(0x80000005), 0x55);
    
    outl(0x80000003, 0x56555453);
    CHECK_DATA(inb(0x80000003), 0x53);
    CHECK_DATA(inb(0x80000004), 0x54);
    CHECK_DATA(inb(0x80000005), 0x55);
    CHECK_DATA(inb(0x80000006), 0x56);

    return 0;
}
