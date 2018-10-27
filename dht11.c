/****
              ��ʪ��ģ��
 *************************************/


#include "dht11.h"
#include "delay.h"
#include "lcd.h"


unsigned char U8T_data_H_temp,U8T_data_L_temp,U8RH_data_H_temp,U8RH_data_L_temp,U8checkdata_temp,U8temp;
unsigned char U8T_data_H,U8T_data_L,U8RH_data_H,U8RH_data_L,U8checkdata;


/*********************************************************************************************
��������DHT11��ʼ������
��  �ã�DHT11_Rst(��
��  ������
����ֵ����
**********************************************************************************************/
void DHT11_Rst(void)	   
{                 
    DHTDAT=0; 				 //��������ʼ�ź�
    delay_ms(25);    	//����������������18ms
    DHTDAT=1; 				//������������20~40us
	delay10us();     //��������20~40us
	delay10us();
	delay10us();
}											

/*********************************************************************************************
��������DHT11��Ӧ���麯��
��  �ã�DHT11_Check(��
��  ������
����ֵ��1δ��⵽DHT11�Ĵ��ڣ�0��⵽DHT11�Ĵ���
**********************************************************************************************/
unsigned char DHT11_Check(void) 	   
{   
	unsigned char retry=0; 
  while (DHTDAT&&retry<100)//DHT11������40~80us
	{
		retry++;
		delay1us();
	} 
	if(retry>=80)return 1;
	else retry=0;
  while (!DHTDAT&&retry<100)	//DHT11���ͺ���ٴ�����40~80us
	{
		retry++;
		delay1us();
	}
	if(retry>=80)return 1;	    
	return 0;
}

/*********************************************************************************************
��������DHT11λ��ȡ����
��  �ã�DHT11_Read_Bit(����
��  ������
����ֵ��1��0
**********************************************************************************************/
unsigned char DHT11_Read_Bit(void) 			 
{
 	unsigned char retry=0;
	while(DHTDAT&&retry<100)		//�ȴ���Ϊ�͵�ƽ
	{
		retry++;
		delay1us();
	}
	retry=0;
	while(!DHTDAT&&retry<100)		//�ȴ���ߵ�ƽ
	{
		retry++;
		delay1us();
	}
	delay40us();								//�ȴ�40us(���뾫ȷ)
	if(DHTDAT)return 1;
	else return 0;		   
}

/*********************************************************************************************
��������DHT11�ֽڣ�8λ����ȡ����
��  �ã�DHT11_Read_Bit(����
��  ������
����ֵ��1��0
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
��������DHT11���ݶ�ȡ����
��  �ã�DHT11_Read_Data��
��  ����temp:�¶�ֵ(��Χ:0~50��)
				humi:ʪ��ֵ(��Χ:20%~90%)
����ֵ��1��2��ȡʧ�ܣ�0��������
**********************************************************************************************/

unsigned char DHT11_Read_Data()    
{        
// 	unsigned char buf[5];
//	unsigned char i;
	DHT11_Rst();
	if(DHT11_Check()==0)
	{
		U8RH_data_H_temp=DHT11_Read_Byte();					//��ȡ40λ����
		U8RH_data_L_temp=DHT11_Read_Byte();
		U8T_data_H_temp=DHT11_Read_Byte();
		U8T_data_L_temp=DHT11_Read_Byte();
		U8checkdata_temp=DHT11_Read_Byte();
		DHTDAT = 1;
		//����Ч��
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
����������ʼ��DHT11��IO�� DATA ͬʱ���DHT11�Ĵ���
��  �ã�DHT11_Init��
��  ����
����ֵ��1�����ڣ�0����
**********************************************************************************************/	 
unsigned char DHT11_Init(void)
{  
	 DHTDAT=1;
	 DHT11_Rst();
	 return DHT11_Check();
}

/**************************************************************************************************
��������LCD��ʾ��������һ��7~12��ʾ�¶ȣ��ڶ���7~12����ʾʪ��
��  �ã�lcdout();
��  ������
����ֵ����
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
