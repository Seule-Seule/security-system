#include "intrins.h"
/***********************************************************
 *					��ʱ����
 * 		  �����徧����12MHZ�ģ�ÿ����������1us
 *		   40us����DHT11ͨѶ����Ҫ��ȷ
*************************************************************/

#define delay1us()	_nop_();_nop_()        //��ʱ2us
void delay10us();							//��ʱ10us
void delay1ms();							//��ʱ1ms
void delay_ms(unsigned short s);			 //��ʱs ms
void delay40us();							 //��ʱ40us