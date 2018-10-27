#include "intrins.h"
/***********************************************************
 *					延时函数
 * 		  开发板晶振是12MHZ的，每个机器周期1us
 *		   40us用于DHT11通讯，需要精确
*************************************************************/

#define delay1us()	_nop_();_nop_()        //延时2us
void delay10us();							//延时10us
void delay1ms();							//延时1ms
void delay_ms(unsigned short s);			 //延时s ms
void delay40us();							 //延时40us