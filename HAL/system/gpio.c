/*
**************************************************************************************************************
*	@file			gpio.c
*	@author 	Jason.Yan
*	@version  V0.1
*	@date     2018/07/24
*	@brief	
* @connect  Jason_531@163.com
***************************************************************************************************************
*/
#include "gpio.h"

/**
  * @brief GPIO初始化
  * @param SX1276 RESET引脚初始化---PB0  
  * @retval None
  */
void SX1276GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_Initure;
	__HAL_RCC_GPIOB_CLK_ENABLE();           

	GPIO_Initure.Pin=LORA_REST_PIN;  
	GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  
	GPIO_Initure.Pull=GPIO_NOPULL; 
	GPIO_Initure.Speed=GPIO_SPEED_HIGH;     
	HAL_GPIO_Init(LORA_IO,&GPIO_Initure);

	HAL_GPIO_WritePin(LORA_IO,LORA_REST_PIN,GPIO_PIN_SET);	
}

/**
  * @brief GPIO初始化
  * @param  LoRa电源控制 
  * @retval None
  */
void LoRaPower_Init(void)
{
	GPIO_InitTypeDef GPIO_Initure;
	__HAL_RCC_GPIOB_CLK_ENABLE();           
	__HAL_RCC_GPIOA_CLK_ENABLE();

	GPIO_Initure.Pin=LORA_POWER_ON;  
	GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;
	GPIO_Initure.Pull=GPIO_NOPULL;
	GPIO_Initure.Speed=GPIO_SPEED_HIGH;     
	HAL_GPIO_Init(LORA_IO,&GPIO_Initure);
	
	GPIO_Initure.Pin=LORA_LED_PIN;    
	GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  
	GPIO_Initure.Pull=GPIO_NOPULL;
	GPIO_Initure.Speed=GPIO_SPEED_HIGH;     
	
	HAL_GPIO_Init(LORA_LED,&GPIO_Initure);

	HAL_GPIO_WritePin(LORA_LED,LORA_LED_PIN,GPIO_PIN_RESET);	
	HAL_GPIO_WritePin(LORA_IO,LORA_POWER_ON,GPIO_PIN_SET);	
}

/**
  * @brief 外部中断初始化
  * @param huart: DIO0--PB1   DIO1--PB2   DIO2--PB10   DIO3--PB11   
  * @retval None
  */
void SX1276EXTI_Init(void)
{
	GPIO_InitTypeDef GPIO_Initure;
	
	__HAL_RCC_GPIOB_CLK_ENABLE();               		 

	GPIO_Initure.Pin=LORA_DIO0|LORA_DIO1|LORA_DIO2|LORA_DIO3;  
	GPIO_Initure.Mode=GPIO_MODE_IT_RISING;      			
	GPIO_Initure.Pull=GPIO_PULLDOWN;
	HAL_GPIO_Init(GPIOB,&GPIO_Initure);
			
	//中断线2-PC2
	HAL_NVIC_SetPriority(EXTI0_1_IRQn,5,0);       //5,0
	HAL_NVIC_EnableIRQ(EXTI0_1_IRQn);             
	
	//中断线3-PC3
	HAL_NVIC_SetPriority(EXTI2_3_IRQn,6,0);       
	HAL_NVIC_EnableIRQ(EXTI2_3_IRQn);           
	
	//中断线4-PC15
	HAL_NVIC_SetPriority(EXTI4_15_IRQn,7,0);      
	HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);            
}


void GpioWrite( GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState )
{
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin,  PinState);
}

void GpioToggle( GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin )
{
  HAL_GPIO_TogglePin(GPIOx,  GPIO_Pin);   
}

uint32_t GpioRead( GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin )
{
	return HAL_GPIO_ReadPin(GPIOx, GPIO_Pin);
}
