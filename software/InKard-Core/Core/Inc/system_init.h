
#ifndef __SYSTEM_INIT_H
#define __SYSTEM_INIT_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32l0xx_hal.h"
	 

	 
void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_USART1_UART_Init(void);
	 
#ifdef __cplusplus
}
#endif

#endif
