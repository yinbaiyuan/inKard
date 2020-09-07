#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32l0xx_hal.h"

void Error_Handler(void);

#define LED_Pin GPIO_PIN_2
#define LED_GPIO_Port GPIOA

#define INK_MOSI_Pin GPIO_PIN_5
#define INK_MOSI_GPIO_Port GPIOA

#define INK_CLK_Pin GPIO_PIN_6
#define INK_CLK_GPIO_Port GPIOA

#define INK_CS_Pin GPIO_PIN_7
#define INK_CS_GPIO_Port GPIOA

#define INK_DC_Pin GPIO_PIN_0
#define INK_DC_GPIO_Port GPIOB

#define INK_RST_Pin GPIO_PIN_1
#define INK_RST_GPIO_Port GPIOB

#define INK_IS_BUSY_Pin GPIO_PIN_8
#define INK_IS_BUSY_GPIO_Port GPIOA

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
