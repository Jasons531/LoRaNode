/*
**************************************************************************************************************
*	@file		debug.h
*	@author Ysheng
*	@version 
*	@date    
*	@brief	debug
***************************************************************************************************************
*/
#ifndef __DEBUG_H
#define __DEBUG_H	 
#include <stdio.h>
#include <stdint.h>
#include "stm32l0xx_hal.h"
#include "usart.h"

#ifdef __cplusplus
	extern "C" {
#endif
			
#define DEBUG__						1
#define DEBUG_LEVEL	  		        2					//调试等级，配合DEBUG调试宏控制调试输出范围,大于该等级的调试不输出
		
		
#ifdef DEBUG__				  	//调试宏定义  
#include <stdio.h>
#include <string.h>  
//	#define DEBUG(level, fmt, arg...)  if(level <= DEBUG_LEVEL)	printf(fmt,##arg);  
//	#define DEBUG_NOW(level, fmt, arg...)	
//	#define REDIRECT_SEND()	
//	#define REDIRECT_RECIVE()
//	#define REDIRECT_RECORD()
////extern void DEBUG(uint8_t level, const int8_t *fmt, ...);
		
#define APP        2

#define NORMAL     2

#define WARNING    2

#define ERROR      2

#define DEBUG(level,format,...)  if(level <= DEBUG_LEVEL)  printf(__FILE__", %d: "format"\r\n", __LINE__, ##__VA_ARGS__)

#define DEBUG_APP(level,format,...) if(level <= APP) printf("APP:"__FILE__", %d: "format"\r\n", __LINE__, ##__VA_ARGS__) 

#define DEBUG_NORMAL(level,format,...) if(level <= NORMAL) printf("NORMAL:"__FILE__", %d: "format"\r\n", __LINE__, ##__VA_ARGS__) 

#define DEBUG_WARNING(level,format,...) if(level <= WARNING) printf("WARNING:"__FILE__", %d: "format"\r\n", __LINE__, ##__VA_ARGS__) 

#define DEBUG_ERROR(level,format,...)  if(level <= ERROR) printf("ERROR:"__FILE__", %d: "format"\r\n", __LINE__, ##__VA_ARGS__) 

#endif //end of DEBUG__							

#ifdef __cplusplus
}
#endif

#endif
