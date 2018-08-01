/*
**************************************************************************************************************
*	@file			led.h
*	@author 	Jason.Yan
*	@version  V0.1
*	@date     2018/07/24
*	@brief	
* @connect  Jason_531@163.com
***************************************************************************************************************
*/
#ifndef __LED_H
#define __LED_H

#include "gpio.h"

void SendDoneLed(void);
void RxLed(void);
void ErrorLed(void);
void PowerEnableLed(void);
void PowerDisbleLed(void);

#endif

