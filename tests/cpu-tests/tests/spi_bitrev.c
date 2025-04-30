#include "trap.h"
#include "peripheral/spi.h"

#define CHECK_DATA(a,b) do{if((a)!=(b)) halt((int)b);}while(0)

uint32_t bitrev(uint32_t data)
{
    spi_dev->ss.ss = SPI_SLAVE_BITREV;
    spi_dev->divider.divider = 0;
    spi_ctrl_t ctrl_val = {
        .char_len = 16,
        .go_bsy = 0,
        .rx_neg = 0,
        .tx_neg = 1,
        .lsb = 1,
        .ie = 0,
        .ass = 1,
    };
    spi_dev->ctrl.raw_data = ctrl_val.raw_data;
   
    spi_dev->tx[0] = data;
    spi_dev->ctrl.go_bsy = 1;
    while(spi_dev->ctrl.go_bsy) ;

    return spi_dev->rx[0];
}

int main()
{
    CHECK_DATA(bitrev(0x0051), 0x8aff);
    CHECK_DATA(bitrev(0x0052), 0x4aff);
    return 0;
}