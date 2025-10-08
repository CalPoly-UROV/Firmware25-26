#### UART & Serial Communication Protocols
Serial communication protocols use 1 or 2 signal lines to communicate a message. By flipping the line high and low at a specific rate, we can send data. Examples: SPI, I2C, UART. We'll be using UART.

UART stands for Universal Asynchronous Receiver-Transmitter.
	Asynchronous : There is no clock signal, instead both devices have to decide on a shared frequency ahead of time.
	Receiver-Transmitter: This protocol can be used for both receiving and sending data to and from both devices. There are 2 signal lines, Rx and Tx: Receive and Transmit.

We'll be using the devboard's in-built UART to USB to send serial data to computer. We need a way to display that serial data: Tera Term or another serial console program.

#### Setting up the IOC
![Image](https://github.com/CalPoly-UROV/Firmware25-26/blob/main/Documentation/Onboarding/Week%202%20Images/2.11.png) 
USART3 is the one that's connected to the devboard's UART to USB. S stands for synchronous. So USART has an option to share a clock line, but its optional.
![Image](https://github.com/CalPoly-UROV/Firmware25-26/blob/main/Documentation/Onboarding/Week%202%20Images/2.12.png) 
Make sure to change the default pins to PD9 and PD8. Then save & generate code.
#### Writing code in main.c

![Image](https://github.com/CalPoly-UROV/Firmware25-26/blob/main/Documentation/Onboarding/Week%202%20Images/2.21.png) 
`char* message` This is a character pointer, basically a string in c.  
`\n\r` This is an escape character. When the serial terminal receives these characters, they go to a newline  
##### `HAL_UART_Transmit(&huart3, (uint8_t*)&message, sizeof(message), 1);`  
HAL : Hardware Abstraction Layer  
	Documentation : https://sourcevu.sysprogs.com/stm32  

![Image](https://github.com/CalPoly-UROV/Firmware25-26/blob/main/Documentation/Onboarding/Week%202%20Images/2.13.png) 
`HAL_StatusTypeDef` This is the type of data that is returned by this function. We don't care about it.  
`UART_HandleTypeDef *huart` This points the function to the peripheral, UART3.  
`const uint8_t *pData` This points to the data we want to send. We are passing a `char*` so we cast it to a `uint8_t*`  
`uint16_t Size` How many bytes are being sent. `sizeof()` returns how long a variable is in bytes. 
