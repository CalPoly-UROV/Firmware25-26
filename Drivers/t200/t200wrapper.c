#include "main.h"
#include "t200driver.h"

void Thruster_Init() {
	// Vertical Thruster
	PWM_Init(TIM2, GPIOA, 15, 1, 15, 19999, 1, 28, 1);
	PWM_Init(TIM2, GPIOA, 1, 2, 15, 19999, 0, 4, 1);
	PWM_Init(TIM2, GPIOA, 2, 3, 15, 19999, 0, 8, 1);
	PWM_Init(TIM2, GPIOA, 3, 4, 15, 19999, 0, 12, 1);

	// Horizontal Thruster
	PWM_Init(TIM3, GPIOA, 6, 1, 15, 19999, 0, 24, 2);
	PWM_Init(TIM3, GPIOA, 7, 2, 15, 19999, 0, 28, 2);
}

void t200_setspeed(TIM_TypeDef *TIMx, uint8_t channel, uint32_t speed) {
	// speed is a number 0-100
	if (speed > 100) speed = 100;

	if (speed <= 0){
		PWM_SetDuty(TIMx, channel, 0);
	} else  {
		PWM_SetDuty(TIMx, channel, (8 * speed) + 1100);
	}

}
