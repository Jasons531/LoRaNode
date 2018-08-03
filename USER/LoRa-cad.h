/*
**************************************************************************************************************
*	@file	LoRa-cad.h
*	@author Jason_531@163.com
*	@version 
*	@date    
*	@brief	Ӧ�ò�ͷ�ļ�������MAC��
***************************************************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LORA_CAD_H
#define __LORA_CAD_H

/* Includes ------------------------------------------------------------------*/
#include "board.h"
#include <stdio.h>
#include <stdint.h>

extern uint32_t RfSend_time;

#define SLEEPTIME						1000
#define PROTECTIME					100

#define PREAMBLETIME				(SLEEPTIME+PROTECTIME)

typedef struct LoRaCsmas
{
	bool 			Iq_Invert;///node to node 
	bool 			Listen;   ///������־
	bool 			Ack;   ///���ݹ���

	uint8_t  	DisturbCounter; ///��������
	uint8_t  	retry;          ///����������
	float   	SymbolTime;     ///preamblelen time
	uint32_t  CadTime;
}LoRaCsma_t;

typedef struct //sLoRaMacCsma
{
	void 	( *ChannelAddFun )(void);
	float ( *SymbolTime )(void);	
	void 	( *ListenAagain )(void);
	void 	( *CadMode )(void);
	void  ( *CadTime )(void);
}LoRaMacCsma_t;

extern LoRaCsma_t Csma;
extern const LoRaMacCsma_t LoRaMacCsma;

extern uint8_t Channel; ///�ŵ���

extern TimerEvent_t CsmaTimer;

void OnCsmaTimerEvent( void );

void LoRaChannelAddFun( void );

void LoRaCadMode( void );

float LoRaSymbolTime( void );

void LoRaListenAagain( void );

void LoRaCadTime(void);

#endif /* __LoRa-cad_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
