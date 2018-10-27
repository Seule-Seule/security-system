#ifndef __DHT11_H
#define __DHT11_H 
#include "STC15.h"   

sbit DHTDAT=P0^0;

unsigned char DHT11_Init(void);																						//初始化DHT11
unsigned char DHT11_Read_Data(unsigned char *temp,unsigned char *humi);	//读取温湿度
unsigned char DHT11_Read_Data_num(unsigned char *temp_num,unsigned char *humi_num)  ; //小数部分
unsigned char DHT11_Read_Byte(void);																			//读出一个字节
unsigned char DHT11_Read_Bit(void);																				//读出一个位
unsigned char DHT11_Check(void);																					//检测是否存在DHT11
void DHT11_Rst(void);																											//复位DHT11    
#endif















