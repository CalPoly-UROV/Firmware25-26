/*
 * brightness.c
 *
 *  Created on: Oct 8, 2025
 *      Author: robot
 */

#include "brightness.h"

uint32_t on_duration = 0;
uint32_t off_duration = 100;

uint8_t LED_on = 0;

void set_brightness(uint32_t brightness){
	if(brightness < 100){
		TIM3->CCR1 = brightness * 10;
	}else if(brightness == 0){
		GPIOB->ODR &= ~(1); //LED off
	}else if(brightness == 100){
		GPIOB->ODR |= 1; //LED on
	}
}

void TIM3_IRQHandler(void)
{
	if(TIM3->SR & 1){
		GPIOB->ODR |= 1; //Turn LED on
		TIM3 -> SR &= ~(1); //clear status register
	}else{
		GPIOB->ODR &= ~(1);//Turn LED off
		TIM3 -> SR &= ~(1 << 1);
	}
}
