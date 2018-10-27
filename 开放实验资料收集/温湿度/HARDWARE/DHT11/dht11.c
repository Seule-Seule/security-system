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
		//��ʱ������forѭ��
		if(U8FLAG==1)break;
		//�ж�����λ��0����1
		// ����ߵ�ƽ�߹�Ԥ��0�ߵ�ƽֵ������λΪ 1
		U8comdata<<=1;
		U8comdata|=U8temp; //0
	}//rof
}
//------------ --------------------
//-----ʪ�ȶ�ȡ�ӳ��� ------------
//---------------------- ----------
//----���±�����Ϊȫ�ֱ���--------
//----�¶ȸ�8λ== U8T_data_H------
//----�¶ȵ�8λ== U8T_data_L------
//----ʪ�ȸ�8λ== U8RH_data_H-----
//----ʪ�ȵ�8λ== U8RH_data_L-----
//----У�� 8λ == U8checkdata-----
//----��������ӳ�������----------
//---- Delay();, Delay_10us();COM();
//--------------------- -----------
void RH(void)
{
	//��������18ms
	DHT11_DATA=0;
	Delay_DHT11(180);
	DHT11_DATA=1;
	//������������������ ������ʱ20us
	Delay_10us();
	Delay_10us();
	Delay_10us();
	Delay_10us();
	//������Ϊ���� �жϴӻ���Ӧ�ź�
	DHT11_DATA=1;
	//�жϴӻ��Ƿ��е͵�ƽ��Ӧ�ź� �粻��Ӧ����������Ӧ����������
	if(!DHT11_DATA) //T !
	{
	U8FLAG=2;
	//�жϴӻ��Ƿ񷢳� 80us �ĵ͵�ƽ��Ӧ�ź��Ƿ����
	while((!DHT11_DATA)&&U8FLAG++);
	U8FLAG=2;
	//�жϴӻ��Ƿ񷢳� 80us �ĸߵ�ƽ���緢����������ݽ���״̬
	while((DHT11_DATA)&&U8FLAG++);
	//���ݽ���״̬
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
	//����У��
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
