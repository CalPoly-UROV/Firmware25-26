/*
 * servo.h
 *
 *  Created on: Feb 23, 2025
 *      Author: USER
 */

#ifndef INC_SERVO_H_
#define INC_SERVO_H_

// Inits servoes
void Servos_Init(void);

// Spec WHICH SERVO, AND WHAT ANGLE TO BE AT (0 - 360)

void Servo_SetPosition(uint8_t servo, uint16_t pulse_width);
void Servo_SetAngle(uint8_t servo, uint16_t angle);

#endif /* INC_SERVO_H_ */
