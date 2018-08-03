/*
**************************************************************************************************************
*	@file			LoRa-cad.c
*	@author 	Jason.Yan
*	@version 	V0.1
*	@date     
*	@brief		Ӧ�ò�ͷ�ļ�������MAC��
* @connect	Jason_531@163.com
***************************************************************************************************************
*/
/* Includes ------------------------------------------------------------------*/
#include "board.h"
#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include "LoRa-cad.h"

/******************************32·ѡ��**************************************/
#define LC4                { 470900000, { ( ( DR_5 << 4 ) | DR_0 ) }, 0 }
#define LC5                { 471100000, { ( ( DR_5 << 4 ) | DR_0 ) }, 0 }
#define LC6                { 471300000, { ( ( DR_5 << 4 ) | DR_0 ) }, 0 }
#define LC7                { 471500000, { ( ( DR_5 << 4 ) | DR_0 ) }, 0 }
#define LC8                { 471700000, { ( ( DR_5 << 4 ) | DR_0 ) }, 0 }

#define LC9                { 471900000, { ( ( DR_5 << 4 ) | DR_0 ) }, 0 }
#define LC10               { 472100000, { ( ( DR_5 << 4 ) | DR_0 ) }, 0 }
#define LC11               { 472300000, { ( ( DR_5 << 4 ) | DR_0 ) }, 0 }
#define LC12               { 472500000, { ( ( DR_5 << 4 ) | DR_0 ) }, 0 }
#define LC13               { 472700000, { ( ( DR_5 << 4 ) | DR_0 ) }, 0 }
#define LC14               { 472900000, { ( ( DR_5 << 4 ) | DR_0 ) }, 0 }
#define LC15               { 473100000, { ( ( DR_5 << 4 ) | DR_0 ) }, 0 }
#define LC16               { 473300000, { ( ( DR_5 << 4 ) | DR_0 ) }, 0 }

#define LC17               { 473500000, { ( ( DR_5 << 4 ) | DR_0 ) }, 0 }
#define LC18               { 473700000, { ( ( DR_5 << 4 ) | DR_0 ) }, 0 }
#define LC19               { 473900000, { ( ( DR_5 << 4 ) | DR_0 ) }, 0 }
#define LC20               { 474100000, { ( ( DR_5 << 4 ) | DR_0 ) }, 0 }
#define LC21               { 474300000, { ( ( DR_5 << 4 ) | DR_0 ) }, 0 }
#define LC22               { 474500000, { ( ( DR_5 << 4 ) | DR_0 ) }, 0 }
#define LC23               { 474700000, { ( ( DR_5 << 4 ) | DR_0 ) }, 0 }
#define LC24               { 474900000, { ( ( DR_5 << 4 ) | DR_0 ) }, 0 }

#define LC25               { 475100000, { ( ( DR_5 << 4 ) | DR_0 ) }, 0 }
#define LC26               { 475300000, { ( ( DR_5 << 4 ) | DR_0 ) }, 0 }
#define LC27               { 475700000, { ( ( DR_5 << 4 ) | DR_0 ) }, 0 }
#define LC28               { 475900000, { ( ( DR_5 << 4 ) | DR_0 ) }, 0 }
#define LC29               { 476100000, { ( ( DR_5 << 4 ) | DR_0 ) }, 0 }
#define LC30               { 476300000, { ( ( DR_5 << 4 ) | DR_0 ) }, 0 }
#define LC31               { 476500000, { ( ( DR_5 << 4 ) | DR_0 ) }, 0 }
#define LC32               { 476700000, { ( ( DR_5 << 4 ) | DR_0 ) }, 0 }


/************************����CADģʽ����**************************/
LoRaCsma_t Csma = {true, false, false, 0, 2, 0, 0};

uint32_t RfSend_time = 0;

const LoRaMacCsma_t LoRaMacCsma = {LoRaChannelAddFun, LoRaSymbolTime, LoRaListenAagain, LoRaCadMode, LoRaCadTime};

TimerEvent_t CsmaTimer;
void OnCsmaTimerEvent( void )
{  
	TimerStop( &CsmaTimer );

	Csma.Listen = true;
}

/*
*ChannelAddFun�������豸Ƶ��
*������         ��
*����ֵ��       ��
*/
void LoRaChannelAddFun( void )
{
	LoRaMacChannelAdd( 3, ( ChannelParams_t )LC4  );
	LoRaMacChannelAdd( 4, ( ChannelParams_t )LC5  );
	LoRaMacChannelAdd( 5, ( ChannelParams_t )LC6  );
	LoRaMacChannelAdd( 6, ( ChannelParams_t )LC7  );
	LoRaMacChannelAdd( 7, ( ChannelParams_t )LC8  );
	LoRaMacChannelAdd( 8, ( ChannelParams_t )LC9  );
	
	LoRaMacChannelAdd( 9, ( ChannelParams_t )LC10 );
	LoRaMacChannelAdd( 10,( ChannelParams_t )LC11 );
	LoRaMacChannelAdd( 11,( ChannelParams_t )LC12 );
	LoRaMacChannelAdd( 12,( ChannelParams_t )LC13 );
	LoRaMacChannelAdd( 13,( ChannelParams_t )LC14 );
	LoRaMacChannelAdd( 14,( ChannelParams_t )LC15 );
	LoRaMacChannelAdd( 15,( ChannelParams_t )LC16 );
	LoRaMacChannelAdd( 16,( ChannelParams_t )LC17 );
	
	LoRaMacChannelAdd( 17,( ChannelParams_t )LC18 );
	LoRaMacChannelAdd( 18,( ChannelParams_t )LC19 );
	LoRaMacChannelAdd( 19,( ChannelParams_t )LC20 );
	LoRaMacChannelAdd( 20,( ChannelParams_t )LC21 );
	LoRaMacChannelAdd( 21,( ChannelParams_t )LC22 );
	LoRaMacChannelAdd( 22,( ChannelParams_t )LC23 );
	LoRaMacChannelAdd( 23,( ChannelParams_t )LC24 );    

	LoRaMacChannelAdd( 24,( ChannelParams_t )LC25 );
	LoRaMacChannelAdd( 25,( ChannelParams_t )LC26 );
	LoRaMacChannelAdd( 26,( ChannelParams_t )LC27 );
	LoRaMacChannelAdd( 27,( ChannelParams_t )LC28 );
	LoRaMacChannelAdd( 28,( ChannelParams_t )LC29 );
	LoRaMacChannelAdd( 29,( ChannelParams_t )LC30 );
	LoRaMacChannelAdd( 30,( ChannelParams_t )LC31 );
	LoRaMacChannelAdd( 31,( ChannelParams_t )LC32 );
}

/*
 * LoRaCadMode:	 ����ΪCAD
 * ����:	     ��
 * ����ֵ:		 ��
*/
void LoRaCadMode(void)
{
	Radio.Sleep(  );     
	Radio.StartCad(  );  
}

/*
 * LoRaSymbolTime:	��ȡSymbolTime
 * ����:	     			��
 * ����ֵ:		      SymbolTime
*/
float LoRaSymbolTime(void)
{
	Csma.SymbolTime = 0;
	uint8_t LORA_SPREADING_FACTOR = 0;
	
	if(LoRapp_Handle.default_datarate == 0)
		LORA_SPREADING_FACTOR = 12;
	else if(LoRapp_Handle.default_datarate == 1)
		LORA_SPREADING_FACTOR = 11;
	else if(LoRapp_Handle.default_datarate == 2)
		LORA_SPREADING_FACTOR = 10;
	else if(LoRapp_Handle.default_datarate == 3)
		LORA_SPREADING_FACTOR = 9;
	else if(LoRapp_Handle.default_datarate == 4)
		LORA_SPREADING_FACTOR = 8;
	else 
		LORA_SPREADING_FACTOR = 7;
	
	 Csma.SymbolTime = ( pow( (float)2, (float)LORA_SPREADING_FACTOR ) ) / 125;  // SF7 and BW = 125 KHz
	 DEBUG(2,"LORA_SPREADING_FACTOR = %d symbolTime = %0.1f\r\n",LORA_SPREADING_FACTOR,Csma.SymbolTime);
	 return Csma.SymbolTime;
}

/*
*ListenAagain: ��������ڼ��������źţ����ܣ��¸����ʱ���ٷ�������
*/
void LoRaListenAagain(void)
{
	if(!Csma.Listen && Csma.DisturbCounter < Csma.retry)
	{	 
		 Csma.DisturbCounter ++;
	 
		 TimerStop( &CsmaTimer );
		 TimerSetValue( &CsmaTimer, 500 + randr(-5, 5) * 100); //+ randr(-1.5*TimeOnAir, 0)
		 TimerStart( &CsmaTimer );
		
		 DEBUG_WARNING(2,"LoRaCsma.Listen is true\r\n");
	}
}

/*
*	LoRaCadTime ����ȡCAD�ܵ�ʱ��
*/
void LoRaCadTime(void)
{
		Csma.CadTime = LoRaMacCsma.SymbolTime(  ) * 1000 + 280; ///tx preamblelen = 1000+2(LoRaMacCsma.SymbolTime+2.8ms)
		Csma.CadTime *= 2;
}
