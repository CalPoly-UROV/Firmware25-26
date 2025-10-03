/*
 * probe.c
 *
 *  Created on: Sep 28, 2025
 *      Author: robot
 */

#include "timer.h"

void _write_1(void){
	GPIOB->ODR &= ~GPIO_PIN_11;
	timer_delay(100);
	GPIOB->ODR |= GPIO_PIN_11;
}

void _write_0(void){
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

uint8_t _read_bit(void){
	uint8_t response_bit;
	GPIOB->ODR &= ~GPIO_PIN_11;
	GPIOB->ODR |= GPIO_PIN_11;
	timer_delay(10);
	response_bit = GPIOB->ODR & GPIO_PIN_11;
	timer_delay(90);
	return response_bit;
}

uint8_t probe_read_byte(void){
	int cur_bit = 0;
	int response_byte = 0;
	while(cur_bit < 8){
		response_byte |= _read_bit() << cur_bit;
		cur_bit += 1;
	}
	return response_byte;
}


