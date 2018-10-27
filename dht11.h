/***************************

温度湿度传感器定义头函数


***************************/
#include <reg51.h>
//#define uchar unsigned char
//#define uint unsigned int

//管脚定义
sbit DHTDAT = P2^0;


void DHT11_Rst(void);     //DHT11初始化函数

unsigned char DHT11_Check(void);  //DHT11响应检验函数

unsigned char DHT11_Read_Bit(void);  //DHT11位读取函数

unsigned char DHT11_Read_Byte(void);  //DHT11字节（8位）读取函数

unsigned char DHT11_Read_Data();  //DHT11数据读取函数

unsigned char DHT11_Init(void);   //初始化DHT11的IO口 DATA 同时检测DHT11的存在

unsigned char lcdout();//显示函数
