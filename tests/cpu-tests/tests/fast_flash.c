#include "trap.h"
#include "peripheral/test_intf.h"

static inline uint8_t  inb(uintptr_t addr) { return *(volatile uint8_t  *)addr; }
static inline uint16_t inw(uintptr_t addr) { return *(volatile uint16_t *)addr; }
static inline uint32_t inl(uintptr_t addr) { return *(volatile uint32_t *)addr; }
static inline uint64_t inll(uintptr_t addr) { return *(volatile uint64_t *)addr; }

#define FLASH_BASEADDR (0x30000000)
#define CHECK_DATA(a,b) do{if((a)!=(b)) halt((int)b);}while(0)

int main()
{
    test_intf_switch_flash(1);

    CHECK_DATA(inb(FLASH_BASEADDR+0), 0x30);
    CHECK_DATA(inb(FLASH_BASEADDR+1), 0x31);
    CHECK_DATA(inb(FLASH_BASEADDR+2), 0x32);
    CHECK_DATA(inb(FLASH_BASEADDR+3), 0x33);
    CHECK_DATA(inb(FLASH_BASEADDR+4), 0x34);
    CHECK_DATA(inb(FLASH_BASEADDR+5), 0x35);
    
    CHECK_DATA(inw(FLASH_BASEADDR+0), 0x3130);
    CHECK_DATA(inw(FLASH_BASEADDR+1), 0x3231);
    CHECK_DATA(inw(FLASH_BASEADDR+2), 0x3332);
    CHECK_DATA(inw(FLASH_BASEADDR+3), 0x3433);
    CHECK_DATA(inw(FLASH_BASEADDR+4), 0x3534);
    CHECK_DATA(inw(FLASH_BASEADDR+5), 0x3635);
    
    CHECK_DATA(inl(FLASH_BASEADDR+0), 0x33323130);
    CHECK_DATA(inl(FLASH_BASEADDR+1), 0x34333231);
    CHECK_DATA(inl(FLASH_BASEADDR+2), 0x35343332);
    CHECK_DATA(inl(FLASH_BASEADDR+3), 0x36353433);
    CHECK_DATA(inl(FLASH_BASEADDR+4), 0x37363534);
    CHECK_DATA(inl(FLASH_BASEADDR+5), 0x38373635);
    
    CHECK_DATA(inll(FLASH_BASEADDR+0), 0x3736353433323130LL);
    CHECK_DATA(inll(FLASH_BASEADDR+1), 0x3837363534333231LL);
    CHECK_DATA(inll(FLASH_BASEADDR+2), 0x3938373635343332LL);
    CHECK_DATA(inll(FLASH_BASEADDR+3), 0x3a39383736353433LL);
    CHECK_DATA(inll(FLASH_BASEADDR+4), 0x3b3a393837363534LL);
    CHECK_DATA(inll(FLASH_BASEADDR+5), 0x3c3b3a3938373635LL);
    
    return 0;
}
