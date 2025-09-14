#include "main.h"
#include "pht_sensor.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

//Return Data
uint32_t PHT_Temperature = 0;
uint32_t PHT_Pressure = 0;
double PHT_depth_meters = 0;

//PT PROM VALUES
uint16_t PRESSURE_SENSITIVITY = 0; //C1
uint16_t PRESSURE_OFFSET = 0; //C2
uint16_t TC_PRESSURE_SENSITIVITY = 0; //C3
uint16_t TC_PRESSURE_OFFSET = 0; //C4
uint16_t TEMP_REF = 0; //C5
uint16_t TC_TEMP = 0; //C6

//Digital Read Values
uint32_t DIGITAL_PRESSURE = 0; //D1
uint32_t DIGITAL_TEMPERATURE = 0; //D2

//Timing
uint64_t lasttime = 0;

extern I2C_HandleTypeDef hi2c2;

//Function Declarations
void PT_PROMReadAll(void);
HAL_StatusTypeDef PT_PROMRead(uint8_t cmd, uint16_t* val);

HAL_StatusTypeDef PHT_Init(void)
{
	uint8_t command;

	//TRANSMIT RESET FOR PT AND RH
	command = PT_RESET;
	HAL_I2C_Master_Transmit(&hi2c2, PT_ADDR << 1, &command, sizeof(uint8_t), TIMEOUT);
	command = RH_RESET;
	HAL_I2C_Master_Transmit(&hi2c2, RH_ADDR << 1, &command, sizeof(uint8_t), TIMEOUT);

	//Get all PROM values for PT
    PT_PROMReadAll();

    return HAL_OK;
}

HAL_StatusTypeDef PHT_ReadPressureValue(uint8_t sensitivity)
{
	uint8_t receive[4];
	uint32_t val;

    HAL_I2C_Master_Transmit(&hi2c2, PT_ADDR << 1, &sensitivity, sizeof(sensitivity), TIMEOUT);
    HAL_I2C_Master_Transmit(&hi2c2, PT_ADDR << 1, 0x00, sizeof(uint8_t), TIMEOUT);
    HAL_I2C_Master_Receive(&hi2c2, PT_ADDR << 1, receive, sizeof(uint32_t), TIMEOUT);

    uint32_t* recvptr = (uint32_t*)receive;
    val = *recvptr;
    //val = ((uint32_t)receive[2] << 16) + ((uint32_t)receive[1] << 8) + ((uint32_t)receive[0]);

    DIGITAL_PRESSURE = val;;

    return HAL_OK;
}

HAL_StatusTypeDef PHT_ReadTemperatureValue(uint8_t sensitivity)
{
	uint8_t receive[4] = {0};
	uint32_t val;
    HAL_I2C_Master_Transmit(&hi2c2, PT_ADDR << 1, &sensitivity, sizeof(sensitivity), TIMEOUT);
    HAL_I2C_Master_Transmit(&hi2c2, PT_ADDR << 1, 0x00, sizeof(uint8_t), TIMEOUT);
    HAL_I2C_Master_Receive(&hi2c2, PT_ADDR << 1, receive, sizeof(uint32_t), TIMEOUT);

    uint32_t* recvptr = (uint32_t*)receive;
    val = *recvptr;
    //val = ((uint32_t)receive[3] << 24) + ((uint32_t)receive[2] << 16) + ((uint32_t)receive[1] << 8) + ((uint32_t)receive[0]);

    DIGITAL_TEMPERATURE = val;

    return HAL_OK;
}

void PHT_CalcTemperature(void)
{
	int32_t temp_diff = (DIGITAL_TEMPERATURE - TEMP_REF) * 256;
	PHT_Temperature = 2000 + ((temp_diff * TC_TEMP) / 8388608);
}

void PHT_CalcPressure(void)
{
	int32_t temp_diff = (DIGITAL_TEMPERATURE - TEMP_REF) * 256;
	int64_t offset = (PRESSURE_OFFSET * 131072) + ((TC_PRESSURE_OFFSET * temp_diff) / 64);
	int64_t sens = (PRESSURE_SENSITIVITY * 65536) + ((TC_PRESSURE_SENSITIVITY * temp_diff) / 128);

	PHT_Pressure = (((DIGITAL_PRESSURE * sens) / 2097152) - offset) / 32768;
}

int32_t PHT_GetPressure(void)// pressure in millibars
{
	return PHT_Pressure;
}

int32_t PHT_GetTemperature(void)
{
	return PHT_Temperature;
}

double PHT_GetDepth(void){
	return PHT_depth_meters;
}

double PHT_CalcDepth(void)//depth in meters for freshwater
{
	double density_freshwater = 1000; //100 kg/m^3 is the density of freshwater
	double gravity = 9.81;// m/s^2
	double pressure_pascal = PHT_Pressure / 100;//pressure in pascals
	double PHT_depth_meters = pressure_pascal / (density_freshwater*gravity);
	return PHT_depth_meters;
}

void PHT_Run(void)
{
	if (HAL_GetTick() - lasttime >= 1000) {
		lasttime = HAL_GetTick();
		PHT_ReadPressureValue(PT_D1_8192);
		PHT_ReadTemperatureValue(PT_D2_8192);
		PHT_CalcTemperature();
		PHT_CalcPressure();
		PHT_CalcDepth();
	}
}

void PT_PROMReadAll(void)
{
	uint8_t command;
	uint16_t val;
	//C1 PRESSURE SENS
	command = PT_PROM_READ | 0x02;
	PT_PROMRead(command, &val);
	PRESSURE_SENSITIVITY = val;

	//C2 PRESSURE OFFSET
	command = PT_PROM_READ | 0x04;
	PT_PROMRead(command, &val);
	PRESSURE_OFFSET = val;

	//C3 PRESSURE SENSITIVITY
	command = PT_PROM_READ | 0x06;
	PT_PROMRead(command, &val);
	PRESSURE_SENSITIVITY = val;

	//C4
	command = PT_PROM_READ | 0x08;
	PT_PROMRead(command, &val);
	TC_PRESSURE_OFFSET = val;

	//C5
	command = PT_PROM_READ | 0x0A;
	PT_PROMRead(command, &val);
	TEMP_REF = val;

	//C6
	command = PT_PROM_READ | 0x0C;
	PT_PROMRead(command, &val);
	TC_TEMP = val;
}

HAL_StatusTypeDef PT_PROMRead(uint8_t command, uint16_t* val)
{
	uint8_t receive[2];
	HAL_I2C_Master_Transmit(&hi2c2, PT_ADDR << 1, &command, sizeof(command), TIMEOUT);
	HAL_I2C_Master_Receive(&hi2c2, PT_ADDR << 1, receive, sizeof(receive), TIMEOUT);

	uint16_t* recv_ptr = (uint16_t*)receive;
	*val = recv_ptr[0];

	return HAL_OK;
}
