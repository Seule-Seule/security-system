#include <reg51.h>
#include <intrins.h>
#include "dht11.h"
#include "1602.h"
xdata int REAL_TEMP=25,REAL_RH=30;
U8 U8FLAG,k;
U8 U8count,U8temp;
U8 U8T_data_H,U8T_data_L,U8RH_data_H,U8RH_data_L,U8checkdata;
U8 U8T_data_H_temp,U8T_data_L_temp,U8RH_data_H_temp,U8RH_data_L_temp,U8checkdata_temp;
U8 U8comdata;
U8 count, count_r=0;
U16 U16temp1,U16temp2;
sbit DHT11_DATA = P0^1;//DATA
void Delay_DHT11(U16 j)
{ 
	U8 i;
	for(;j>0;j--)
	{
	for(i=0;i<27;i++);
	}
}

void Delay_10us(void)
{
	U8 i;
	i--;
	i--;
	i--;
	i--;
	i--;
	i--;
}

void COM(void)
{
	U8 i;
	for(i=0;i<8;i++)
	{
		U8FLAG=2;
		//----------------------
//		P2_1=0 ; //T
//		P2_1=1 ; //T
		//----------------------
		while((!DHT11_DATA)&&U8FLAG++);
		Delay_10us();
		Delay_10us();
		// Delay_10us();
		U8temp=0;
		if(DHT11_DATA)U8temp=1;
		U8FLAG=2;
		while((DHT11_DATA)&&U8FLAG++);
		//----------------------
//		P2_1=0 ; //T
//		P2_1=1 ; //T
		//----------------------
		//超时则跳出for循环
		if(U8FLAG==1)break;
		//判断数据位是0还是1
		// 如果高电平高过预定0高电平值则数据位为 1
		U8comdata<<=1;
		U8comdata|=U8temp; //0
	}//rof
}
//------------ --------------------
//-----湿度读取子程序 ------------
//---------------------- ----------
//----以下变量均为全局变量--------
//----温度高8位== U8T_data_H------
//----温度低8位== U8T_data_L------
//----湿度高8位== U8RH_data_H-----
//----湿度低8位== U8RH_data_L-----
//----校验 8位 == U8checkdata-----
//----调用相关子程序如下----------
//---- Delay();, Delay_10us();COM();
//--------------------- -----------
void RH(void)
{
	//主机拉低18ms
	DHT11_DATA=0;
	Delay_DHT11(180);
	DHT11_DATA=1;
	//总线由上拉电阻拉高 主机延时20us
	Delay_10us();
	Delay_10us();
	Delay_10us();
	Delay_10us();
	//主机设为输入 判断从机响应信号
	DHT11_DATA=1;
	//判断从机是否有低电平响应信号 如不响应则跳出，响应则向下运行
	if(!DHT11_DATA) //T !
	{
	U8FLAG=2;
	//判断从机是否发出 80us 的低电平响应信号是否结束
	while((!DHT11_DATA)&&U8FLAG++);
	U8FLAG=2;
	//判断从机是否发出 80us 的高电平，如发出则进入数据接收状态
	while((DHT11_DATA)&&U8FLAG++);
	//数据接收状态
	COM();
	U8RH_data_H_temp=U8comdata;
	COM();
	U8RH_data_L_temp=U8comdata;
	COM();
	U8T_data_H_temp=U8comdata;
	COM();
	U8T_data_L_temp=U8comdata;
	COM();
	U8checkdata_temp=U8comdata;
	DHT11_DATA=1;
	//数据校验
	U8temp=(U8T_data_H_temp+U8T_data_L_temp+U8RH_data_H_temp+U8RH_data_L_temp);
	if(U8temp==U8checkdata_temp)
	{
		U8RH_data_H=U8RH_data_H_temp;
		U8RH_data_L=U8RH_data_L_temp;
		U8T_data_H=U8T_data_H_temp;
		U8T_data_L=U8T_data_L_temp;
		U8checkdata=U8checkdata_temp;
	}//fi
	}//fi
}
//xdata int REAL_TEMP,REAL_RH;
void Get_TEMP(void)
{
	RH();
	REAL_TEMP=U8T_data_H;
	REAL_RH  =U8RH_data_H;
		lcd_pos(40);
	lcd_wdat('T');lcd_wdat(':');
lcd_wdat('0'+(U8T_data_H/10)%10);
	lcd_wdat('0'+U8T_data_H%10);
	lcd_wdat('.');
	lcd_wdat('0'+U8T_data_L%10);
	lcd_wdat('C');lcd_wdat(' ');
	lcd_wdat('R');lcd_wdat('H');lcd_wdat(':');

lcd_wdat('0'+(U8RH_data_H/10)%10);
	lcd_wdat('0'+U8RH_data_H%10);
		
	lcd_wdat('.');
	lcd_wdat('0'+U8RH_data_L%10);
	lcd_wdat('%');lcd_wdat(' ');


}
