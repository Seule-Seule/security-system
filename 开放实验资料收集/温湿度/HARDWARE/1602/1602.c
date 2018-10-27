#include "reg52.h"
#include "1602.h"
#include "intrins.h"
#define DS1302_SECOND	0x80
#define DS1302_MINUTE	0x82
#define DS1302_HOUR		0x84 


extern xdata char set_H,set_M,set_S;
extern xdata int SET_TEMP_H,SET_TEMP_L;//温度高低限制
extern xdata int SET_RH_H,SET_RH_L;
extern void DS1302_SetTime(unsigned char Address, unsigned char Value);
sbit rs=P3^5;
sbit rw=P3^6;
sbit ep=P3^7;

sbit KEY1=P1^1;
sbit KEY2=P1^0;
sbit KEY3=P1^2;
sbit KEY4=P1^3;
sbit KEY5=P1^4;


void delay (int m)
{
 xdata unsigned int i,j;
 for (i=0;i<m;i++)
 for (j=0;j<253;j++);
}

 BOOL lcd_bz()
{
  BOOL result;
  rs=0;           // 读忙信号
  rw=1;
  ep=1;
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  result = (BOOL)(P2&0x80);
  ep=0;
  return result;
}

void lcd_wcmd (BYTE cmd)
{
  while (lcd_bz());
  rs=0;
  rw=0;
  ep=0;
  _nop_();
  _nop_();
  P2=cmd ;
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  ep=1;
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  ep=0;
}

void lcd_pos (BYTE pos)
{
  lcd_wcmd (pos|0x80);
}

void lcd_wdat (BYTE dat)
{
   while (lcd_bz());
  rs=1;
  rw=0;
  ep=0;
  _nop_();
  _nop_();
  P2=dat ;
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  ep=1;
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  ep=0;
}

void LCD_1602_Init(void)
{
  lcd_wcmd (0x38);
  delay (1);
  lcd_wcmd (0x0c);
  delay (1);
  lcd_wcmd (0x06);
  delay (1);
  lcd_wcmd (0x01);
  delay (1);
}
char code SETTEMP[]= {"SET  TEMP:"};
char code REALTEMP[]={"REAL TEMP:"};
void Print_Temp(int Set_temp,int Real_temp)
{
	char i;
	lcd_pos (0);
for(i=0;i<10;i++)
	lcd_wdat(SETTEMP[i]);
	if(Set_temp<0)
	{lcd_wdat('-');Set_temp=-Set_temp;}
	else
		lcd_wdat(' ');
	
	lcd_wdat('0'+Set_temp/100);
	lcd_wdat('0'+(Set_temp/10)%10);
		lcd_wdat('.');
	lcd_wdat('0'+Set_temp%10);

	lcd_wdat('C');	
	
	
	lcd_pos (40);
for(i=0;i<10;i++)
	lcd_wdat(REALTEMP[i]);
	if(Real_temp<0)
	{lcd_wdat('-');Real_temp=-Real_temp;}
	else
		lcd_wdat(' ');
	lcd_wdat('0'+Real_temp/100);
	lcd_wdat('0'+(Real_temp/10)%10);
	lcd_wdat('.');
	lcd_wdat('0'+Real_temp%10);
	lcd_wdat('C');		
}

void PRINT_SET_TIME_TIME()
{
		lcd_pos (44);
	lcd_wdat('0'+set_H/10);
	lcd_wdat('0'+set_H%10);
	lcd_wdat(':');
	lcd_wdat('0'+set_M/10);
	lcd_wdat('0'+set_M%10);
	lcd_wdat(':');
	lcd_wdat('0'+set_S/10);
	lcd_wdat('0'+set_S%10);
}
void PRINT__TEMP_H(void)
{
		lcd_pos (44);
	lcd_wdat('0'+SET_TEMP_H/100);
	lcd_wdat('0'+(SET_TEMP_H/10)%10);
	lcd_wdat('.');
	lcd_wdat('0'+SET_TEMP_H%10);
	lcd_wdat('C');
}
void PRINT__TEMP_L(void)
{
		lcd_pos (44);
	lcd_wdat('0'+SET_TEMP_L/100);
	lcd_wdat('0'+(SET_TEMP_L/10)%10);
	lcd_wdat('.');
	lcd_wdat('0'+SET_TEMP_L%10);
	lcd_wdat('C');
}
void PRINT__RH_H(void)
{
		lcd_pos (44);
	lcd_wdat('0'+SET_RH_H/10);
	lcd_wdat('0'+SET_RH_H%10);
	lcd_wdat('%');
		lcd_wdat(' ');
		lcd_wdat(' ');
		lcd_wdat(' ');
		lcd_wdat(' ');
		lcd_wdat(' ');
}

void PRINT__RH_L(void)
{
		lcd_pos (44);
	lcd_wdat('0'+SET_RH_L/10);
	lcd_wdat('0'+SET_RH_L%10);
	lcd_wdat('%');
			lcd_wdat(' ');
		lcd_wdat(' ');
		lcd_wdat(' ');
		lcd_wdat(' ');
		lcd_wdat(' ');
}

char KEY_SCAN(void)
{
	char DATA=0;
if(KEY1==0||KEY2==0||KEY3==0||KEY4==0||KEY5==0)
{
	if(KEY1==0){while(KEY1==0);DATA= 1;}
	if(KEY2==0){while(KEY2==0);DATA= 2;}
	if(KEY3==0){while(KEY3==0);DATA= 3;}
	if(KEY4==0){while(KEY4==0);DATA= 4;}
	if(KEY5==0){while(KEY5==0);DATA= 5;}
	while(KEY1==0||KEY2==0||KEY3==0||KEY4==0||KEY5==0);
	return DATA;
}
else
	return 0;


}
//extern xdata char set_H,set_M,set_S;
void PRINT_SET_TIME_hour()
{
	static xdata char  old_time=0;
	char code Data[]={"SET TIME HOUR"};
	char xdata i;
	lcd_pos(0);
for(i=0;i<13;i++)
	lcd_wdat(Data[i]);
		switch(KEY_SCAN())
		{
			case 0:break;//无按键按下
			case 1:break;
			case 2:set_H=set_H>=23 ? 0:set_H+1;break;
			case 3:break;
			case 4:set_H=set_H<1 ? 23:set_H-1;break;
		}
		if(set_H!=old_time)//有新的设置时间
		{
			old_time=set_H;
			DS1302_SetTime(DS1302_HOUR,old_time);
			PRINT_SET_TIME_TIME();
		}
}

void PRINT_SET_TIME_minute()
{
	static xdata char  old_time=0;
	char code Data[]={"SET TIME MINUTE"};
	char xdata i;
	lcd_pos(0);
for(i=0;i<15;i++)
	lcd_wdat(Data[i]);
		switch(KEY_SCAN())
		{
			case 0:break;//无按键按下
			case 1:break;
			case 2:set_M=set_M>=59 ? 0:set_M+1;break;
			case 3:break;
			case 4:set_M=set_M<1 ? 59:set_M-1;break;
		}
		if(set_M!=old_time)//有新的设置时间
		{
			old_time=set_M;
			DS1302_SetTime(DS1302_MINUTE,set_M);
			PRINT_SET_TIME_TIME();
		}
}
void PRINT_SET_TIME_second()
{
	static xdata char  old_time=0;
	char code Data[]={"SET TIME SECOND"};
	char xdata i;
	lcd_pos(0);
for(i=0;i<15;i++)
	lcd_wdat(Data[i]);
		switch(KEY_SCAN())
		{
			case 0:break;//无按键按下
			case 1:break;
			case 2:set_S=set_S>=59 ? 0:set_S+1;break;
			case 3:break;
			case 4:set_S=set_S<1 ? 59:set_S-1;break;
		}
		if(set_S!=old_time)//有新的设置时间
		{
			old_time=set_S;
			DS1302_SetTime(DS1302_SECOND,set_S);
			PRINT_SET_TIME_TIME();
		}
}

//xdata int SET_TEMP_H,SET_TEMP_L;
void PRINT_SET_TEMP_H(void)
{
	char code Data[]={"SET Temp High"};
	char xdata i;
	lcd_pos(0);
for(i=0;i<13;i++)
	lcd_wdat(Data[i]);
		switch(KEY_SCAN())
		{
			case 0:break;//无按键按下
			case 1:break;
			case 2:SET_TEMP_H=SET_TEMP_H>=980 ? 980:SET_TEMP_H+10;break;
			case 3:break;
			case 4:SET_TEMP_H=SET_TEMP_H<30 ? 30:SET_TEMP_H-10;break;
		}
			PRINT__TEMP_H();
}

void PRINT_SET_TEMP_L(void)
{
	char code Data[]={"SET Temp Low"};
	char xdata i;
	lcd_pos(0);
for(i=0;i<12;i++)
	lcd_wdat(Data[i]);
		switch(KEY_SCAN())
		{
			case 0:break;//无按键按下
			case 1:break;
			case 2:SET_TEMP_L=SET_TEMP_L>=980 ? 980:SET_TEMP_L+10;break;
			case 3:break;
			case 4:SET_TEMP_L=SET_TEMP_L<30 ? 30:SET_TEMP_L-10;break;
		}
			PRINT__TEMP_L();
}


void PRINT_SET_RH_H(void)
{
	char code Data[]={"SET RH High"};
	char xdata i;
	lcd_pos(0);
for(i=0;i<11;i++)
	lcd_wdat(Data[i]);
		switch(KEY_SCAN())
		{
			case 0:break;//无按键按下
			case 1:break;
			case 2:SET_RH_H=SET_RH_H>=98 ? 98:SET_RH_H+1;break;
			case 3:break;
			case 4:SET_RH_H=SET_RH_H<3 ? 3:SET_RH_H-1;break;
		}
			PRINT__RH_H();
}

void PRINT_SET_RH_L(void)
{
	char code Data[]={"SET RH Low"};
	char xdata i;
	lcd_pos(0);
for(i=0;i<10;i++)
	lcd_wdat(Data[i]);
		switch(KEY_SCAN())
		{
			case 0:break;//无按键按下
			case 1:break;
			case 2:SET_RH_L=SET_RH_L>=98 ? 98:SET_RH_L+1;break;
			case 3:break;
			case 4:SET_RH_L=SET_RH_L<3 ? 3:SET_RH_L-1;break;
		}
			PRINT__RH_L();
}