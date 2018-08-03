/*
**************************************************************************************************************
*	@file		BinHex.c
*	@author 	Jason.Yan
*	@version 	V0.1
*	@date     
*	@brief		应用层头文件：连接MAC层
* @connect		Jason_531@163.com
***************************************************************************************************************
*/

#ifndef __BINHEX__H
#define __BINHEX__H

#include <stdint.h>
#include <stdio.h>

extern char String_Buffer[33];

int PowerXY(int x, int y);

int Convert16To10(int number);

uint32_t ReadDecNumber(char *str);

void StringConversion(char *str, uint8_t *src, uint8_t len);


#endif //__BINHEX__H
