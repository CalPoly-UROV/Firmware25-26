/*
 * timer.c
 *
 *  Created on: Sep 19, 2025
 *      Author: robot
 */
#include "timer.h"

int flag = 0;

void timer_init(){
	RCC -> APB1ENR |= 1U;
	TIM4 -> DIER |= 1U;
	NVIC_EnableIRQ(TIM4_IRQn);//enable TIM2 interrupt
	__enable_irq();
}

void timer_pause(uint32_t delay){
	TIM4->ARR = delay;
	TIM4->CR1 |= 1U;
	while(flag == 0){}
	TIM4->CR1 &= 0U;
	flag = 0;
}

void TIM4_IRQHandler(void)
{
  /* USER CODE BEGIN TIM4_IRQn 0 */

	flag = 1;
  /* USER CODE END TIM4_IRQn 0 */

  /* USER CODE BEGIN TIM4_IRQn 1 */
	TIM4 -> SR &= 0xFFF8;
  /* USER CODE END TIM4_IRQn 1 */
}
