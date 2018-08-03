/*
**************************************************************************************************************
*	@file	main.c
*	@author Jason_531@163.com
*	@version V1.1
*	@date    2017/12/13
*	@brief	NBI_LoRaWAN���ܴ���: add OTAA
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


/*!***********************************���м���************************************/

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
         loramac_rx_info = msg;   ///mac�����������Ϣ��rssi �˿ڵ�
         loramac_evt = evt;
         
         break;
    }
}


/*!***********************************�ָ���************************************/

extern UART_HandleTypeDef 			    UartHandle;
extern RTC_HandleTypeDef 						RtcHandle;
extern SPI_HandleTypeDef            SPI1_Handler;  

PROCESS(Sleep_process,"Sleep_process");
PROCESS(Control_process,"Control_process");
//PROCESS(SX1278Send_process,"SX1278Send_process");
AUTOSTART_PROCESSES(&Sleep_process, &Control_process);  // ,&SX1278Send_process

process_event_t CadWakeup;

/*
*����Sleep_process����Ȩ
*/
void SleepProcess(void)
{
	process_poll(&Sleep_process);
}

/*
*����Control_process�첽�߳�
*/
void ControlProcess(void)
{
	process_post(&Control_process, CadWakeup, NULL);
}

/*
*����CreateEvent�¼�
*/
void CreateEvent(void)
{
	 CadWakeup = process_alloc_event(); //return lastevent++; �½�һ���¼�����ʵ������һ��unsigned charֵ����ʶ��ͬ�¼�
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

//		///����Ϊ����Ƶ��: ����ͨѶ�ŵ�
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
//		//ǳ������            
//		BoardSleep(  );

//		///sleep
//		HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
//	
//		DEBUG_APP(2,"CsmaTimerEvent LoRapp_Handle.FPort : %d \r\n",LoRapp_Handle.FPort);
//		while(!Csma.Listen);

//#endif 
//		//��������ģʽ
//		Radio.Standby( );
//		LoRaMacSetDeviceClass( CLASS_A );
//         
//		Gps_Send_Stae = false; ///�������ƣ���ֹͬʱ��������
//		LoRapp_Handle.Send_Counter = 0;
//		
//		LoRapp_Handle.Send_Buf = "0123456789";
//		LoRapp_Handle.Tx_Len = 10;

//		RfSend_time = HAL_GetTick(  );
//								
//		for(uint8_t i = 0; i < 3; ) ///�������ݻ��ƣ�����ʧ�����ط���������
//		{
//			///�������ݣ����Ӧ�����ģʽ��ȷ�������ȶ���
//			if(User.AppSend(CONFIRMED, LoRapp_Handle.Send_Buf, LoRapp_Handle.Tx_Len, 2) == 0) ///���ͳɹ����л��������ģʽFreq + 30mhz
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

//		///�л�ΪC��ģʽ --- >�������������� --- >����+CAD�л�����
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
//		SetRtcAlarm(60);  ///��������ʱ�� Get_Flash_Datas.sleep_times
//		IntoLowPower(  );     

//#endif	
//		
//	}
//	PROCESS_END();
//}

void processset(void)
{
	process_init();
	process_start(&etimer_process,NULL); ///�Զ�����������߳�
	autostart_start(autostart_processes);
}

PROCESS_THREAD(Sleep_process,ev,data) ///�����̼����Ƿ�CAD����
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
			SetRtcAlarm(10);  ///��������ʱ�� ��������Ϊms����������ʱ��ƫ�Ƶ��»��ѳɹ��ʲ���
			User.LowPower(  );  
		}			

	}
	
  PROCESS_END(); 
}

PROCESS_THREAD(Control_process,ev,data) ///�����豸ִ�в���
{
	
	PROCESS_BEGIN();
	
	while(1)
	{
	
		PROCESS_WAIT_EVENT_UNTIL(ev == CadWakeup);
		
		///ִ�п����豸����
		
		
		///����Ӧ������ǰͬƵ����
		Radio.Standby(  );
		
		LoRaMacSetDeviceClass( CLASS_A );
		
		
		////�ɾ�ֱ�ӷ�������
		
		///�رս��մ��ڣ������˳�
		LoRaMacTestRxWindowsOn( false );
		User.AppSend(UNCONFIRMED, "hello", 6, 2);
		
#if 0		
		////P-CSMA
		LoRapp_Handle.Work_Mode = CSMA; ///�˳�C��״̬
		Radio.Standby( );
		LoRaMacSetDeviceClass( CLASS_A );
		
		LoRapp_Handle.Send_Buf = "helloworld";
		LoRapp_Handle.Tx_Len = 15;
		
		for(uint8_t i = 0; i < 3; ) ///�������ݻ��ƣ�����ʧ�����ط���������
		{
			///�������ݣ����Ӧ�����ģʽ��ȷ�������ȶ���
			if(User.AppSend(UNCONFIRMED, LoRapp_Handle.Send_Buf, LoRapp_Handle.Tx_Len, 2) == 0) ///���ͳɹ����л��������ģʽFreq + 30mhz
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
  * @��������	main
  * @����˵��   ������ 
  * @�������   ��
  * @�������   ��
  * @���ز���   ��

	�汾˵����
	��1����V2.1.1��MCU---stm32L0�����ݲɼ��豸 PRO II��ӦС����;

	�Ż����ܣ�
	��1���� ʵ��LORAWAN��С����ͨ�š�
	��2���� RTCͣ�����ѻ��ơ�
  ��3���� ˫Ƶ��FreqTX = FreqRX2  FreqRX1 = FreqTX+30MHZ
  ��4���� ˫ģ����ͨѶ���֣���ֹ�ŵ�й¶
  ��5���� ģ���װΪ͸�������ýӿ�Ԥ������
  ��6���� ������������CADģʽ��ֻ����preamblelen���ڲ��ȶ��ԣ���˲�ʹ�øû���
	��7���� �������߻��Ѵ������
  ��8���� LoRapp_Handle.Work_Mode��1.����״̬��2.��֤CLASS A/C�������ܸ���
  *****************************************************************************/
/* variable functions ---------------------------------------------------------*/	
int main(void)
{	
	BoardInitMcu(  );	
	DEBUG(2,"TIME : %s  DATE : %s\r\n",__TIME__, __DATE__);
		
	//	MX_IWDG_Init(  );

	//	HAL_IWDG_Refresh(&hiwdg); ///���Ź�ι��
	
	User.AppInit(app_mac_cb);
	
	User.SetLoRaMac(  );
	
	//��������ģʽ
//	Radio.Standby( );
//	LoRaMacSetDeviceClass( CLASS_C );

//	LoRapp_Handle.Loramac_evt_flag = 0;

//	LoRapp_Handle.FPort = randr( 1, 0xDF );

//	LoRapp_Handle.Send_Buf = (uint8_t *)malloc(sizeof(uint8_t)*56); ///ʹ��ָ���������ַ�ռ䣬��������HardFault_Handler����

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

