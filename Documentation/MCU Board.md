## USB
https://embeddedprojects101.com/design-a-battery-powered-stm32-board-with-usb/
Use CP2102 USB-to-UART

MCU sends USART_TX and USART_RX to CP2102.
CP2102 sends USB_D+ and USB_D1 to USB port

Use USART1
USART1_TX : PA9
USART1_RX : PA10

## SWD Debugger
https://www.hackster.io/patrick-fitzgerald2/program-stm32-arm-cortex-with-st-link-swd-interface-f0d9e2

4 lines: 3v3, GND, SWCLK, and SWDIO

SWDIO : PA13
SWCLK : PA14

## Power
idk

## Thrusters and Servos (Timer Channels)
use PWM on 3 timers

TIM2 : 4 Horizontal Thrusters
TIM3 : 2 Vertical Thrusters
TIM4 : up to 4 Servos

TIM2_CH1 : PA5
TIM2_CH2 : PA1
TIM2_CH3 : PA2
TIM2_CH4 : PA3
TIM3_CH1 : PA6
TIM3_CH2 : PA7

TIM4_CH1 : PB6
TIM4_CH2 : PB7
TIM4_CH3 : PB8
TIM4_CH4 : PB9

Does placing these signals on close traces do anything?

## Sensors
### IMU
Use SPI
