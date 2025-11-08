## USB
https://embeddedprojects101.com/design-a-battery-powered-stm32-board-with-usb/

Use CP2102 USB-to-UART

MCU sends USART_TX and USART_RX to CP2102.  

CP2102 sends USB_D+ and USB_D1 to USB port

Use USART6  

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

## Dev Board
| 1    | 2   |     | 3   | 4   |
| ---- | --- | --- | --- | --- |
| C10  | C11 |     | C8  | C9  |
| C12  | D2  |     | C6  | B8  |
| VDD  | 5V  |     | C5  | B9  |
| BTO  | GND |     | 5V  | VDD |
| F6   | NC  |     | D8  | GND |
| F7   | 3V3 |     | A12 | A5  |
| A13  | RST |     | A11 | A6  |
| A14  | 3V3 |     | B12 | A7  |
| A15  | 5V  |     | B11 | B6  |
| GND  | GND |     | GND | C7  |
| B7   | GND |     | B2  | A9  |
| C13  | VIN |     | B1  | A8  |
| C14  |     |     | B15 | B10 |
| C15  | A0  |     | B14 | B4  |
| OSC1 | A1  |     | B13 | B5  |
| OSC2 | A4  |     | GND | B3  |
| VBAT | B0  |     | C4  | A10 |
| C2   | C1  |     | F5  | A2  |
| C3   | C0  |     | F4  | A3  |
| D4   | D3  |     | E8  | GND |
| D5   | G2  |     | F10 | D13 |
| D6   | G3  |     | E7  | D12 |
| D7   | E2  |     | D14 | D11 |
| E3   | E4  |     | D15 | E10 |
| GND  | E5  |     | F14 | E12 |
| F1   | F2  |     | E9  | E14 |
| F0   | F8  |     | GND | E15 |
| D1   | F9  |     | E11 | E13 |
| D0   | G1  |     | F3  | F13 |
| G0   | GND |     | F15 | F12 |
| E1   | E6  |     | F11 | G14 |
| G9   | G15 |     | E0  | GND |
| G12  | G10 |     | G8  | D10 |
| H2   | G13 |     | G5  | G7  |
| D9   | G11 |     | G6  | G4  |
