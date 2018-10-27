//////////////////////////////////////////////
//      ����stc89c52�İ���ϵͳ
//      �Կ�1702��--�����
//       2018-10-17
/////////////////////////////////////////////
//		LCD1602���ߣ�
//          P0--��������
//          RS--P2^6
//          RW--P2^5
//          EN--P2^7	
//		DHT11���ߣ�
//			DHT11--P2^0
//		������ģ�飺	
//			Beep--P2^1 
//      ���洫������
//			flame--P2^2
//      ����������
//          mq-2--P2^3
//      ������⴫������
//          hr-sr--P3^7
///////////////////////////////////////////////

//�ļ�����

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


uchar dht11_chec = 1;  //dht11���λ
uchar dht11_chec2 = 1;	//dht11����λ
uchar flame_check = 1;  //���洫�������λ
uchar mq_check = 1;		//�����������λ
uchar hr_sr_check = 1;  //���������λ


void main()
{
	InitLcd1602();              //1602��ʼ��
	DHT11_Init();              //DHT11��ʼ��
	delay_ms(1100);			   //�ϵ���ͣ1�룬�ȴ�DHT�������
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