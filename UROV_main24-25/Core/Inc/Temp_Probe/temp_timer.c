#include "temp_timer.h"

int temp_final = 0;

uint16_t read = 0;
int read_index = 0;

TempProbe_STATE state = s_STOP;

int response = 0;

uint16_t to_write = command_CONVERT_T;
int write_index = 0;

int conv_skip_1_arr = 0;

void GPIO_Init(void){
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	GPIO_InitStruct.Pin = TEMPPROBE_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(TEMPPROBE_PORT, &GPIO_InitStruct);
}

void TIM2_Init(void)
{

	RCC -> APB1ENR |= 1U;
	TIM2 -> PSC = 41U;


}

void calc_temp(){
	uint16_t t = 0;
	double temp_d;

	read = read >> 1;
	t = read << 5;

	for (int i = 6; i > -5; i--) {
		if ((t & 0x8000) == 0x8000){
			temp_d += pow(2,i);
		}
		t <<= 1;
	}

	temp_final = (int)(temp_d * 100);
}

void switch_state(TempProbe_STATE ns){
	TIM2->CR1 &= 0xFFFE; //PAUSES COUNTER
	TIM2->CNT = (int32_t)0; //RESET COUNT

	TIM2->DIER &= -1U ^ 7U; //DISABLES ALL INTERRUPT FLAGS
	TIM2->CCER &= -1 ^ 1U; //DISABLE CCR1
	TIM2->CCER &= -1 ^ 16U;	//DISABLE CCR2

	TIM2->CCR1 = 0x0; //DISABLE CCR1 COUUNT
	TIM2->CCR2 = 0x0; //DISABLE CCR2 COUNT

	TIM2->ARR = 0x1; //DISABLE ARR

	switch (ns) {
	    case s_CONV_RESET:
		case s_READ_RESET:
			TIM2->ARR = 1000;
			TIM2->CCR1 = 500;
			TIM2->CCR2 = 575;

			TIM2->DIER |= 7U; //ENABLE ALL INTERRUPTS
			TIM2->CCER |= 1U; //ENABLE CCR1
			TIM2->CCER |= 16U; //ENABLE CCR2

			HAL_GPIO_WritePin(TEMPPROBE_PORT, TEMPPROBE_PIN, 0);
			break;

		case s_CONV_WRITE:
			TIM2->ARR = 100;
			TIM2->CCR1 = 60;
			TIM2->DIER |= 3U; //ENABLE ARR & CCR1
			TIM2->CCER |= 1U; //ENABLE CCR1

			//SET WRITE ARRAY
			write_index = 0;
			to_write = command_CONVERT_T;
			break;

		case s_READ_WRITE:
			TIM2->ARR = 100;
			TIM2->CCR1 = 60;
			TIM2->DIER |= 3U; //ENABLE ARR &CCR1
			TIM2->CCER |= 1U; //ENABLE CCR1

			//SET WRITE ARRAY
			write_index = 0;
			to_write = command_READ_SPAD;
			break;

		case s_READ:
			TIM2->ARR = 100;
			TIM2->CCR1 = 15;
			TIM2->DIER |= 3U; // ENABLE ARR & CCR1
			TIM2->CCER |= 1U; //ENABLE CCR1

			read_index = 0;
			read = 0;
			break;

		case s_CONVERT:
			TIM2->ARR = 1000000;
			TIM2->DIER |= 1U; // ENABLE ARR

			conv_skip_1_arr = 0;
			calc_temp();
			break;

		case s_STOP:
			break;
		}

	state = ns;
	TIM2->CR1 |= 1U; //ENABLE TIMER
}

void s_Reset(int iflag, TempProbe_STATE ns){
	switch(iflag & 7U){
		case 0x1: //ARR
			if(response){
				switch_state(ns);
			}else{
				switch_state(s_CONV_RESET);
			}
			break;

		case 0x2: //CCR1
			HAL_GPIO_WritePin(TEMPPROBE_PORT, TEMPPROBE_PIN, 1);
			break;

		case 0x4: //CCR2
			response = 1U ^ HAL_GPIO_ReadPin(TEMPPROBE_PORT, TEMPPROBE_PIN);
			break;
	}
}

void s_Write(int iflag, TempProbe_STATE ns){
	switch(iflag & 3U){
		case 0x1: //ARR
			if(write_index != 16){
				int bit = to_write & 1U;

				HAL_GPIO_WritePin(TEMPPROBE_PORT, TEMPPROBE_PIN, 0);
				if(bit){
					HAL_GPIO_WritePin(TEMPPROBE_PORT, TEMPPROBE_PIN, 1);
				}else{
				}

				to_write = to_write >> 1;
				write_index++;
			}else{
				switch_state(ns);
			}
			break;

		case 0x2: //CCR1
			HAL_GPIO_WritePin(TEMPPROBE_PORT, TEMPPROBE_PIN, 1);
			break;
	}
}

void s_Read(int iflag){
	switch(iflag & 3U){
		case 0x1: //ARR
			if(read_index != 16){
					HAL_GPIO_WritePin(TEMPPROBE_PORT, TEMPPROBE_PIN, 0);
					HAL_GPIO_WritePin(TEMPPROBE_PORT, TEMPPROBE_PIN, 1);

				}else{
					switch_state(s_CONV_RESET);
				}
			break;

		case 0x2: //CC1
			int read_bit = HAL_GPIO_ReadPin(TEMPPROBE_PORT, TEMPPROBE_PIN);
			read = read >> 1;
			read |= read_bit << 15;
			read_index++;
			break;
	}
}

void s_Convert(int iflag){
	if(conv_skip_1_arr){
		switch_state(s_READ_RESET);
	}
	else{
		conv_skip_1_arr  = 1;
	}
}

void TIM2_IRQHandler(void)
{
	uint16_t iflag = TIM2 -> SR;

	switch (state) {
		case s_CONV_RESET:
			s_Reset(iflag, s_CONV_WRITE);
			break;

		case s_CONV_WRITE:
			s_Write(iflag, s_CONVERT);
			break;

		case s_CONVERT:
			s_Convert(iflag);
			break;

		case s_READ_RESET:
			s_Reset(iflag, s_READ_WRITE);
			break;

		case s_READ_WRITE:
			s_Write(iflag, s_READ);
			break;

		case s_READ:
			s_Read(iflag);
			break;

		case s_STOP:
			break;
		}

	TIM2 -> SR &= 0xFFF8; //Clear Interrupt Flags
}

void TempProbe_Init(){

	GPIO_Init();
	TIM2_Init();

	NVIC_EnableIRQ(TIM2_IRQn);//enable TIM2 interrupt
	__enable_irq();
}

void TempProbe_Start(){
	switch_state(s_CONV_RESET);
}

void TempProbe_Stop(){
	switch_state(s_STOP);
}

TempProbe_Connection TempProbe_GetConn(){
	if(response){
		return TempProbe_OK;
	}
	return TempProbe_DC;
}

int TempProbe_GetTemp(){
	return temp_final;
}
