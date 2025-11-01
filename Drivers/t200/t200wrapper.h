#ifndef INC_T200WRAPPER_H_
#define INC_T200WRAPPER_H_

void Thruster_Init();
void t200_setspeed(TIM_TypeDef *TIMx, uint8_t channel, uint32_t speed);

#endif /* INC_T200WRAPPER_H_ */
