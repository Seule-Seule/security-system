/***************************

�¶�ʪ�ȴ���������ͷ����


***************************/
#include <reg51.h>
//#define uchar unsigned char
//#define uint unsigned int

//�ܽŶ���
sbit DHTDAT = P2^0;


void DHT11_Rst(void);     //DHT11��ʼ������

unsigned char DHT11_Check(void);  //DHT11��Ӧ���麯��

unsigned char DHT11_Read_Bit(void);  //DHT11λ��ȡ����

unsigned char DHT11_Read_Byte(void);  //DHT11�ֽڣ�8λ����ȡ����

unsigned char DHT11_Read_Data();  //DHT11���ݶ�ȡ����

unsigned char DHT11_Init(void);   //��ʼ��DHT11��IO�� DATA ͬʱ���DHT11�Ĵ���

unsigned char lcdout();//��ʾ����
