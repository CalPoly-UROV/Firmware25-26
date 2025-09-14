/*
 * IMU.h
 *
 *  Created on: Apr 20, 2025
 *      Author: robot
 */

#ifndef INC_IMU_IMU_H_
#define INC_IMU_IMU_H_

#include "BNO080.h"

float* IMU_GetData();

void IMU_Init();
void IMU_StartCalibration();
void IMU_EndCalibration();
void IMU_Run();

uint32_t* IMU_CalibrationStatus();

#endif /* INC_IMU_IMU_H_ */
