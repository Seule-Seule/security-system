#include<reg52.h>    //包含单片机寄存器的头文件
#include<intrins.h> //包含_nop_()函数定义的头文件
#include "1602.h"
#include "dht11.h"
#include "ds1302.h"
#include "timer.h"
#define uchar unsigned char
#define uint  unsigned int
#define delayNOP(); {_nop_();_nop_();_nop_();_nop_();};
sbit BEEP=P0^0;
sbit K1=P1^1;
sbit K2=P1^0;
sbit K3=P1^2;
sbit K4=P1^3;
sbit K5=P1^4;
char work_mode=0;
char SET_TIME_MODE=1,SET_TEMP_MODE=1,SET_RH_MODE=1;
xdata char set_H=10,set_M=10,set_S=10;
xdata int SET_TEMP_H=400,SET_TEMP_L=100;
xdata int SET_RH_H=60,SET_RH_L=10;

void SET_TIME(char SET_TIME_mode)
{
	switch(SET_TIME_mode)
	{
		case 1:
		PRINT_SET_TIME_hour();	
		break;//时
		case 2:
		PRINT_SET_TIME_minute();	
		break;//分
		case 3:
		PRINT_SET_TIME_second();	
		break;//秒
	}
}
void SET_TEMP(char SET_TEMP_mode)
{
	switch(SET_TEMP_mode)
	{
		case 1:
		PRINT_SET_TEMP_H();//设置温度高限	
		break;//时
		case 2:
		PRINT_SET_TEMP_L();//设置温度低限
		break;//分
	}
}

void SET_RH(char SET_RH_mode)
{
	switch(SET_RH_mode)
	{
		case 1:
		PRINT_SET_RH_H();//设置温度高限	
		break;//时
		case 2:
		PRINT_SET_RH_L();//设置温度低限
		break;//分
	}
}



void main()
{

	char code sys_Data[2][11]={"SYSTEM Init","Please Wait"};
	char xdata i;
	BEEP=1;
	LCD_1602_Init();
	Initial_DS1302();
		
	lcd_pos(2);
	for(i=0;i<11;i++)
	lcd_wdat(sys_Data[0][i]);
	lcd_pos(42);
	for(i=0;i<11;i++)
	lcd_wdat(sys_Data[1][i]);
	delay(2500);
	TIMER_Init();
//	DS1302_SetTime(DS1302_HOUR,10);	//设置的时间是10：54：30
//	DS1302_SetTime(DS1302_MINUTE,54);
//	DS1302_SetTime(DS1302_SECOND,30);   

while(1)
{
	switch(work_mode)
	{
		case 0:break;//正常输出
		case 1:SET_TIME(SET_TIME_MODE);break;//修改时间
		case 2:SET_TEMP(SET_TEMP_MODE);break;//修改温度
		case 3:SET_RH(SET_RH_MODE);break;//修改湿度
		default:break;
	}

}

} 