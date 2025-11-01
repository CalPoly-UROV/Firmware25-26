#ifndef T200DRIVER_H
#define T200DRIVER_H
	void useHSE(void);
	void PWM_Init(TIM_TypeDef *TIMx, GPIO_TypeDef *GPIOx, uint32_t, uint8_t, uint32_t, uint32_t, uint8_t, uint8_t, uint8_t);
	void PWM_SetDuty(TIM_TypeDef*TIMx, uint8_t, uint32_t);
#endif
