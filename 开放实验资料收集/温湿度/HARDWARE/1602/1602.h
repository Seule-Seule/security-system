#ifndef __1602_H
#define __1602_H
typedef unsigned char BYTE;
typedef unsigned int WORD;
typedef bit BOOL;
void LCD_1602_Init(void);
void lcd_pos(BYTE pos);
void lcd_wdat(BYTE dat);
void delay (int m);
void Print_Temp(int Set_temp,int Real_temp);
void PRINT_SET_TIME_hour(void);
void PRINT_SET_TIME_minute(void);
void PRINT_SET_TIME_second(void);
#endif