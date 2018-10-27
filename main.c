//////////////////////////////////////////////
//      基于stc89c52的安防系统
//      自控1702班--泛玉成
//       2018-10-17
/////////////////////////////////////////////
//		LCD1602接线：
//          P0--数据总线
//          RS--P2^6
//          RW--P2^5
//          EN--P2^7	
//		DHT11接线：
//			DHT11--P2^0
//		蜂鸣器模块：	
//			Beep--P2^1 
//      火焰传感器：
//			flame--P2^2
//      烟雾传感器：
//          mq-2--P2^3
//      人体红外传感器：
//          hr-sr--P3^7
///////////////////////////////////////////////

//文件包含

#include "lcd.h"
#include "reg51.h"
#include "dht11.h"
#include "delay.h"
#include "flame.h"
#include "MQ-2.h"
#include "beep.h"
#include "hr-sr.h"


uchar code  tem[3] = "T:"  ;
uchar code  hum[3] = "H:" ;
uchar code  fire[] = "FIRE!";
uchar code  smoky[] = "SMOKY!";
uchar code  stranger[] = "STRANGER!";


uchar dht11_chec = 1;  //dht11检测位
uchar dht11_chec2 = 1;	//dht11报警位
uchar flame_check = 1;  //火焰传感器检测位
uchar mq_check = 1;		//烟雾报警器检测位
uchar hr_sr_check = 1;  //人体红外检测位


void main()
{
	InitLcd1602();              //1602初始化
	DHT11_Init();              //DHT11初始化
	delay_ms(1100);			   //上电暂停1秒，等待DHT测试完成
	while(1)
	{
		LcdShowStr(0,0,tem);
		LcdShowStr(9,0,hum);
		dht11_chec = DHT11_Read_Data();
	  	if(dht11_chec == 0)
	   	{	
			uchar i;
			dht11_chec2 = lcdout();
			if(dht11_chec2 == 0)
			for(i = 0;i<4;i++) 	bep();	
		}
		flame_check = flame_read();	
		if(flame_check == 0)
		{
			uchar i;
			LcdShowStr(2,1,fire);
			for(i = 0;i < 3;i++)
				bep();
			Lcd1602_Write_Cmd(0x01);
		} 
		mq_check = mq_2();
		if(mq == 0)
		{
			uchar i;
			LcdShowStr(2,1,smoky);
			for(i = 0;i < 2;i++)
				bep();
			Lcd1602_Write_Cmd(0x01);
		}
		hr_sr_check = hr_sr();
		if(hr_sr_check == 0)
		{
			uchar i;
			LcdShowStr(2,1,stranger);
			for(i = 0;i < 5;i++)
				bep();
			Lcd1602_Write_Cmd(0x01);
		}  				 	  
	}		 
}