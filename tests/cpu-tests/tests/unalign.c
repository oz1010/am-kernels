#include "trap.h"

volatile unsigned x = 0xffffffff;
volatile unsigned char buf[16] = {0x11,0x11,0x11,0x11, 0x22,0x22,0x22,0x22,};


int main() {
	/* 非对齐写入测试 */
	for(int i = 0; i < 16; i++) buf[i] = i+1;
	*((volatile uint32_t*)(buf + 1)) = 0xaabbccdd;
	check(buf[1]==0xdd);
	check(buf[2]==0xcc);
	check(buf[3]==0xbb);
	check(buf[4]==0xaa);
	
	for(int i = 0; i < 16; i++) buf[i] = i+1;
	*((volatile uint32_t*)(buf + 2)) = 0xaabbccdd;
	check(buf[2]==0xdd);
	check(buf[3]==0xcc);
	check(buf[4]==0xbb);
	check(buf[5]==0xaa);
	
	for(int i = 0; i < 16; i++) buf[i] = i+1;
	*((volatile uint32_t*)(buf + 3)) = 0xaabbccdd;
	check(buf[3]==0xdd);
	check(buf[4]==0xcc);
	check(buf[5]==0xbb);
	check(buf[6]==0xaa);

	// /* 非对齐读取测试 */
	for(int i = 0; i < 16; i++) buf[i] = i+1;
	buf[1]=0xdd;
	buf[2]=0xcc;
	buf[3]=0xbb;
	buf[4]=0xaa;
	check(*((volatile unsigned*)(buf + 1)) == 0xaabbccdd);
	
	for(int i = 0; i < 16; i++) buf[i] = i+1;
	buf[2]=0xdd;
	buf[3]=0xcc;
	buf[4]=0xbb;
	buf[5]=0xaa;
	check(*((volatile unsigned*)(buf + 2)) == 0xaabbccdd);
	
	for(int i = 0; i < 16; i++) buf[i] = i+1;
	buf[3]=0xdd;
	buf[4]=0xcc;
	buf[5]=0xbb;
	buf[6]=0xaa;
	check(*((volatile unsigned*)(buf + 3)) == 0xaabbccdd);

	return 0;
}
