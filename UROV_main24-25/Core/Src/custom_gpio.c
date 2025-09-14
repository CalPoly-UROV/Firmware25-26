/*
 * initpin.c
 *
 *  Created on: Apr 19, 2024
 *      Author: liamduckworth
 */

#include "custom_gpio.h"

//configure a pin as an general output
void initGPO(GPIO_TypeDef *port, uint32_t pin, uint32_t type,
					uint32_t speed, uint32_t pupd){

	port->MODER &= ~(MSK2B << (pin << 1));
	port->MODER |= (MOUTPUT << (pin << 1));

	port->OTYPER &= ~(MSK1B << pin);
	port->OTYPER |= (type << pin);

	port->OSPEEDR &= ~(MSK2B << (pin << 1));
	port->OSPEEDR |= (speed << (pin << 1));

	port->PUPDR &= ~(MSK2B << (pin << 1));
	port->PUPDR |= ~(pupd << (pin << 1));

}

//configure a pin as an general input
void initGPI(GPIO_TypeDef *port, uint32_t pin, uint32_t speed, uint32_t pupd){

	port->MODER &= ~(MSK2B << (pin << 1));
	port->MODER |= (MINPUT << (pin << 1));

	port->PUPDR &= ~(MSK2B << (pin << 1));
	port->PUPDR |= ~(pupd << (pin << 1));

}

//configure a pin generically
void initpin(GPIO_TypeDef *port, uint32_t pin, uint32_t mode, uint32_t type,
				uint32_t speed, uint32_t pupd, AFSEL_t afsel){
	port->MODER &= ~(MSK2B << (pin << 1));
	port->MODER |= (mode << (pin << 1));

	port->OTYPER &= ~(MSK1B << pin);
	port->OTYPER |= (type << pin);

	port->OSPEEDR &= ~(MSK2B << (pin << 1));
	port->OSPEEDR |= (speed << (pin << 1));

	port->PUPDR &= ~(MSK2B << (pin << 1));
	port->PUPDR |= ~(pupd << (pin << 1));

	if(pin > 7){
		port->AFR[1] &= ~(MSK4B << ((pin-8) << 2));
		port->AFR[1] |= (afsel << ((pin-8) << 2));
	}
	else{
		port->AFR[0] &= ~(MSK4B << (pin << 2));
		port->AFR[0] |= (afsel << (pin << 2));
	}

}

//configure multiple pins the same way
void mpininit(GPIO_TypeDef *port, uint32_t *pins, uint32_t pincount,
				uint32_t mode, uint32_t type, uint32_t speed, uint32_t pupd,
				AFSEL_t afsel){

	for(int i = 0; i < pincount; i++){
		port->MODER &= ~(MSK2B << (pins[i] << 1));
		port->MODER |= (mode << (pins[i] << 1));

		port->OTYPER &= ~(MSK1B << pins[i]);
		port->OTYPER |= (type << pins[i]);

		port->OSPEEDR &= ~(MSK2B << (pins[i] << 1));
		port->OSPEEDR |= (speed << (pins[i] << 1));

		port->PUPDR &= ~(MSK2B << (pins[i] << 1));
		port->PUPDR |= ~(pupd << (pins[i] << 1));

		if(pins[i] > 7){
			port->AFR[1] &= ~(MSK4B << ((pins[i]-8) << 2));
			port->AFR[1] |= (afsel << ((pins[i]-8) << 2));
		}
		else{
			port->AFR[0] &= ~(MSK4B << (pins[i] << 2));
			port->AFR[0] |= (afsel << (pins[i] << 2));
		}
	}

}

void setpin(GPIO_TypeDef *port, uint32_t pin){

	port->ODR |= (MSK1B << pin);

}

void resetpin(GPIO_TypeDef *port, uint32_t pin){

	port->ODR &= ~(MSK1B << pin);

}
