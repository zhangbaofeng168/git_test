#include "s5pv210.h"

void put_char(char c)
{
	while( !( (UTRSTAT0>>2)&1 ) );//wait transmit buffer register empty
	UTXH0 = c;
}

void put_string(char *str)
{
	char *p = str;
	while(*p){
		put_char(*p++);
	}
}

int uart_init()
{
	__REG(0xE0200000) = 0x2222;//config GPA0_0/1/2/3 as uart mode

	ULCON0 = 0x3;		//data=8bit
	UCON0 = 0x3c5;		//polling
	UBRDIV0 = 34;
	UDIVSLOT0 = 0xdddd;
	
	return 0;
}



