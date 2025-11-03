## USB
https://embeddedprojects101.com/design-a-battery-powered-stm32-board-with-usb/

Use CP2102 USB-to-UART

MCU sends USART_TX and USART_RX to CP2102.  

CP2102 sends USB_D+ and USB_D1 to USB port

Use USART6  

| Signal    | Pin |
| --------- | --- |
| USART3_TX | C6  |
| USART3_RX | C7  |

## SWD Debugger
https://www.hackster.io/patrick-fitzgerald2/program-stm32-arm-cortex-with-st-link-swd-interface-f0d9e2

4 lines: 3v3, GND, SWCLK, and SWDIO

| Signal | Pin |
| ------ | --- |
| SWDIO  | A13 |
| SWCLK  | A14 |
| SWO    | B3  |


## Power
idk

### Heartbeat LED
| Signal | Pin |
| ------ | --- |
| GPIO   | A10 | (may change)

## Thrusters and Servos (Timer Channels)
use PWM on 3 timers

TIM2 : 4 Horizontal Thrusters

TIM3 : 2 Vertical Thrusters

TIM4 : up to 4 Servos PWMs

| Signal   | Pin |
| -------- | --- |
| TIM2_CH1 | A0  |
| TIM2_CH2 | A1  |
| TIM2_CH3 | B10 |
| TIM2_CH4 | B11 |
| TIM3_CH1 | B3  |
| TIM3_CH2 | B4  |
| TIM4_CH1 | D12 |
| TIM4_CH2 | D13 |
| TIM4_CH3 | D14 |
| TIM4_CH4 | D15 |


## Sensors
### 1 UART, 2 SPI, and 2 I2C

| Signal    | Pin | Notes |
| --------- | --- | ----- |
| USART2_Tx | A1  |       |
| USART2_Rx | A2  |       |
|           |     |       |
| SPI1_NSS  | A4  |       |
| SPI1_SCK  | A5  |       |
| SPI1_MISO | A6  |       |
| SPI1_MOSI | A7  |       |
| IMU_WAKE  | E0  |       |
| IMU_RST   | E1  |       |
| IMU_INT   | E3  |       |
|           |     |       |
| SPI4_NSS  | E4  |       |
| SPI4_SCK  | E2  |       |
| SPI4_MISO | E5  |       |
| SPI4_MOSI | E6  |       |
|           |     |       |
| I2C1_SCL  | B6  |       |
| I2C1_SDA  | B7  |       |
| I2C2_SDA  | F0  |       |
| I2C2_SCL  | F1  |       |
|           |     |       |
