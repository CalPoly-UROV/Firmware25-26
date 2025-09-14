/*
 * software_test_platform_main.c
 *
 *  Created on: Oct 19, 2024
 *      Author: liam duckworth
 */

#include <string.h>
#include "software_test_platform.h"
#include "PHT/pht_sensor.h"
#include "commands.h"
#include "thrusters.h"
#include "custom_gpio.h"
#include "IMU/IMU.h"

//packet size for FS comms is 64 bytes always,
//allocate 1 extra for null termination

#define RECV_BUFF_SIZE 	(65)

uint8_t recv_buff[RECV_BUFF_SIZE];
uint8_t new = 0;

//arguments must be number of arguments, pointer to arguments
typedef int (*command)(uint32_t, uint8_t*);

command commands[255];
uint32_t com_size[255];

//sensor statuses


int not_implemented(uint32_t size, uint8_t *args){
	CDC_Transmit_FS(args, size);
	return 2;
}

/*
 * Empty the buffer and await new commands
 */
int terminate(uint32_t size, uint8_t *args)
{
	new = 0;
	return 0;
}

/*
 * Blink an LED
 * Debug command
 * args [command, N/A, N/A]
 */
int blink(uint32_t size, uint8_t *args)
{
	HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);
	CDC_Transmit_FS(args, size);
	return 0;
}

int ping(uint32_t size, uint8_t *args)
{
	CDC_Transmit_FS(args, size);
	return 0;
}

/*
 * Set a motor
 * if index 0-7, sets an individual motor
 * args [command, index, value]
 * 
 * if index 8-11, sets an individual servo
 * args [command, index, value]
 */
int motor(uint32_t size, uint8_t *args)
{
	if(args[1] < 8)
	{
		set_thruster(args[1], args[2]);
	}
	
	if(args[1] >= 8 && args[1] <= 11)
	{
		//Servo_SetAngle(args[1] - 8, args[2]);
	}
	
	CDC_Transmit_FS(args, size);
	return 0;
}

/*
 * Read a sensor
 */
int sensor(uint32_t size, uint8_t *args)
{
	uint8_t* transmit = args;
	uint32_t t_size = size;

	uint32_t external_temp;
	switch (args[1]) {
	case 0: //IMU
		switch(args[2]){
		case 0: //Data request
			float imu_data[10];
			transmit = (uint8_t*)IMU_GetData(imu_data);
			t_size = 40;
			break;

		case 1: //Begin Callibration
			IMU_StartCalibration();
			break;

		case 2: //read calibration status
			uint32_t calibration_data[3];
			transmit = (uint8_t*)IMU_CalibrationStatus(calibration_data);
			t_size = 12;
			break;

		case 3:
			IMU_EndCalibration();
			break;
		}
		break;

	case 1: //External Temp
			if (args[2] == 0) {
				external_temp = TempProbe_GetTemp();
				transmit = (uint8_t*)(&external_temp);
			}
			else if (args[2] == 1) {
				if (TempProbe_GetConn()) {
					transmit = (uint8_t*)"OK";
				}
				else {
					transmit = (uint8_t*)"DC";
				}
			t_size = 4;
			break;
			}

	case 2: //Internal Temp
		if (args[2] == 0) {
			uint32_t int_temp = PHT_GetTemperature();
			transmit = (uint8_t*)(&int_temp);
			t_size = 4;
			return 0;
		}
		else if (args[2] == 1) {
			uint32_t int_press = PHT_GetPressure();
			transmit = (uint8_t*)(&int_press);
			t_size = 4;
			return 0;
		}
		else if (args[2] == 2) {
			//get humidity
			return 0;
		}
		break;
	}

	CDC_Transmit_FS(transmit, t_size);
	return 0;
}

/*
 * Set all thrusters in one command
 * args [command, val0, val1, val2, val3, val4, val5, val6, val7]
 */
int thrusters_cmd(uint32_t size, uint8_t *args)
{
	set_all_thrusters(&args[1]);
	CDC_Transmit_FS(args, size);
	return 0;
}

int init(void)
{

	/*preliminary hex commands
	 *
	 * 0x00 none
	 * 0x42 (B)link			(3 bytes)
	 * 0x4D (M)otor set		(3 bytes) //set any motor
	 * 0x53	(S)ensor read	(3 bytes)
	 * 0x54 (T)hrusters set (9 bytes) //set all thruster motors
	 *
	 */
	//set both arrays to 0
	memset(commands, (uint32_t) not_implemented, 255*sizeof(command));
	memset(com_size, CMD_SIZE_NONE, 255*sizeof(uint32_t));

	commands[0x00] = terminate;
	com_size[0x00] = CMD_SIZE_NONE;

	commands['B'] = blink;
	com_size['B'] = CMD_SIZE_3BYTE;

	commands['M'] = motor;
	com_size['M'] = CMD_SIZE_3BYTE;

	commands['S'] = sensor;
	com_size['S'] = CMD_SIZE_3BYTE;

	commands['T'] = thrusters_cmd;
	com_size['T'] = CMD_SIZE_9BYTE;

	commands['P'] = ping;
	com_size['P'] = CMD_SIZE_3BYTE;

	/*
	 * Initialize thrusters
	 */
	init_thrusters();

	/*
	 * Initialize servos
	 */
	//Servo_init();
	
	/*
	 * Initialize Sensors
	 */
	//PHT_Init();

	//TempProbe_Init();
	//TempProbe_Start();

	//IMU_Init();

	return 0;
}

int sw_test_main(void)
{
	init();
	uint32_t rbuffind = 0;
	uint32_t size = 1;
	uint8_t command = 0;

	while(1)
	{
		rbuffind = 0;
		/*
		 * at high clock rates, PHT_run makes the code run extremely slow
		 * probably due to generating too many interrupts or something
		 * probably just need to increase some values
		 */
		//PHT_Run();
		//IMU_Run();
		/*if(new)
		{
			CDC_Transmit_FS(recv_buff, strnlen(recv_buff, (unsigned) RECV_BUFF_SIZE));
		}*/

		//buffer is null terminated by the receive code
		//loop exits if the size would make the next command go out of bounds or if
		//it hits a null byte as the next command (0x00 command sets new = 0)
		while(new){
			size = com_size[recv_buff[rbuffind]];
			command = recv_buff[rbuffind];

			commands[command](size, &recv_buff[rbuffind]);

			//go to next command
			rbuffind += size;
		}

		//uint8_t test[] = "byte array\r\n";
		//CDC_Transmit_FS(test, sizeof(test)-1);

		//CDC_Transmit_FS(text, strlen(text));
		//HAL_Delay(1000);
	}

	return 0;

}
