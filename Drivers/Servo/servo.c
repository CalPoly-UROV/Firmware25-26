/*
 * probe.c
 *
 *  Created on: Sep 28, 2025
 *      Author: robot
 */

#include "timer.h"

void _write_1(void){

	GPIOB->ODR |= GPIO_PIN_11;
	GPIOB->ODR &= ~GPIO_PIN_11;
	timer_delay(100);
	GPIOB->ODR |= GPIO_PIN_11;#ifndef T200DRIVER_H
#define T200DRIVER_H
	void useHSE(void);
	void PWM_Init(TIM_TypeDef *TIMx, GPIO_TypeDef *GPIOx, uint32_t, uint8_t, uint32_t, uint32_t, uint8_t, uint8_t, uint8_t);
	void PWM_SetDuty(TIM_TypeDef*TIMx, uint8_t, uint32_t);
#endif

}

void _write_0(void){
	GPIOB->ODR |= GPIO_PIN_11;
	GPIOB->ODR &= ~GPIO_PIN_11;
	timer_delay(10);
	GPIOB->ODR |= GPIO_PIN_11;
	timer_delay(90);
}

void probe_write_byte(uint8_t byte){
	int cur_bit = 0;
	while(cur_bit < 8){
		if(byte & (1 << cur_bit)){
			_write_1();
		}else{
			_write_0();
		}
		cur_bit += 1;
	}
}

uint8_t probe_read_bit(void){
	GPIOB->ODR &= ~GPIO_PIN_11;

	uint8_t response_bit;
	GPIOB->ODR &= ~GPIO_PIN_11;
	timer_delay(1);
	GPIOB->ODR |= GPIO_PIN_11;
	timer_delay(15);
	response_bit = (GPIOB->ODR & GPIO_PIN_11) >> 11;

	if(response_bit){
		GPIOB->ODR |= GPIO_PIN_11;
	}

	timer_delay(20);
	GPIOB->ODR &= ~GPIO_PIN_11;
	timer_delay(70);
	return response_bit;
}

uint8_t probe_read_byte(void){
	int cur_bit = 0;
	int response_byte = 0;
	while(cur_bit < 8){
		uint8_t bit = probe_read_bit();
		response_byte |= bit << cur_bit;
		cur_bit += 1;
	}
	return response_byte;
}


