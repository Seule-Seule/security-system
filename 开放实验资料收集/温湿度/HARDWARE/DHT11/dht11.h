#ifndef __DHT11_H
#define __DHT11_H
#define uchar unsigned char
#define uint unsigned int
#define Data_0_time 4
//#define U8 unsigned char
typedef unsigned char U8; /* defined for unsigned 8-bits integer variable 无符号8位整型变量 */
typedef signed char S8; /* defined for signed 8-bits integer variable 有符号8位整型变量 */
typedef unsigned int U16; /* defined for unsigned 16-bits integer variable 无符号16位整型变量 */
typedef signed int S16; /* defined for signed 16-bits integer variable 有符号16位整型变量 */
typedef unsigned long U32; /* defined for unsigned 32-bits integer variable 无符号32位整型变量 */
typedef signed long S32; /* defined for signed 32-bits integer variable 有符号32位整型变量 */
typedef float F32; /* single precision floating point variable (32bits) 单精度浮点数（32位长度） */
typedef double F64; /* double precision floating point variable (64bits) 双精度浮点数（64位长度） */




//sbit P2_1 = P2^1 ;
//sbit P2_2 = P2^2 ;
//sbit P2_3 = P2^3 ;

void Delay_DHT11(U16 j);
void Delay_10us(void);
void COM(void);
void Get_TEMP(void);

#endif