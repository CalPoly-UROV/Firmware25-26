#include "main.h"
#include "t200driver.h"

void Thruster_Init() {
	  PWM_Init(TIM2, GPIOA, 5, 1, 15, 19999, 0, 20, 1); // test pin to see if everything actually works

	  PWM_Init(TIM2, GPIOA, 15, 1, 15, 1999, 1, 28, 1);
	  PWM_Init(TIM2, GPIOA, 1, 2, 15, 1999, 0, 4, 1);
	  PWM_Init(TIM2, GPIOA, 2, 3, 15, 1999, 0, 8, 1);
	  PWM_Init(TIM2, GPIOA, 3, 4, 15, 1999, 0, 12, 1);

	  // Horizontal Thruster
	  PWM_Init(TIM3, GPIOA, 6, 1, 15, 3999, 0, 24, 2);
	  PWM_Init(TIM3, GPIOA, 7, 2, 15, 3999, 0, 28, 2);
}

void t200_setspeed(uint32_t speed) {

}
