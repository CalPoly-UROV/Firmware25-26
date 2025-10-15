## USB
https://embeddedprojects101.com/design-a-battery-powered-stm32-board-with-usb/

Use CP2102 USB-to-UART

MCU sends USART_TX and USART_RX to CP2102.  

CP2102 sends USB_D+ and USB_D1 to USB port

Use USART1  

| Signal    | Pin |
| --------- | --- |
| USART3_TX | D8  |
| USART3_RX | D9  |

## SWD Debugger
https://www.hackster.io/patrick-fitzgerald2/program-stm32-arm-cortex-with-st-link-swd-interface-f0d9e2

4 lines: 3v3, GND, SWCLK, and SWDIO

| Signal | Pin |
| ------ | --- |
| SWDIO  | A13 |
| SWCLK  | A14 |


## Power
idk

## Thrusters and Servos (Timer Channels)
use PWM on 3 timers

TIM2 : 4 Horizontal Thrusters

TIM3 : 2 Vertical Thrusters

TIM4 : up to 4 Servos PWMs

| Signal   | Pin |
| -------- | --- |
| TIM2_CH1 | A15 |
| TIM2_CH2 | A1  |
| TIM2_CH3 | A2  |
| TIM2_CH4 | A3  |
| TIM3_CH1 | A6  |
| TIM3_CH2 | A7  |
| TIM4_CH1 | B6  |
| TIM4_CH2 | B7  |
| TIM4_CH3 | B8  |
| TIM4_CH4 | B9  |


## Sensors
### 1 UART, 2 SPI, and 2 I2C

| Signal    | Pin | Notes |
| --------- | --- | ----- |
| USART2_Tx | D5  |       |
| USART2_Rx | D6  |       |
| SPI1_SCK  | B3  |       |
| SPI1_MISO | B4  |       |
| SPI1_MOSI | B5  |       |
| SPI2_SCK  | B10 |       |
| SPI2_MISO | C2  |       |
| SPI2_MOSI | C3  |       |
| I2C1_SCL  | B6  |       |
| I2C1_SDA  | B7  |       |
| I2C2_SDA  | F0  |       |
| I2C2_SCL  | F1  |       |
|           |     |       |
