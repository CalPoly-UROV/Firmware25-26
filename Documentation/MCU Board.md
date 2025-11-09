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
| TIM3_CH1 | B4  |
| TIM3_CH2 | B5  |
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
| # | 1   | 2   | 3   | 4   |
|---|-----|-----|-----|-----|
| 1 | C10 | C11 | C9  | C8  |
| 2 | C12 | D2  | B8  | C6  |
| 3 | VDD | 5V  | B9  | C5  |
| 4 | BTO | GND | VDD | 5V  |
| 5 | F6  | NC  | GND | D8  |
| 6 | F7  | 3V3 | A5  | A12 |
| 7 | A13 | RST | A6  | A11 |
| 8 | A14 | 3V3 | A7  | B12 |
| 9 | A15 | 5V  | B6  | B11 |
|10 | GND | GND | C7  | GND |
|11 | B7  | GND | A9  | B2  |
|12 | C13 | VIN | A8  | B1  |
|13 | C14 |     | B10 | B15 |
|14 | C15 | A0  | B4  | B14 |
|15 | OSC1| A1  | B5  | B13 |
|16 | OSC2| A4  | B3  | GND |
|17 | VBAT| B0  | A10 | C4  |
|18 | C2  | C1  | A2  | F5  |
|19 | C3  | C0  | A3  | F4  |
|20 | D4  | D3  | GND | E8  |
|21 | D5  | G2  | D13 | F10 |
|22 | D6  | G3  | D12 | E7  |
|23 | D7  | E2  | D11 | D14 |
|24 | E3  | E4  | E10 | D15 |
|25 | GND | E5  | E12 | F14 |
|26 | F1  | F2  | E14 | E9  |
|27 | F0  | F8  | E15 | GND |
|28 | D1  | F9  | E13 | E11 |
|29 | D0  | G1  | F13 | F3  |
|30 | G0  | GND | F12 | F15 |
|31 | E1  | E6  | G14 | F11 |
|32 | G9  | G15 | GND | E0  |
|33 | G12 | G10 | D10 | G8  |
|34 | H2  | G13 | G7  | G5  |
|35 | D9  | G11 | G4  | G6  |

