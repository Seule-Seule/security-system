/*******************************************************************************
* ?????	     : ?????????
* ????IO	     : P2^1
* ???��??       : ????????
* ???			 ?????????????????????????????
*******************************************************************************/

#include <reg51.h>
#include "delay.h"

sbit Beep =  P2^1 ;

/*******************************************************************************
* ??????         : beep
* ????????		   :  ?????????????��???
* ????           : ??
* ???         	 : ??
*******************************************************************************/

void bep()
{
	unsigned char t = 90;			//?????t?��????????????????????
	unsigned char i,j;
	for(i=0;i<200;i++)
	{
	Beep=~Beep;
	for(j=0;j<t;j++); 
}
delay_ms(200);
}