#ifndef __TEMPTIMER_H
#define __TEMPTIMER_H

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_tim.h"
#include "stm32f4xx.h"
#include "math.h"

typedef enum {
	s_CONV_RESET,
	s_CONV_WRITE,
	s_CONVERT,

	s_READ_RESET,
	s_READ_WRITE,
	s_READ,

	s_STOP
}TempProbe_STATE;

typedef enum {
	TempProbe_OK = 1,
	TempProbe_DC = 0
}TempProbe_Connection;

#define command_CONVERT_T 0x44CC
#define command_READ_SPAD 0xBECC



void TempProbe_Init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void TempProbe_Start();
void TempProbe_Stop();
int TempProbe_GetTemp();
TempProbe_Connection TempProbe_GetConn();

#endif
