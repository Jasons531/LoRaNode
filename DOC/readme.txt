
	
1��Ӳ��IO�ӿ�ͼ��

								stm32L072CBT6
SX1278						 _ _ _ _ _ _ _ _ _ _ _ _ _ _ 
SPI     NSS	  --------	PA4 |					  		|
		SCK	  --------	PA5 |    				  		|
		MISO  --------	PA6 |					 		|
		MOSI  --------	PA7 |					  		|
						    |					  		|
EXti	DIO0  --------	PB1 |                    		|
		DIO1  --------	PB2 |					  		|
		DIO2  --------	PB10|					  		|
		DIO3  --------	PB11|					 		|
		DIO4  --------	NC	|					  		|
		DIO5  --------	NC	|					 		|
							|					  		|
CPIO	RESET --------	PB0 |					  		|
		LoRa_Power ---  PB12|					 		|
							|					 		|
							|					 		|
GPS	(UART2)					|					 		|	
		TX	  --------  PA2	|					  		|	
		RX	  --------  PA3	|					  		|	
GPS_Power_ON  --------  PB7	|					  		|									
							|					  		|
485	(UART5)					|					 		|	
		485_TX	------	PB3	|					  		|	
		485_RX	------	PB4	|					  		|	
		485_DE	------	PB5	|					  		|
		12V_ON	------  PA8	|					  		|	
							|					  		|
							|					 		|	
DEBUG(UART1)				|					  		|
		TX   ---------	PA9	|					  		|
		RX	 ---------  PA10|					  		|
							|					  		|
I2C							|					  		|
		I2C2_SDA ----- PB14	|					  		|
		I2C2_SCL ----- PB13	|					  		|
							|					  		|
��Դ����ʹ��  -------- PB9	|					  		|
							|					  		|
							|					  		|
							|					  		|
							|_ _ _ _ _ _ _ _ _ _ _ _ _ _|	



�����ط����ƣ�
�ط�����������ģʽ��
1������CONFIRMEDģʽ��Ĭ��Э���ط�ģʽ

2������UNCONFIRMEDģʽ���Զ����ط����ƣ�����CSMA����ģʽ

��Ҫ����ʵ��Ӧ��ʱҪ����Ӧ�ط���������

���л���ʱ��������ִ���

1���ն��豸�ڵ㶨ʱ���߻��ѣ��л���CADģʽ

2�����ض˻��Ѵ���>sleep_time + 2*cad_time��cad������Ҫ��ǰ�������£�

TS=2^SF/BW=2^9/125K=4.1ms/symb 
symb = TS/4.1ms


Radio.SetTxConfig-->SendFrameOnChannel-->ScheduleTx-->(LoRaMacSendFrameOnChannel-->LoRaMacSendOnChannel)

Radio.SetRxConfig-->RxWindowSetup

����class cģʽ


LoRa+4G/2G��4G/2G�����ͳһ���ݸ�ʽ��LoRa��ֻ��ȡʵ����Ч���ݣ�ȥ������




------------------------------------------------------------------------------------
��ܣ����ú���ָ�������չʹ�ã�
      
	  1���������������ѻ��ƣ���ʱSLeep + ����cadtime + �ɹ���ִ�л��Ѻ�����������ٽ�ѭ����������
 	  2��������߻��ѻ���: ���Ѵ���cad_mode--->rx2 = freq+30mhz,preamblelen�ɱ���һ��
	  �����·�preamblelen = symb = TS/2^SF/BW


ע��: CLASS Cģʽ����������Ӧ��ģʽ����֧�ֽ��մ��ڳ�ʱ�˳����ƣ���Э���������Կ��ǣ������¼�����Э��ģʽ��ֱ�Ӳ���A Cģʽ�л�ʹ�ã���Ӧ�Ķ�ʹ��ģʽ����ҪƵ���Ż�ģʽ

	  ����Ӧ����ƣ���������Ӧ��ģʽ��ACK������ƣ�ȷ��Э��������


3��lorawan ���ݸ�ʽ˵����
4012121212000100d1db4e3ac827

MHDR:0x40 (1B)  ///0X80��ȷ�����У�0x40����ȷ������
DevAddr:0x12121212 (4B) ���ģʽ
FCtrl: 0x00(1B)    ///0x20������ACK 
FCnt:  0X01  (2B)֡����
FOpts: 0x00    (0--15B)
FPort: 0xd1  (1B)
FRMPayload:0xdb
MIC: 0x4e3ac827(4B)

5��ͨѶ����ʱ��
  ReceiveDelay1 = RECEIVE_DELAY1;
  ReceiveDelay2 = RECEIVE_DELAY2;
  
6������cad������ģʽ�·�RX����preamblelen���⣬cad = 124, ����rx = 20
Radio.SetTxConfig


radio_configure_csma

packet_sent

csma.c


17101URTU011
