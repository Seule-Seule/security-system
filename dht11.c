/****
              温湿度模块
 *************************************/


#include "dht11.h"
#include "delay.h"
#include "lcd.h"


unsigned char U8T_data_H_temp,U8T_data_L_temp,U8RH_data_H_temp,U8RH_data_L_temp,U8checkdata_temp,U8temp;
unsigned char U8T_data_H,U8T_data_L,U8RH_data_H,U8RH_data_L,U8checkdata;


/*********************************************************************************************
函数名：DHT11初始化函数
调  用：DHT11_Rst(）
参  数：无
返回值：无
**********************************************************************************************/
void DHT11_Rst(void)	   
{                 
    DHTDAT=0; 				 //主机发起始信号
    delay_ms(25);    	//主机拉低总线至少18ms
    DHTDAT=1; 				//主机拉高总线20~40us
	delay10us();     //主机拉高20~40us
	delay10us();
	delay10us();
}											

/*********************************************************************************************
函数名：DHT11响应检验函数
调  用：DHT11_Check(）
参  数：无
返回值：1未检测到DHT11的存在；0检测到DHT11的存在
**********************************************************************************************/
unsigned char DHT11_Check(void) 	   
{   
	unsigned char retry=0; 
  while (DHTDAT&&retry<100)//DHT11会拉低40~80us
	{
		retry++;
		delay1us();
	} 
	if(retry>=80)return 1;
	else retry=0;
  while (!DHTDAT&&retry<100)	//DHT11拉低后会再次拉高40~80us
	{
		retry++;
		delay1us();
	}
	if(retry>=80)return 1;	    
	return 0;
}

/*********************************************************************************************
函数名：DHT11位读取函数
调  用：DHT11_Read_Bit(）；
参  数：无
返回值：1，0
**********************************************************************************************/
unsigned char DHT11_Read_Bit(void) 			 
{
 	unsigned char retry=0;
	while(DHTDAT&&retry<100)		//等待变为低电平
	{
		retry++;
		delay1us();
	}
	retry=0;
	while(!DHTDAT&&retry<100)		//等待变高电平
	{
		retry++;
		delay1us();
	}
	delay40us();								//等待40us(必须精确)
	if(DHTDAT)return 1;
	else return 0;		   
}

/*********************************************************************************************
函数名：DHT11字节（8位）读取函数
调  用：DHT11_Read_Bit(）；
参  数：无
返回值：1，0
**********************************************************************************************/
unsigned char DHT11_Read_Byte(void)    
{        
    unsigned char i,dat;
    dat=0;
	for (i=0;i<8;i++) 
	{
   		dat<<=1; 
	    dat|=DHT11_Read_Bit();
    }						    
    return dat;
}

/*********************************************************************************************
函数名：DHT11数据读取函数
调  用：DHT11_Read_Data；
参  数：temp:温度值(范围:0~50°)
				humi:湿度值(范围:20%~90%)
返回值：1，2读取失败，0数据正常
**********************************************************************************************/

unsigned char DHT11_Read_Data()    
{        
// 	unsigned char buf[5];
//	unsigned char i;
	DHT11_Rst();
	if(DHT11_Check()==0)
	{
		U8RH_data_H_temp=DHT11_Read_Byte();					//读取40位数据
		U8RH_data_L_temp=DHT11_Read_Byte();
		U8T_data_H_temp=DHT11_Read_Byte();
		U8T_data_L_temp=DHT11_Read_Byte();
		U8checkdata_temp=DHT11_Read_Byte();
		DHTDAT = 1;
		//数据效验
		U8temp=(U8T_data_H_temp+U8T_data_L_temp+U8RH_data_H_temp+U8RH_data_L_temp);
		if(U8temp==U8checkdata_temp)
		{
		U8RH_data_H=U8RH_data_H_temp;
		U8RH_data_L=U8RH_data_L_temp;
		U8T_data_H=U8T_data_H_temp;
		U8T_data_L=U8T_data_L_temp;
		U8checkdata=U8checkdata_temp;
		} else return 1;
	} 
	else return 2;  
	return 0; 
} 

/*********************************************************************************************
函数名：初始化DHT11的IO口 DATA 同时检测DHT11的存在
调  用：DHT11_Init；
参  数：
返回值：1不存在，0存在
**********************************************************************************************/	 
unsigned char DHT11_Init(void)
{  
	 DHTDAT=1;
	 DHT11_Rst();
	 return DHT11_Check();
}

/**************************************************************************************************
函数命：LCD显示函数，第一行7~12显示温度，第二行7~12行显示湿度
调  用：lcdout();
参  数：无
返回值：无
*******************************************************************************************************/
unsigned char lcdout()
{
	DHT11_Read_Data();
	 LcdSetCursor(2,0);
	  Lcd1602_Write_Data('0'+(U8T_data_H/10)%10);
	   Lcd1602_Write_Data('0'+U8T_data_H%10);
	    Lcd1602_Write_Data('.');
	     Lcd1602_Write_Data('0'+U8T_data_L%10);
	      Lcd1602_Write_Data('C');
	 LcdSetCursor(11,0);
	  Lcd1602_Write_Data('0'+(U8RH_data_H/10)%10);
	   Lcd1602_Write_Data('0'+U8RH_data_H%10);
	    Lcd1602_Write_Data('.');
	     Lcd1602_Write_Data('0'+U8RH_data_L%10);
	      Lcd1602_Write_Data('%');
   	if((U8T_data_H > 50)||(U8RH_data_H > 90))
   		return 0;
	return 1;
}
