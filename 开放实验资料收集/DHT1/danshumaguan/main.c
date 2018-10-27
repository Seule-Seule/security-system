#include "STC15.h"
#include "stdio.h"
#include "Delay.h"
#include "uart.h"
#include "dht11.h"
unsigned char temp[2],humi[2];
unsigned char flag;
unsigned char code Num[16]={0x3F,
0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,
0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};
int m,n,p,q;
long int i;

void main(void)
{
	P0M1 = 0;	P0M0 = 0;	//����Ϊ׼˫���
	P1M1 = 0;	P1M0 = 1;	//����Ϊ׼˫���
	P2M1 = 0;	P2M0 = 1;	//����Ϊ׼˫���
	P3M1 = 0;	P3M0 = 0;	//����Ϊ׼˫���
	P4M1 = 0;	P4M0 = 0;	//����Ϊ׼˫���
	P5M1 = 0;	P5M0 = 0;	//����Ϊ׼˫���
	P6M1 = 0;	P6M0 = 0;	//����Ϊ׼˫���
	P7M1 = 0;	P7M0 = 0;	//����Ϊ׼˫���
	
	while(1)
	{
		flag=DHT11_Read_Data(temp,humi);
		if(flag==0)				//��ȡ�ɹ�
		{
			m=(int)temp[0]/10;
			n=(int)temp[0]%10;
			p=(int)temp[1]/10;
			i=100;
			
			if(temp[0]>50||humi[0]>90)
			{
				P24=1;
			}
			else P24=0;
			
			while(i--)
			{
				P23=1;
				P1=~Num[12];
				delay_ms(10);
				P23=0;
				P20=1;//P20ʮλ����
				P1=~Num[m];//P1��ʾ
				Delay1ms();
				P20=0;
				P21=1;//P21��λ����
				P1=~(Num[n]+0x80);
				delay_ms(10);
				P21=0;
				P22=1;//P22ʮ��λ����
				P1=~Num[p];
				delay_ms(10);
				P22=0;
			}
			
			m=(int)humi[0]/10;
			n=(int)humi[0]%10;
			p=(int)humi[1]/10;
			q=(int)humi[1]%10;
			i=100;
			while(i--)
			{
				P20=1;//P20ʮλ����
				P1=~Num[m];//P1��ʾ
				Delay1ms();
				P20=0;
				P21=1;//P21��λ����
				P1=~(Num[n]+0x80);
				delay_ms(10);
				P21=0;
				P22=1;//P22ʮ��λ����
				P1=~Num[p];
				delay_ms(10);
				P22=0;
				P23=1;//P23�ٷ�λ����
				P1=~Num[q];
				delay_ms(10);
				P23=0;
			}
		}
	}
}

