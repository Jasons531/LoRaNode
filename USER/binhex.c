/*
**************************************************************************************************************
*	@file		BinHex.c
*	@author 	Jason.Yan
*	@version 	V0.1
*	@date     
*	@brief		Ӧ�ò�ͷ�ļ�������MAC��
* @connect		Jason_531@163.com
***************************************************************************************************************
*/
#include "binhex.h"

char String_Buffer[33] = {0}; ///��ȡflashд���ַ���

int PowerXY(int x, int y)
{
	if(y == 0)
	return 1 ;
	else
	return x * PowerXY(x, y -1 ) ;
}

/*!
*Convert16To10��16����ת��Ϊ10����
*����ֵ: 		    10������ֵ
*/
int Convert16To10(int number)
{
	int r = 0 ;
	int i = 0 ;
	int result = 0 ;
	while(number)
	{
		r = number % 16 ;
		result += r * PowerXY(16, i++) ;
		number /= 16 ;
	}
	return result ;
}

/*!
*Read_DecNumber���ַ����е�����ת��Ϊ10����
*����ֵ: 		     10������ֵ
*/
uint32_t ReadDecNumber(char *str)
{
	uint32_t value;

	if (! str)
	{
			return 0;
	}
	value = 0;
	while ((*str >= '0') && (*str <= '9'))
	{
			value = value*10 + (*str - '0');
			str++;
	}
	return value;
}

/*!
*String_Conversion���ַ���ת��Ϊ16����
*����ֵ: 		        ��
*/
void StringConversion(char *str, uint8_t *src, uint8_t len)
{
 volatile int i,v;
			
	for(i=0; i<len/2; i++)
 {
		sscanf(str+i*2,"%2X",&v);
		src[i]=(uint8_t)v;
	}
}
