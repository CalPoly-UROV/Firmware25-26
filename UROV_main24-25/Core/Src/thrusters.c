
#include <string.h>
#include "main.h"
#include "custom_gpio.h"
#include "thrusters.h"

// VICTOR NOTE: THIS CODE USES TIM3 with PC6, PC7, PC8, PC9 and TIM5 with PA0, PA1, PA2, PA3

#define PASTER(x, y) x ## y
#define EVALUATOR(x, y) PASTER(x, y)

#define PWM_MODE_1

#define UPPER_TIM_n 5 //set this
#define LOWER_TIM_n 3 //set this
#define _UPPER_TIM EVALUATOR(TIM, UPPER_TIM_n)
#define _LOWER_TIM EVALUATOR(TIM, LOWER_TIM_n)

#define UPPER_TIMER (_UPPER_TIM)
#define LOWER_TIMER (_LOWER_TIM)


#define PRESCALE (1)
#define TIM_CLK (42000000 / (PRESCALE + 1)) //Hz

#define PWM_PERIOD (2500) //us
#define MAX_THROTTLE_PERIOD (1900) //us
#define MIN_THROTTLE_PERIOD (1100) //us

#define PWM_FREQ (400) //hz
#define MAX_THROTTLE_FREQ (52631) //frequency for 1900us * 100
#define MIN_THROTTLE_FREQ (90909) //frequency for 1100us *100
#define MAX_THROTTLE (TIM_CLK*100/MAX_THROTTLE_FREQ) //max ccr value
#define MIN_THROTTLE (TIM_CLK*100/MIN_THROTTLE_FREQ) //min ccr value
#define ARR_VALUE (TIM_CLK/PWM_FREQ) //make sure this is <65535 (16 bits)

//#define MAX_THROTTLE (TIM_CLK / ) //max ccr value
//#define MIN_THROTTLE (PRESCALE_CLK * MIN_THROTTLE_PERIOD) //min ccr value

//#define ARR_VALUE (PRESCALE_CLK * PWM_PERIOD) //make sure this is <65535 (16 bits)

//set mode to pwm mode 1 on both OCxM bit fields, enable preloading
#define CCMR_CFG (0x6 << 4 | 0x6 << 12 | 0x1 << 11 | 0x1 << 3)
#define CCEN_ENABLE_ALL (0x1 << 12 | 0x1 << 8 | 0x1 << 4 | 0x1)
#define CR1_ENABLE_TIMER (0x1)

#define clk_enable(n) (0x1 << ((n)-2)) //probably not portable or super safe

//PWM CCR value LUT
uint16_t ccr_vals[256];

//pointers to CCRs
__IO uint32_t* thrusters[8];

int init_thrusters(void)
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOCEN; //turn on gpio ports enable port d for TIM4
	RCC->APB1ENR |= clk_enable(UPPER_TIM_n) | clk_enable(LOWER_TIM_n); //turn on timers

	mpininit(GPIOA, (uint32_t[]){0,1,2,3}, 4, MAF, OTPUSHPULL, OSLOW, PUPDNONE, AF2);//pins for TIM5
	mpininit(GPIOC, (uint32_t[]){6,7,8,9}, 4, MAF, OTPUSHPULL, OSLOW, PUPDNONE, AF2);//pins for TIM3


	UPPER_TIMER->ARR = ARR_VALUE;
	LOWER_TIMER->ARR = ARR_VALUE;
	UPPER_TIMER->PSC = PRESCALE;
	LOWER_TIMER->PSC = PRESCALE;

	UPPER_TIMER->CCMR1 = CCMR_CFG;
	UPPER_TIMER->CCMR2 = CCMR_CFG;
	LOWER_TIMER->CCMR1 = CCMR_CFG;
	LOWER_TIMER->CCMR2 = CCMR_CFG;

	UPPER_TIMER->CCER |= CCEN_ENABLE_ALL;
	LOWER_TIMER->CCER |= CCEN_ENABLE_ALL;

	//generate LUT for throttle values
	for(int i = 0; i < 255; i++){
		ccr_vals[i] = (MAX_THROTTLE - MIN_THROTTLE)/255 * i + MIN_THROTTLE;
	}

	thrusters[0] = &UPPER_TIMER->CCR1;
	thrusters[1] = &UPPER_TIMER->CCR2;
	thrusters[2] = &UPPER_TIMER->CCR3;
	thrusters[3] = &UPPER_TIMER->CCR4;
	thrusters[4] = &LOWER_TIMER->CCR1;
	thrusters[5] = &LOWER_TIMER->CCR2;
	thrusters[6] = &LOWER_TIMER->CCR3;
	thrusters[7] = &LOWER_TIMER->CCR4;

	//enable timers
	UPPER_TIMER->CR1 |= CR1_ENABLE_TIMER;
	LOWER_TIMER->CR1 |= CR1_ENABLE_TIMER;

	//calibration routine
	uint8_t calibration_vals[8];
	for(int i = 255; i > 0; i--){
		memset(calibration_vals, i, 8);
		set_all_thrusters(calibration_vals);
		HAL_Delay(1);
	}

	//zero out thrust
	memset(calibration_vals, 127, 8);
	set_all_thrusters(calibration_vals);

	return 0;
}

int set_thruster(uint8_t index, uint8_t pwm)
{
	if(index < 8){
		*thrusters[index] = ccr_vals[(int8_t)(pwm) + 128];
		return 0;
	}

	return 1;
}

int set_all_thrusters(uint8_t* values)
{
	int8_t* s_values = (int8_t*) values;
	for(int i = 0; i < 8; i ++){
		*thrusters[i] = ccr_vals[s_values[i] + 128];
	}
	return 0;
}

