#include "main.h"
#include "t200/t200driver.h"

TIM_TypeDef thruster_timer;
uint8_t thruster_timer
void t200_setup(GPIO_TypeDef *GPIOx, uint32_t pin, TIM_TypeDef *TIMx, uint8_t channel) {
	thruster_timer =
	  PWM_Init(TIMx, GPIOx, pin, channel, 15, 19999, 0, 20, 1);
}

void t200_setspeed(uint32_t speed) {

}
