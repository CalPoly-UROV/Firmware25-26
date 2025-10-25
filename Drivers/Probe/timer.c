/*
 * timer.c
 *
 *  Created on: Sep 19, 2025
 *      Author: robot
 */
#include "timer.h"
#include "main.h"

int flag = 0;

void timer_init(){
	RCC -> APB1ENR |= 1U;
	TIM4 -> DIER |= 1U;
	TIM4 -> PSC = (uint16_t)15;
	NVIC_EnableIRQ(TIM4_IRQn);//enable TIM4 interrupt
	__enable_irq();
}

char* begin = "Beginning Wait";
char* end = "Ending Wait";

void timer_delay(uint32_t delay){
	TIM4->ARR = delay;
	TIM4->CR1 |= 1U;
	while(flag == 0){}
	TIM4->CR1 &= 0U;
	flag = 0;
}

void TIM4_IRQHandler(void)
{
	flag = 1;
	TIM4 -> SR &= ~(1);
}
