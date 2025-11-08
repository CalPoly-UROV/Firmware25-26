#include "main.h"
#include "t200driver.h"
/*
 * NUCLEO-F439ZI only
 * use 32 bit timers 2 and 5 only
 * make sure your frequency is 50hz
 *
 * AFR stuff:
 * 		afr_index → which AFR register to use (0 = AFR[0], 1 = AFR[1])
	    afr_shift → bit position of the 4-bit AF field within that AFR
	    af_num    → actual alternate function number (AF1 = TIM1/TIM2, AF2 = TIM3/TIM4, etc.)
 *
 * Example 1: TIM2_CH1 on PA5, pre-scale of 15(16mhz/(15+1) is 1mhz)
 * PWM_Init(TIM2, GPIOA, 5, 1, 15, 19999, 1, 3, 1);//defaults to 1500 stop band on initialization
 * PWM_SetDuty(TIM2, 1, 250); // 25%
 */



// Configure PWM to allow for https://www.amazon.com/Rcmall-Torque-GX3270BLS-Digital-Brushless/dp/B0DGD83PNV?th=1




void useHSE(void) {
    RCC->CR |= RCC_CR_HSEON; //Turn on HSE oscillator
    while (!(RCC->CR & RCC_CR_HSERDY)); //

    if (RCC->CR & RCC_CR_PLLRDY) {       // PLL ready → use PLL
        RCC->CFGR = (RCC->CFGR & ~RCC_CFGR_SW) | RCC_CFGR_SW_PLL;
        while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
    } else {                              // fallback → HSE direct
        RCC->CFGR = (RCC->CFGR & ~RCC_CFGR_SW) | RCC_CFGR_SW_HSE;
        while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSE);
    }
}

void PWM_Init(TIM_TypeDef *TIMx, GPIO_TypeDef *GPIOx, uint32_t pin, uint8_t channel, uint32_t prescaler, uint32_t autoReload, uint8_t afr_index, uint8_t afr_shift, uint8_t af_num){
	TIMx->CR1 &= ~TIM_CR1_CEN;   // Stop timer during config
	//-----------------------------------------------------------------------------------
	// ENABLE CLOCKS
	//-----------------------------------------------------------------------------------
	if(GPIOx == GPIOA) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	else if(GPIOx == GPIOB) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	else if(GPIOx == GPIOC) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	else if(GPIOx == GPIOD) RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;

	if(TIMx == TIM2) RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	else if(TIMx == TIM5) RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;
	//-----------------------------------------------------------------------------------
	// PRELOAD CONFIGURATION — ensures updates happen only at period edge
	//-----------------------------------------------------------------------------------
	TIMx->CR1   |= TIM_CR1_ARPE;     // preload enable for ARR
	TIMx->EGR   |= TIM_EGR_UG;       // force update event to latch registers
	//-----------------------------------------------------------------------------------
	// GPIO CONFIGURATION
	//-----------------------------------------------------------------------------------
	GPIOx->MODER &= ~(3 << (pin * 2));   // clear moder bits
	GPIOx->MODER |=  (2 << (pin * 2));   // set to alternate function

	GPIOx->AFR[afr_index] &= ~(0xF << afr_shift);
	GPIOx->AFR[afr_index] |=  (af_num << afr_shift);  // AF1 = TIM1/TIM2 (for many STM32s)
	// NOTE: For other timers/pins, adjust AF number (AF2, AF3, etc.) as needed
	//-----------------------------------------------------------------------------------
	// TIMER BASE CONFIG
	//-----------------------------------------------------------------------------------
	TIMx->PSC = prescaler;           // 16 MHz / 15+1 = 1 MHz tick
	TIMx->ARR = autoReload;         // 1 ms period -> 1 kHz PWM
	switch(channel) {
	  case 1: TIMx->CCR1 = 1500; break;
	  case 2: TIMx->CCR2 = 1500; break;
	  case 3: TIMx->CCR3 = 1500; break;
	  case 4: TIMx->CCR4 = 1500; break;
	}
	TIMx->EGR |= TIM_EGR_UG; //latch all settings. forces all settings to activate NOW
	//-----------------------------------------------------------------------------------
	// CHANNEL CONFIGURATION
	//-----------------------------------------------------------------------------------
	switch(channel){
		case 1:
			TIMx->CCMR1 &= ~TIM_CCMR1_OC1M;//pwm mode 1
			TIMx->CCMR1 |=  (6 << 4) | TIM_CCMR1_OC1PE;  // enable preload
			TIMx->CCER  |=  TIM_CCER_CC1E;               // enable output
			break;

		case 2:
			TIMx->CCMR1 &= ~TIM_CCMR1_OC2M;
			TIMx->CCMR1 |=  (6 << 12) | TIM_CCMR1_OC2PE;
			TIMx->CCER  |=  TIM_CCER_CC2E;
			break;

		case 3:
			TIMx->CCMR2 &= ~TIM_CCMR2_OC3M;
			TIMx->CCMR2 |=  (6 << 4) | TIM_CCMR2_OC3PE;
			TIMx->CCER  |=  TIM_CCER_CC3E;
			break;

		case 4:
			TIMx->CCMR2 &= ~TIM_CCMR2_OC4M;
			TIMx->CCMR2 |=  (6 << 12) | TIM_CCMR2_OC4PE;
			TIMx->CCER  |=  TIM_CCER_CC4E;
			break;
	}
	//-----------------------------------------------------------------------------------
	// START TIMER
	//-----------------------------------------------------------------------------------
	TIMx->CR1 |= TIM_CR1_CEN;
}

void PWM_SetDuty(TIM_TypeDef *TIMx, uint8_t channel, uint32_t us){//microsecond
	if(us > 1900) us = 1900;
	if(us < 1100) us = 1100;

	switch(channel){
		case 1: TIMx->CCR1 = us; break;
		case 2: TIMx->CCR2 = us; break;
		case 3: TIMx->CCR3 = us; break;
		case 4: TIMx->CCR4 = us; break;
	}
}
