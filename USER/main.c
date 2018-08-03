/*
**************************************************************************************************************
*	@file	main.c
*	@author Jason_531@163.com
*	@version V1.1
*	@date    2017/12/13
*	@brief	NBI_LoRaWAN功能代码: add OTAA
***************************************************************************************************************
*/
/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <math.h>
#include "stm32l0xx_hal.h"
#include "usart.h"
#include "rtc-board.h"
#include "timerserver.h"
#include "delay.h"
#include "board.h"
#include "user-app.h"
#include "etimer.h"
#include "autostart.h"


#ifndef SUCCESS
#define SUCCESS                         1
#endif

#ifndef FAIL
#define FAIL                            0
#endif

#define CSMAS														2


/*!***********************************空中激活************************************/

#if  OVER_THE_AIR_ACTIVATION

extern uint8_t DevEui[8];
static uint8_t AppEui[] = LORAWAN_APPLICATION_EUI;
static uint8_t AppKey[] = LORAWAN_APPLICATION_KEY;

extern TimerEvent_t JoinReqTimer;
extern volatile bool IsNetworkJoined;
extern bool JoinReq_flag;

#endif

LoRaMacRxInfo *loramac_rx_info;
mac_evt_t loramac_evt;

void app_mac_cb (mac_evt_t evt, void *msg)
{
    switch(evt){
    case MAC_STA_TXDONE:                
    case MAC_STA_RXDONE:
    case MAC_STA_RXTIMEOUT:
    case MAC_STA_ACK_RECEIVED:
    case MAC_STA_ACK_UNRECEIVED:
    case MAC_STA_CMD_JOINACCEPT:         
    case MAC_STA_CMD_RECEIVED:
         loramac_rx_info = msg;   ///mac层接收数据信息：rssi 端口等
         loramac_evt = evt;
         
         break;
    }
}


/*!***********************************分割线************************************/

extern UART_HandleTypeDef 			    UartHandle;
extern RTC_HandleTypeDef 						RtcHandle;
extern SPI_HandleTypeDef            SPI1_Handler;  

PROCESS(Sleep_process,"Sleep_process");
PROCESS(Control_process,"Control_process");
//PROCESS(SX1278Send_process,"SX1278Send_process");
AUTOSTART_PROCESSES(&Sleep_process, &Control_process);  // ,&SX1278Send_process

process_event_t CadWakeup;

/*
*启动Sleep_process控制权
*/
void SleepProcess(void)
{
	process_poll(&Sleep_process);
}

/*
*启动Control_process异步线程
*/
void ControlProcess(void)
{
	process_post(&Control_process, CadWakeup, NULL);
}

/*
*创建CreateEvent事件
*/
void CreateEvent(void)
{
	 CadWakeup = process_alloc_event(); //return lastevent++; 新建一个事件，事实上是用一组unsigned char值来标识不同事件
}

extern uint32_t UpLinkCounter;

bool Gps_Send_Stae = false;

/*!
 * Channels default datarate
 */
extern int8_t ChannelsDefaultDatarate;

//PROCESS_THREAD(SX1278Send_process,ev,data)
//{
//	static struct etimer et;
//        
//	PROCESS_BEGIN();
//	
//	USR_UsrLog("Contiki System SX1278Send Process..."); 
//    
//  	etimer_set(&et,CLOCK_SECOND);	    
//	while(1)
//	{		
//		PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));		
//		
//#if CSMAS		
//       								
//		Csma.DisturbCounter = 0;

//		Csma.Listen = false;

//		///设置为侦听频段: 更改通讯信道
//		///RxWindowSetup
//		LoRapp_Handle.Work_Mode = CSMA;
//		SX1276.Settings.State = RF_IDLE;
//		Radio.Standby( );
//	  LoRaMacSetDeviceClass( CLASS_C );

//		LoRaMacCsma.SymbolTime(  );
//		
//		TimerStop( &CsmaTimer );
//		TimerSetValue( &CsmaTimer, 1000 + randr(-10, 10)*100); 
//		TimerStart( &CsmaTimer );		
//				
//		//浅度休眠            
//		BoardSleep(  );

//		///sleep
//		HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
//	
//		DEBUG_APP(2,"CsmaTimerEvent LoRapp_Handle.FPort : %d \r\n",LoRapp_Handle.FPort);
//		while(!Csma.Listen);

//#endif 
//		//开启侦听模式
//		Radio.Standby( );
//		LoRaMacSetDeviceClass( CLASS_A );
//         
//		Gps_Send_Stae = false; ///保护机制，防止同时发送数据
//		LoRapp_Handle.Send_Counter = 0;
//		
//		LoRapp_Handle.Send_Buf = "0123456789";
//		LoRapp_Handle.Tx_Len = 10;

//		RfSend_time = HAL_GetTick(  );
//								
//		for(uint8_t i = 0; i < 3; ) ///发送数据机制：发送失败则重发两次数据
//		{
//			///上行数据，添加应答机制模式，确保数据稳定性
//			if(User.AppSend(CONFIRMED, LoRapp_Handle.Send_Buf, LoRapp_Handle.Tx_Len, 2) == 0) ///发送成功后切换进入接收模式Freq + 30mhz
//			{
//				DEBUG(2,"Wait ACK app_send UpLinkCounter = %d\r\n", LoRaMacGetUpLinkCounter( ));
//						
//				PROCESS_YIELD_UNTIL(LoRapp_Handle.Loramac_evt_flag == 1);
//				LoRapp_Handle.Loramac_evt_flag = 0;
//				
//				Csma.Listen = false;
//				break;
//			}
//			else
//			{
//				DEBUG_WARNING(2,"app_send again\r\n");
//				Radio.Standby(  );
//				etimer_set(&et,CLOCK_SECOND*4 + randr(-CLOCK_SECOND*4,CLOCK_SECOND*4));
//				PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
//				i++;
//			}
//		}
//		etimer_set(&et,CLOCK_SECOND*20);	 

//		///切换为C类模式 --- >进入周期性休眠 --- >休眠+CAD切换机制
//		//Radio.Standby( );
//		//LoRapp_Handle.Work_Mode = CAD;
//		//LoRaMacSetDeviceClass( CLASS_C);
//	
//	
//#if GPPS			
//			
//		Gps_Send_Stae = true;	
//		PROCESS_YIELD_UNTIL(GPSLocationDone == ev);
//		Radio.Sleep();
//						
//		if(Get_Flash_Datas.sleep_times>60)
//		{
//				Get_Flash_Datas.sleep_times -= (LoRapp_SenSor_States.Work_Time/1000);
//		}
//		DEBUG(2,"sleep_times = %d Work_Time = %d\r\n", Get_Flash_Datas.sleep_times,LoRapp_SenSor_States.Work_Time);
//		SetRtcAlarm(60);  ///设置闹钟时间 Get_Flash_Datas.sleep_times
//		IntoLowPower(  );     

//#endif	
//		
//	}
//	PROCESS_END();
//}

void processset(void)
{
	process_init();
	process_start(&etimer_process,NULL); ///自动包含下面的线程
	autostart_start(autostart_processes);
}

PROCESS_THREAD(Sleep_process,ev,data) ///主进程监听是否CAD唤醒
{	
  static struct etimer et;
	static uint32_t usertime = 0;
	
	PROCESS_BEGIN();
	
	usertime = HAL_GetTick(  );
	
	etimer_set(&et,CLOCK_SECOND*0.05);
	
	USR_UsrLog("Contiki System Sleep Process..."); 
	
	while(1)
	{
		PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));			
		
		if(!LoRapp_Handle.Cad_Detect)
		{
			DEBUG(2, "usertime = %d\r\n",HAL_GetTick(  ) - usertime);
			
//			LoRaMacCsma.CadMode(  );	
//			
//			LoRaMacCsma.CadTime(  );
						
			delay_us( User.CadTime( ) ); 
			
			DEBUG(2,"-----------------timecad = %d----------\r\n",Csma.CadTime);
		}	
		if(!LoRapp_Handle.Cad_Detect)
		{
			DEBUG(2,"-----------------Cad_Done----------\r\n");
			SetRtcAlarm(10);  ///设置闹钟时间 必须设置为ms，否则会出现时间偏移导致唤醒成功率不高
			User.LowPower(  );  
		}			

	}
	
  PROCESS_END(); 
}

PROCESS_THREAD(Control_process,ev,data) ///控制设备执行操作
{
	
	PROCESS_BEGIN();
	
	while(1)
	{
	
		PROCESS_WAIT_EVENT_UNTIL(ev == CadWakeup);
		
		///执行控制设备命令
		
		
		///发送应答命令前同频侦听
		Radio.Standby(  );
		
		LoRaMacSetDeviceClass( CLASS_A );
		
		
		////干净直接发送数据
		
		///关闭接收窗口，快速退出
		LoRaMacTestRxWindowsOn( false );
		User.AppSend(UNCONFIRMED, "hello", 6, 2);
		
#if 0		
		////P-CSMA
		LoRapp_Handle.Work_Mode = CSMA; ///退出C类状态
		Radio.Standby( );
		LoRaMacSetDeviceClass( CLASS_A );
		
		LoRapp_Handle.Send_Buf = "helloworld";
		LoRapp_Handle.Tx_Len = 15;
		
		for(uint8_t i = 0; i < 3; ) ///发送数据机制：发送失败则重发两次数据
		{
			///上行数据，添加应答机制模式，确保数据稳定性
			if(User.AppSend(UNCONFIRMED, LoRapp_Handle.Send_Buf, LoRapp_Handle.Tx_Len, 2) == 0) ///发送成功后切换进入接收模式Freq + 30mhz
			{
				DEBUG(2,"Wait ACK app_send UpLinkCounter = %d\r\n", LoRaMacGetUpLinkCounter( ));
						
				PROCESS_YIELD_UNTIL(LoRapp_Handle.Loramac_evt_flag == 1);
				LoRapp_Handle.Loramac_evt_flag = 0;
				
				Csma.Listen = false;
				break;
			}
			else
			{
				DEBUG_WARNING(2,"app_send again\r\n");
				Radio.Standby(  );
				etimer_set(&et,CLOCK_SECOND*4 + randr(-CLOCK_SECOND*4,CLOCK_SECOND*4));
				PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
				i++;
			}
		}
		
#endif
	}

  PROCESS_END(); 
}

/*******************************************************************************
  * @函数名称	main
  * @函数说明   主函数 
  * @输入参数   无
  * @输出参数   无
  * @返回参数   无

	版本说明：
	【1】：V2.1.1：MCU---stm32L0，数据采集设备 PRO II适应小网关;

	优化功能：
	【1】： 实现LORAWAN与小网关通信。
	【2】： RTC停机唤醒机制。
  【3】： 双频段FreqTX = FreqRX2  FreqRX1 = FreqTX+30MHZ
  【4】： 双模进行通讯区分，防止信道泄露
  【5】： 模块封装为透传，采用接口预留接入
  【6】： 侦听：不采用CAD模式，只依靠preamblelen存在不稳定性，因此不使用该机制
	【7】： 增加休眠唤醒处理机制
  【8】： LoRapp_Handle.Work_Mode：1.侦听状态；2.保证CLASS A/C正常不受干扰
  *****************************************************************************/
/* variable functions ---------------------------------------------------------*/	
int main(void)
{	
	BoardInitMcu(  );	
	DEBUG(2,"TIME : %s  DATE : %s\r\n",__TIME__, __DATE__);
		
	//	MX_IWDG_Init(  );

	//	HAL_IWDG_Refresh(&hiwdg); ///看门狗喂狗
	
	User.AppInit(app_mac_cb);
	
	User.SetLoRaMac(  );
	
	//开启侦听模式
//	Radio.Standby( );
//	LoRaMacSetDeviceClass( CLASS_C );

//	LoRapp_Handle.Loramac_evt_flag = 0;

//	LoRapp_Handle.FPort = randr( 1, 0xDF );

//	LoRapp_Handle.Send_Buf = (uint8_t *)malloc(sizeof(uint8_t)*56); ///使用指针必须分配地址空间，否则会出现HardFault_Handler错误

	processset( );

	USR_UsrLog("System Contiki InitSuccess...");	

	TimerInit( &CsmaTimer, OnCsmaTimerEvent );

	Radio.Sleep();
	    	
	while (1)
	{		
		do
		{
		}while(process_run() > 0);    
	}
}


/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void)
{ 
	DEBUG(2,"error\r\n");
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif


/*--------------------------------------------------------------------------------------------------------
																						0ooo											
                   							ooo0       (   )
                								(   )     	) /
                								 \ (     	 (_/
                								  \_)
----------------------------------------------------------------------------------------------------------*/

