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
*SendDoneLed�� �������LED״̬
*����				�� ��
*����ֵ			�� ��
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
*RxLed			�� ��������LED״̬
*����				�� ��
*����ֵ			�� ��
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
*ErrorLed		�� �쳣LED״̬
*����				�� ��
*����ֵ			�� ��
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
*PowerEnableLed		�� LED��
*����							�� ��
*����ֵ						�� ��
*/
void PowerEnableLed(void)
{
	HAL_GPIO_WritePin(LORA_LED,LORA_LED_PIN,GPIO_PIN_SET);
}

/*
*PowerDisbleLed		�� LED��
*����							�� ��
*����ֵ						�� ��
*/
void PowerDisbleLed(void)
{
	HAL_GPIO_WritePin(LORA_LED,LORA_LED_PIN,GPIO_PIN_RESET);
}
