/*
 * timer.h
 *
 *  Created on: Sep 19, 2025
 *      Author: robot
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_tim.h"
#include "stm32f4xx.h"
#include "math.h"

void timer_init(void);
void timer_delay(uint32_t delay);
void TIM4_IRQHandler(void);

#endif /* INC_TIMER_H_ */
