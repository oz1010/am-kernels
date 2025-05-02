#include "trap.h"
#include "peripheral/flash.h"
#include "peripheral/test_intf.h"

#define CHECK_DATA(a,b) do{if((a)!=(b)) halt((int)b);}while(0)

int main()
{
    test_intf_switch_flash(1);

    CHECK_DATA(flash_read(0x1000000+0x0), 0x33323130);
    CHECK_DATA(flash_read(0x1000000+0x1), 0x34333231);
    CHECK_DATA(flash_read(0x1000000+0x2), 0x35343332);
    CHECK_DATA(flash_read(0x1000000+0x3), 0x36353433);
    CHECK_DATA(flash_read(0x1000000+0x4), 0x37363534);
    CHECK_DATA(flash_read(0x1000000+0x5), 0x38373635);
    return 0;
}