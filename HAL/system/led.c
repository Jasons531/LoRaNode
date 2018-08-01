/*
**************************************************************************************************************
*	@file			LED.c
*	@author 	Jason.Yan
*	@version  V0.1
*	@date     2018/07/24
*	@brief	
* @connect  Jason_531@163.com
***************************************************************************************************************
*/

#include "led.h"

/*
*SendDoneLed： 发送完成LED状态
*参数				： 无
*返回值			： 无
*/
void SendDoneLed(void)
{
	for(uint8_t i = 0; i < 5; i++)
	{
		HAL_GPIO_WritePin(LORA_LED,LORA_LED_PIN,GPIO_PIN_SET);
		delay_ms(50);
		HAL_GPIO_WritePin(LORA_LED,LORA_LED_PIN,GPIO_PIN_RESET);
		delay_ms(50);
	}
}

/*
*RxLed			： 接收数据LED状态
*参数				： 无
*返回值			： 无
*/
void RxLed(void)
{
	for(uint8_t i = 0; i < 5; i++)
	{
		HAL_GPIO_WritePin(LORA_LED,LORA_LED_PIN,GPIO_PIN_SET);
		delay_ms(50);
		HAL_GPIO_WritePin(LORA_LED,LORA_LED_PIN,GPIO_PIN_RESET);
		delay_ms(50);
	}
}

/*
*ErrorLed		： 异常LED状态
*参数				： 无
*返回值			： 无
*/
void ErrorLed(void)
{
	for(uint8_t i = 0; i < 3; i++)
	{
		HAL_GPIO_WritePin(LORA_LED,LORA_LED_PIN,GPIO_PIN_SET);
		delay_ms(1000);
		HAL_GPIO_WritePin(LORA_LED,LORA_LED_PIN,GPIO_PIN_RESET);
		delay_ms(200);
	}
}

/*
*PowerEnableLed		： LED亮
*参数							： 无
*返回值						： 无
*/
void PowerEnableLed(void)
{
	HAL_GPIO_WritePin(LORA_LED,LORA_LED_PIN,GPIO_PIN_SET);
}

/*
*PowerDisbleLed		： LED灭
*参数							： 无
*返回值						： 无
*/
void PowerDisbleLed(void)
{
	HAL_GPIO_WritePin(LORA_LED,LORA_LED_PIN,GPIO_PIN_RESET);
}
