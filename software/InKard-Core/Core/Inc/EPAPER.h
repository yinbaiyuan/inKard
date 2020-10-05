#ifndef __EPAPER_H
#define __EPAPER_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32l0xx_hal.h"
#include "main.h"
//250*122///////////////////////////////////////

#define MONOMSB_MODE 1
#define MONOLSB_MODE 2 
#define RED_MODE     3

#define MAX_LINE_BYTES 25// =200/8
#define MAX_COLUMN_BYTES  200

#define ALLSCREEN_GRAGHBYTES	5000

///////////////////////////GPIO Settings//////////////////////////////////////////////////////

#define EPD_W21_MOSI_0	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET) //GPIO_ResetBits(GPIOA, GPIO_PIN_5)
#define EPD_W21_MOSI_1	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET)

#define EPD_W21_CLK_0	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET)
#define EPD_W21_CLK_1	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET)

#define EPD_W21_CS_0	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET)
#define EPD_W21_CS_1	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET)

#define EPD_W21_DC_0	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET)
#define EPD_W21_DC_1	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET)

#define EPD_W21_RST_0	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET)
#define EPD_W21_RST_1	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET)

#define EPD_W21_BUSY_LEVEL 0
#define isEPD_W21_BUSY HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) 


void driver_delay_xms(unsigned long xms);			
void Epaper_READBUSY(void);
void Epaper_Spi_WriteByte(unsigned char TxData);
void Epaper_Write_Command(unsigned char cmd);
void Epaper_Write_Data(unsigned char data);

void EPD_HW_Init(void); //Electronic paper initialization
void EPD_Update(void);

void EPD_Part_Init(void);//Local refresh initialization
void EPD_Part_Update(void); 

void EPD_WhiteScreen_White(void);
void EPD_DeepSleep(void);
//Display 
void EPD_WhiteScreen_ALL(const unsigned char *datas);
void EPD_SetRAMValue_BaseMap(const unsigned char * datas);
void EPD_Dis_Part(unsigned int x_start,unsigned int y_start,const unsigned char * datas,unsigned int PART_COLUMN,unsigned int PART_LINE);
void EPD_Dis_Part_myself(unsigned int x_startA,unsigned int y_startA,const unsigned char * datasA,
	                       unsigned int x_startB,unsigned int y_startB,const unsigned char * datasB,
												 unsigned int x_startC,unsigned int y_startC,const unsigned char * datasC,
												 unsigned int x_startD,unsigned int y_startD,const unsigned char * datasD,
											   unsigned int x_startE,unsigned int y_startE,const unsigned char * datasE,
												 unsigned int PART_COLUMN,unsigned int PART_LINE
	                      );
												 
										
#ifdef __cplusplus
}
#endif
#endif


