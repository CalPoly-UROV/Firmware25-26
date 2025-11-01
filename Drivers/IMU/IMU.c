/*
 * IMU.c
 *
 *  Created on: Apr 20, 2025
 *      Author: robot
 */
#include "IMU.h"

void IMU_Init(){
	BNO080_Initialization();
	BNO080_enableRotationVector(2500);
	BNO080_enableLinearAccelerometer(2500);
	BNO080_enableGyro(2500);
}

float data[10] = {10,1,2,3,4,5,6,7,8,9};

uint32_t lasttime2 = 0;
void IMU_Run(){
	if (HAL_GetTick() - lasttime2 >= 10) {

			lasttime2 = HAL_GetTick();
			int avail = BNO080_dataAvailable();
			if(avail == 1){
				  //Quats
				  data[0] = BNO080_getQuatReal();
				  data[1] = BNO080_getQuatI();
				  data[2] = BNO080_getQuatJ();
				  data[3] = BNO080_getQuatK();
				  //Linear Accels
				  data[4] = BNO080_getLinAccelX();
				  data[5] = BNO080_getLinAccelY();
				  data[6] = BNO080_getLinAccelZ();
				  //Angular Velocities
				  data[7] = BNO080_getGyroX();
				  data[8] = BNO080_getGyroY();
				  data[9] = BNO080_getGyroY();
			}
	}
}

float* IMU_GetData(float* imu_data){
	for (int i = 0; i < 10; i++){
		imu_data[i] = data[i];
	}
	return imu_data;
}

void IMU_StartCalibration(){
	BNO080_calibrateAll();
}

uint32_t*IMU_CalibrationStatus(uint32_t* buff){
	buff[0] = (uint32_t)(BNO080_getQuatRadianAccuracy()*100);
	buff[1] = BNO080_getLinAccelAccuracy();
	buff[2] = BNO080_getGyroAccuracy();
}

void IMU_EndCalibration(){
	BNO080_endCalibration();
}

