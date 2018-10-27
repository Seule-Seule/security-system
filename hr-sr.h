#include "delay.h"

sbit hr = P3^7;

unsigned char hr_sr()
{
	if(hr == 1)
	{
		delay_ms(200);
		if(hr == 1)
			return 0;
	}
	return 1;
}