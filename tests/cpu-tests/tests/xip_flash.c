#include "trap.h"
#include "peripheral/flash.h"
#include "peripheral/test_intf.h"

int main()
{
    test_intf_switch_flash(1);
    uint32_t data;

    // *(volatile uint32_t *)SPI_DIVIDER = 0;
    // *(volatile uint32_t *)SPI_SS= 1;
    // *(volatile uint32_t *)SPI_TX0= 0;
    // *(volatile uint32_t *)SPI_TX1= 0x03000002;
    // *(volatile uint32_t *)SPI_CTRL= 0x2540;
    // while(spi_dev->ctrl.go_bsy) ;
    // data = *(volatile uint32_t*)SPI_RX0;

    data = *(volatile uint32_t*)0x30000000;
    data = *(volatile uint32_t*)0x30000004;

    // flash_init();
    // data = flash_read(0x2);

    halt(data);

    return 0;
}
