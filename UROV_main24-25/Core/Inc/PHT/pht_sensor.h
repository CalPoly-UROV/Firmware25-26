/*
 * phtMS8607.h
 *
 *  Created on: Oct 12, 2024
 *      Author: poo_face
 */
#ifndef PHT_SENSOR_H
#define PHT_SENSOR_H

#include "stm32f4xx_hal.h"

#define PT_ADDR 0x76
#define RH_ADDR 0x40

//PT Sensitivity
#define PT_D1_256 0x40
#define PT_D1_512 0x42
#define PT_D1_1024 0x44
#define PT_D1_2048 0x46
#define PT_D1_4096 0x48
#define PT_D1_8192 0x4A
#define PT_D2_256 0x50
#define PT_D2_512 0x52
#define PT_D2_1024 0x54
#define PT_D2_2048 0x58
#define PT_D2_4096 0x58
#define PT_D2_8192 0x5A

//Pressure and temperature commands
#define ADC_READ
#define PROM_READ Ax0
#define PT_RESET 0x1E
#define PT_PROM_READ 0xA0

//RH PROM Read
#define RH_PROM_READ 0xA0
#define RH_MEASURE_HOLD 0xE5
#define RH_MEASURE_NO_HOLD 0xF5
#define RH_RESET 0xFE

#define TIMEOUT 10000
/*
typedef struct {
    //PT PROM Values
    uint16_t PRESSURE_SENSITIVITY; //C1
    uint16_t PRESSURE_OFFSET; //C2
    uint16_t TC_PRESSURE_SENSITIVITY; //C3
    uint16_t TC_PRESSURE_OFFSET; //C4
    uint16_t TEMP_REF; //C5
    uint16_t TC_TEMP; //C6

    //Read Values
    uint32_t DIGITAL_PRESSURE; //D1
    uint32_t DIGITAL_TEMPERATURE; //D2

    //RH PROM Values

} PHT_MS8607;
*/
HAL_StatusTypeDef PHT_Init();
void PHT_Run(void);
int32_t PHT_GetTemperature(void);
int32_t PHT_GetPressure(void);

#endif /* INC_PHTMS8607_H_ */
