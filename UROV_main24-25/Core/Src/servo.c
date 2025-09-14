/*
 * servo.c
 *
 * Created on: Feb 22, 2025
 * Author: closed clock
 * IMPORTANT NOTES ON SERVO IM DRIVING (for my reference):
 * PWM range: 500 - 2500 uSec (goes clockwise)
 * Neutral @ 1500 uSec
 *
 * CODE USES TIM4: PB6, PB7, PB8
 *
 */

#include "main.h"
#include "custom_gpio.h"
#include "servo.h"

// Servo pin definitions
#define SERVO1_PIN 6 // TIM4 CH1
#define SERVO2_PIN 7 // TIM4 CH2
#define SERVO3_PIN 8 // TIM4 CH3

// Timer configuration
#define SERVO_PRESCALE (1)
#define SERVO_TIM_CLK (42000000 / (SERVO_PRESCALE + 1)) // 21MHz

// Servo PWM specifications
#define SERVO_PWM_FREQ (50) // 50Hz standard for servos
#define SERVO_ARR_VALUE (SERVO_TIM_CLK/SERVO_PWM_FREQ)

// Pulse width specifications in microseconds
#define SERVO_MIN_PULSE (500)
#define SERVO_MAX_PULSE (2500)
#define SERVO_NEUTRAL_PULSE (1500)

// Convert microseconds to timer counts
#define US_TO_COUNTS(us) ((us) * (SERVO_TIM_CLK/1000000))
#define SERVO_MIN_CCR US_TO_COUNTS(SERVO_MIN_PULSE)
#define SERVO_MAX_CCR US_TO_COUNTS(SERVO_MAX_PULSE)
#define SERVO_NEUTRAL_CCR US_TO_COUNTS(SERVO_NEUTRAL_PULSE)

// PWM mode definitions
#define SERVO_CCMR_CFG (0x6 << 4 | 0x6 << 12 | 0x1 << 11 | 0x1 << 3) // PWM mode 1 with preload
#define SERVO_CCEN_ENABLE (0x1 | 0x1 << 4 | 0x1 << 8) // Enable channels 1-3
#define SERVO_CR1_ENABLE (0x1) // Timer enable bit

// PWM CCR value lookup table for angle to pulse width conversion
uint16_t servo_ccr_vals[256];

// Pointers to CCR registers
__IO uint32_t* servos[3];

void Servo_init(void)
{
    // Enable GPIO and Timer clocks
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN; // Enable GPIOB clock
    RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;  // Enable TIM4 clock

    // Configure GPIO pins for TIM4 alternate function
    mpininit(GPIOB, (uint32_t[]){SERVO1_PIN, SERVO2_PIN, SERVO3_PIN}, 3,
             GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_NOPULL, GPIO_AF2_TIM4);

    // Timer configuration
    TIM4->PSC = SERVO_PRESCALE;
    TIM4->ARR = SERVO_ARR_VALUE;

    // Configure PWM mode
    TIM4->CCMR1 = SERVO_CCMR_CFG; // Configure channels 1 & 2
    TIM4->CCMR2 = (0x6 << 4 | 0x1 << 3); // Configure channel 3
    TIM4->CCER |= SERVO_CCEN_ENABLE; // Enable output on channels 1-3

    // Generate lookup table for angle to pulse width conversion
    for(int i = 0; i < 256; i++) {
        servo_ccr_vals[i] = SERVO_MIN_CCR +
                           ((SERVO_MAX_CCR - SERVO_MIN_CCR) * i / 255);
    }

    // Set up pointers to CCR registers for easy access
    servos[0] = &TIM4->CCR1;
    servos[1] = &TIM4->CCR2;
    servos[2] = &TIM4->CCR3;

    // Initialize servos to neutral position
    *servos[0] = SERVO_NEUTRAL_CCR;
    *servos[1] = SERVO_NEUTRAL_CCR;
    *servos[2] = SERVO_NEUTRAL_CCR;

    // Enable timer
    TIM4->CR1 |= SERVO_CR1_ENABLE;
}

void Servo_SetPosition(uint8_t servo, uint16_t pulse_width)
{
    if(servo < 3) {
        // Convert pulse width in microseconds to timer counts
        uint32_t counts = US_TO_COUNTS(pulse_width);

        // Constrain to valid range
        if(counts < SERVO_MIN_CCR) counts = SERVO_MIN_CCR;
        if(counts > SERVO_MAX_CCR) counts = SERVO_MAX_CCR;

        // Set position
        *servos[servo] = counts;
    }
}

void Servo_SetAngle(uint8_t servo, uint16_t angle)
{
    if(servo < 3 && angle <= 256) {
        // Use the lookup table for a more efficient conversion
        *servos[servo] = servo_ccr_vals[angle];
    }
}

void Servo_SetNeutral(uint8_t servo)
{
    if(servo < 3) {
        *servos[servo] = SERVO_NEUTRAL_CCR;
    }
}

void Servo_SetAllNeutral(void)
{
    for(uint8_t i = 0; i < 3; i++) {
        *servos[i] = SERVO_NEUTRAL_CCR;
    }
}
