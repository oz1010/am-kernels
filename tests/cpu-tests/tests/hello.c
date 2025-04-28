#include "trap.h"

#define outb(addr, val) (*((volatile uint8_t*)(addr))=(val))
#define inb(addr) (*((volatile uint8_t*)(addr)))
#define bits(n) (0x1<<(n))
#define UART16550_BASEADDR (0x10000000)
#define UART16550_REG_LCR (UART16550_BASEADDR+0x3)
// value=sys_clk/(16*baud), 需要先写DL1，写DL0模块会立即开始工作
#define UART16550_REG_DL0 (UART16550_BASEADDR+0x0)
#define UART16550_REG_DL1 (UART16550_BASEADDR+0x1)

void init_uart16550()
{
    uint8_t val = inb(UART16550_REG_LCR);
    outb(UART16550_REG_LCR, val|=bits(7));
    // 115200 : 1c200
    outb(UART16550_REG_DL1, 0x00);
    outb(UART16550_REG_DL0, 0x01);
    outb(UART16550_REG_LCR, val&=~bits(7));
}

void uart16550_putstr(const char* str) {
    while(*str) {
        putch(*str);
        // TODO 需要改为判断状态寄存器或中断方式
        for(volatile int i=0;i<2; ++i) ;
        ++str;
    }
}

int main()
{
    init_uart16550();
    uart16550_putstr("1234567890abcdefghijklmn\n");
    uart16550_putstr("1234567890abcdefghijklmn\n");
    return 0;
}
