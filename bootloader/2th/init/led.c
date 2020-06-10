#include "s5pv210.h"

int led_test()
{
	GPH0CON = 0x1111;
	GPH0DAT = 0x08;
	
	return 0;
}
