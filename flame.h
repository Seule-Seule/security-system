#include "delay.h"



sbit flame = P2^2;
unsigned char m;

unsigned char flame_read()
{
	flame = 1;
	delay_ms(200);
	if(flame == 0)
	 return 0;
	return 1;
}
	
