#include "delay.h"

sbit mq = P2^3;

unsigned char mq_2()
{
	if(mq == 0)
	{
		delay_ms(200);
		if(mq == 0)
			return 0;
	}
	return 1;
}