#include "main.h"

// call this to start receiving data
void comms_init(){
	uint8_t rx_byte;          // single-byte receive buffer h
	uint8_t rx_buffer[3];     // 3-byte packet
	uint8_t rx_index = 0;     // index into rx_buffer
	// 🟢 START UART reception (non-blocking)
 	 HAL_UART_Receive_IT(&huart3, &rx_byte, 1);
}

// Callback — called automatically when 1 byte is received
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if (huart->Instance == USART3)  // change to your UART
  {
    rx_buffer[rx_index++] = rx_byte;

    if (rx_index >= 3)  // when we have 3 bytes
    {
      process_packet(rx_buffer, rx_index);
      rx_index = 0;  // reset for next packet
    }

    // Re-arm the interrupt for next byte
    HAL_UART_Receive_IT(&huart3, &rx_byte, 1);
  }
}

// Process the 3-byte packet sent from topside
void process_packet(uint8_t *data, uint8_t len)
{
  if (len < 3) return;

  if (data[0] == 'S' && data[1] == 0x00 && data[2] == 0x01)
  {
      GPIOB-> ODR |= 1; // LED on
  }
  else if (data[0] == 'S' && data[1] == 0x00 && data[2] == 0x00)
  {
	  GPIOB-> ODR &= ~1; // LED off
  }

  const char *msg = "Great Success ! \r\n";
  HAL_UART_Transmit(&huart3, (uint8_t *)msg, strlen(msg), 50);
}
