#include "reg51.h"
#include "timer.h"
sbit BEEP=P0^0;
sbit K1=P1^1;
sbit K2=P1^0;
sbit K3=P1^2;
sbit K4=P1^3;
sbit K5=P1^4;
extern xdata int REAL_TEMP,REAL_RH;
extern char work_mode;
extern char SET_TIME_MODE,SET_TEMP_MODE,SET_RH_MODE;
extern char KEY_SCAN(void);
void TIMER_Init(void)
{
    TMOD = 0x01;
    TH0 = 0x0D8;
    TL0 = 0x0F0;
    EA = 1;
    ET0 = 1;
    TR0 = 1;
}
extern xdata int SET_TEMP_H,SET_TEMP_L;//温度高低限制
extern xdata int SET_RH_H,SET_RH_L;
//xdata int REAL_TEMP,REAL_RH;
void Timer0Interrupt(void) interrupt 1//0.1毫秒
{
	static unsigned int t=0,first=0; 
    TH0 = 0x0D8;
    TL0 = 0x0F0;
	t++;
	if(t>=100)//10ms
	{
		t=0;
		if(work_mode==0)
		{
					
			if( REAL_TEMP*10<=SET_TEMP_H && REAL_TEMP*10>=SET_TEMP_L && REAL_RH<=SET_RH_H&& REAL_RH>=SET_RH_L)
			BEEP=1;
			else
			BEEP=0;
			if(first==0)
			{LCD_1602_Init();first=1;}
			Print_Time();
			Get_TEMP();
		}
		else
			first=0; 
		
		

		
			
			
	}
	if(KEY_SCAN!=0)//有按键按下
	{
		if(K1==0){while(K1==0);work_mode=work_mode>=3? 0:work_mode+1;SET_TIME_MODE=1;SET_TEMP_MODE=1;SET_RH_MODE=1;LCD_1602_Init();}
		if(K5==0 && work_mode==1){while(K5==0);SET_TIME_MODE=SET_TIME_MODE>3? 0:SET_TIME_MODE+1;}
		if(K5==0 && work_mode==2){while(K5==0);SET_TEMP_MODE=SET_TEMP_MODE>2? 0:SET_TEMP_MODE+1;}
		if(K5==0 && work_mode==3){while(K5==0);SET_RH_MODE=SET_RH_MODE>2? 0:SET_RH_MODE+1;}
	}
}