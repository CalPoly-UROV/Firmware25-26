#ifndef INC_T200WRAPPER_H_
#define INC_T200WRAPPER_H_

// TIM2 | Channel 1,2,3,4: Output Compare No Output | Prescaler: 15 if the chip clock is 16mhz
// TIM3 | Channel 1,2: Output Compare No Output | Prescaler: 15 if the chip clock is 16mhz
void Thruster_Init();
void t200_setspeed(TIM_TypeDef *TIMx, uint8_t channel, uint32_t speed);

#endif /* INC_T200WRAPPER_H_ */
