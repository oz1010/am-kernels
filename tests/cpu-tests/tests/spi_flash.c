#include "trap.h"

#define SPI_BASEADDR    (0x10001000)
#define SPI_RX0         (SPI_BASEADDR+0x0)
#define SPI_RX1         (SPI_BASEADDR+0x4)
#define SPI_RX2         (SPI_BASEADDR+0x8)
#define SPI_RX3         (SPI_BASEADDR+0xc)
#define SPI_TX0         (SPI_BASEADDR+0x0)
#define SPI_TX1         (SPI_BASEADDR+0x4)
#define SPI_TX2         (SPI_BASEADDR+0x8)
#define SPI_TX3         (SPI_BASEADDR+0xc)
#define SPI_CTRL        (SPI_BASEADDR+0x10)
#define SPI_DIVIDER     (SPI_BASEADDR+0x14)
#define SPI_SS          (SPI_BASEADDR+0x18)

#define CHECK_DATA(a,b) do{if((a)!=(b)) halt((int)b);}while(0)

typedef union {
    struct {
        uint32_t char_len:7;
        uint32_t reserved0:1;
        uint32_t go_bsy:1;
        uint32_t rx_neg:1;
        uint32_t tx_neg:1;
        uint32_t lsb:1;
        uint32_t ie:1;
        uint32_t ass:1;
        uint32_t reserved1:18;
    };
    uint32_t raw_data;
} spi_ctrl_t;

typedef union {
    struct {
        uint32_t ss:8;
        uint32_t reserved0:24;
    };
    uint32_t raw_data;
} spi_ss_t;

volatile spi_ctrl_t *spi_ctrl = (volatile spi_ctrl_t *)SPI_CTRL;
volatile spi_ss_t *spi_ss = (volatile spi_ss_t *)SPI_SS;
volatile uint32_t *spi_rx = (volatile uint32_t *)SPI_RX0;
volatile uint32_t *spi_tx = (volatile uint32_t *)SPI_TX0;

uint32_t bitrev_test(uint32_t data)
{
    spi_ss->ss = 7; // bitrev slave: 7, flash slave: 0
    spi_ctrl_t ctrl_val = {
        // .char_len = 64,
        .char_len = 16,
        .go_bsy = 0,
        .rx_neg = 0,
        .tx_neg = 1,
        .lsb = 1,
        .ie = 0,
        .ass = 1,
    };
    spi_ctrl->raw_data = ctrl_val.raw_data;

    /*
      SPI驱动程序在与slave通信之前, 先设置SS寄存器来选择目标slave, 并按照slave的约定配置SPI master的控制寄存器, 然后再将需要传输的数据写入发送数据寄存器, 最后往某控制寄存器写入表示"开始传输"的命令. SPI驱动程序可以轮询SPI master的状态寄存器, 当状态标志为"忙碌"时则等待, 直到状态标志为"空闲"为止, 此时可从接收数据寄存器中读出slave的回复.
     */

    spi_tx[0] = data;
    spi_ctrl->go_bsy = 1;

    while(spi_ctrl->go_bsy) ;

    return spi_rx[0];
}

uint32_t flash_read(uint32_t addr)
{
    spi_ctrl_t ctrl_val = {
        // .char_len = 64,
        .char_len = 16,
        .go_bsy = 0,
        .rx_neg = 0,
        .tx_neg = 1,
        .lsb = 1,
        .ie = 0,
        .ass = 1,
    };
    spi_ctrl->raw_data = ctrl_val.raw_data;
    // spi_ctrl->tx_neg = 1;
    // spi_ctrl->rx_neg = 0;

    /*
      SPI驱动程序在与slave通信之前, 先设置SS寄存器来选择目标slave, 并按照slave的约定配置SPI master的控制寄存器, 然后再将需要传输的数据写入发送数据寄存器, 最后往某控制寄存器写入表示"开始传输"的命令. SPI驱动程序可以轮询SPI master的状态寄存器, 当状态标志为"忙碌"时则等待, 直到状态标志为"空闲"为止, 此时可从接收数据寄存器中读出slave的回复.
     */

    spi_ss->ss = 7; // bitrev slave: 7, flash slave: 0
    spi_tx[0] = 0x5a;
    spi_ctrl->go_bsy = 1;

    while(spi_ctrl->go_bsy) ;

    halt(spi_rx[0]);
    halt(0x4321);

    return 0;
}

int main()
{
    CHECK_DATA(bitrev_test(0x5a), 0x33323130);
    return 0;
}