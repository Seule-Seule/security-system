#ifndef __DHT11_H
#define __DHT11_H 
#include "STC15.h"   

sbit DHTDAT=P0^0;

unsigned char DHT11_Init(void);																						//��ʼ��DHT11
unsigned char DHT11_Read_Data(unsigned char *temp,unsigned char *humi);	//��ȡ��ʪ��
unsigned char DHT11_Read_Data_num(unsigned char *temp_num,unsigned char *humi_num)  ; //С������
unsigned char DHT11_Read_Byte(void);																			//����һ���ֽ�
unsigned char DHT11_Read_Bit(void);																				//����һ��λ
unsigned char DHT11_Check(void);																					//����Ƿ����DHT11
void DHT11_Rst(void);																											//��λDHT11    
#endif















