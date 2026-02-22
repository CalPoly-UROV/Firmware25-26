# Command Packet Structure

Commands are always sent as **10 bytes total**:

If a command uses fewer than 9 arguments, the remaining argument bytes **must be set to `0x00`** and are ignored by the receiver.

## Packet Format

| Byte Index | 0            | 1–9       |
| ---------- | ------------ | --------- |
| Data       | Command Byte | Arguments |

## Command Responses

All commands return at least **3 bytes**:

- **Byte 0** = echoed command byte  
- **Byte 1** = status (`0x00` = success unless otherwise specified)
- **Byte 2** = size of next data packet (nonzero only for data commands)

| Byte Index | 0            | 1      | 2                |
| ---------- | ------------ | ------ | ---------------- |
| Data       | Command Echo | Status | Data Packet Size |

For IMU commands which return more data, the 3rd byte will signify how many bytes large the ensuing data packet will be. The data packet will be transmitted immediately after the 3-byte response packet.

# Commands

## LED Commands
#### LED_BLNK (0x10)
Toggles LED state
Status: 0x00

## THS (Thruster) Commands

Thruster speed commands are given as unsigned 8-bit integers. They are converted to PWM pulse width using the following equation:
**'pulse_us = 1500 + ((int32_t)speed - 127) * 400 / 127'**

| Speed Command | Approx. Pulse (µs) | Meaning      |
| ------------: | -----------------: | ------------ |
|             0 |              ~1100 | Full Reverse |
|           127 |               1500 | Neutral      |
|           255 |              ~1900 | Full Forward |

- Casting to `int32_t` prevents unsigned wraparound when subtracting 127.  
- The mapping produces approximately ±400 µs around neutral.  
- Small rounding error (≈ ±3 µs at extremes) is normal and acceptable for ESC control.

| Status |                        |
| ------ | ---------------------- |
| 0x00   | Success                |
| 0x01   | Thruster not booted    |
| 0x02   | Invalid thruster index |

#### THS_SET (0x20)
Sets individual thrusters. Thrusters must be first booted before their speed can be changed.

| Byte Index | 0    | 1                    | 2              |
| ---------- | ---- | -------------------- | -------------- |
| Data       | 0x20 | Thruster Index (0-5) | Speed (uin8_t) |

#### THS_SET_A (0x21)
Sets all thrusters. Thrusters must be first booted before their speed can be changed.

| Byte Index | 0    | 1                          | 2                          | 3                          | 4                          | 5                          | 6                          |
| ---------- | ---- | -------------------------- | -------------------------- | -------------------------- | -------------------------- | -------------------------- | -------------------------- |
| Data       | 0x21 | Thruster 0 Speed (uint8_t) | Thruster 1 Speed (uint8_t) | Thruster 2 Speed (uint8_t) | Thruster 3 Speed (uint8_t) | Thruster 4 Speed (uint8_t) | Thruster 5 Speed (uint8_t) |
#### THS_BT (0x22)
Boots individual thrusters by setting their PWM pulse widths to 1500ms. Thruster should do its boot up beeps.

| Byte Index | 0    | 1                    |
| ---------- | ---- | -------------------- |
| Data       | 0x22 | Thruster Index (0-5) |
#### THS_BT_A (0x23)
Boots all thrusters.

| Byte Index | 0    |
| ---------- | ---- |
| Data       | 0x23 |
#### THS_UNBT (0x24)
Unboots individual thrusters by setting their PWM pulse widths to 0ms. 

| Byte Index | 0    | 1                    |
| ---------- | ---- | -------------------- |
| Data       | 0x24 | Thruster Index (0-5) |
#### THS_UNBT_A (0x25)
Unboots all thrusters.

| Byte Index | 0    |
| ---------- | ---- |
| Data       | 0x25 |
## SEV (Servo) Commands
Servo commands use an angle in degrees (0–270).  
Angles are transmitted as **16-bit unsigned integers (uint16_t)** in command packets.
Angles are converted to PWM pulse widths with the following equation: **'pulse_us = 500 + angle * 2000 / 270'**

| Angle (deg) | Approx. Pulse (µs)  | Meaning                   |
|------------:|--------------------:|--------------------------|
| 0           | 500                 | Minimum                  |
| 135         | ~1500               | Neutral (approximate)    |
| 270         | ~2500               | Maximum                  |

| Status |                     |
| ------ | ------------------- |
| 0x00   | Success             |
| 0x01   | Servo not booted    |
| 0x02   | Invalid servo index |
| 0x03   | Invalid angle       |

#### SEV_SET (0x30)
Sets a single servo angle.

| Byte Index | 0    | 1                 | 2–3                   |
| ---------: | ---- | ----------------- | --------------------- |
|       Data | 0x30 | Servo Index (0–3) | Angle (uint16, 0–270) |
#### SEV_SET_A (0x31)
Sets all servo angles.

| Byte Index | 0    | 1–2                    | 3–4                    | 5–6                    | 7–8                    |
| ---------: | ---- | ---------------------- | ---------------------- | ---------------------- | ---------------------- |
|       Data | 0x31 | Servo 0 Angle (uint16) | Servo 1 Angle (uint16) | Servo 2 Angle (uint16) | Servo 3 Angle (uint16) |

#### SEV_BT (0x32)
Boots one servo channel.  
Booting sets the servo output to **1500 µs (neutral position)**.

| Byte Index | 0    | 1                 |
| ---------: | ---- | ----------------- |
|       Data | 0x32 | Servo Index (0–3) |

#### SEV_BT_A (0x33)
Boots all servo channels.  
Booting sets all servo outputs to **1500 µs (neutral position)**.

| Byte Index | 0    |
| ---------: | ---- |
|       Data | 0x33 |

#### SEV_UNBT (0x34)
Unboots (disables) one servo channel.  
Unbooting sets the servo output to **0 µs (output disabled)**.

| Byte Index | 0    | 1                 |
| ---------: | ---- | ----------------- |
|       Data | 0x34 | Servo Index (0–3) |

#### SEV_UNBT_A (0x35)
Unboots (disables) all servo channels.  
Unbooting sets all servo outputs to **0 µs (output disabled)**.

| Byte Index | 0    |
| ---------: | ---- |
|       Data | 0x35 |

## BOP (Breakout Output Pin) Commands
There are 8 breakout pins on the MCU boards. These commands test the pin connections. Do not use while using any breakout components.

| Status |         |
| ------ | ------- |
| 0x00   | Success |

#### BOP_HIGH (0x40)

Sets breakout pins HIGH.

Pins Affected:
PB6, PB7
PE2, PE4, PE5, PE6
PF0, PF1

| Byte Index | 0    |
| ---------- | ---- |
| Data       | 0x40 |

#### BOP_LOW (0x41)

Sets breakout pins LOW.

Pins Affected:
PB6, PB7
PE2, PE4, PE5, PE6
PF0, PF1

| Byte Index | 0    |
| ---------- | ---- |
| Data       | 0x41 |

## BNO IMU Commands (Board IMU)
The BNO085 board-mounted IMU reports positional data: angle since boot and linear acceleration. The BNO085 uses UART-RVC mode and reports data to the STM32 at a rate of 50Hz over UART and has a 19-byte data packet. 

| Byte |               |
| ---- | ------------- |
| 0    | 0xAA (Header) |
| 1    | 0xAA (Header) |
| 2    | Report Index  |
| 3    | YAW_LSB       |
| 4    | YAW_MSB       |
| 5    | PITCH_LSB     |
| 6    | PITCH_MSB     |
| 7    | ROLL_LSB      |
| 8    | ROLL_MSB      |
| 9    | XACCEL_LSB    |
| 10   | XACCEL_MSB    |
| 11   | YACCEL_LSB    |
| 12   | YACCEL_MSB    |
| 13   | ZACCEL_LSB    |
| 14   | ZACCEL_MSB    |
| 15   | 0x00          |
| 16   | 0x00          |
| 17   | Reserved      |
| 18   | Checksum      |
Checksum is calculated as the sum of bytes 2-14 and byte 17. The driver will check the header and checksum bytes for validity. 
Each measurement is a 16-bit signed integer. Acceleration is in milli-gs and has no gravity compensation. Yaw has a range of +/- 180 degrees, Pitch has a range of +/- 90 degrees, Roll has a range of +/- 180 degrees. Angles are given in increments of 0.01 degrees. Ex: -1093 = -10.93 degrees. To determine orientation, apply rotations in the order of: yaw, pitch, then roll.

| Status |                    |
| ------ | ------------------ |
| 0x00   | Success            |
| 0x01   | Header Incorrect   |
| 0x02   | Checksum Incorrect |


#### BNO_READ (0xA0)
Returns the current data packet stored from the BNO085. Will only return a data packet if the status is 0x00.

| Byte Index | 0    |
| ---------- | ---- |
| Data       | 0xA0 |

| Data Packet Byte |            |
| ---------------- | ---------- |
| 0                | YAW_LSB    |
| 1                | YAW_MSB    |
| 2                | PITCH_LSB  |
| 3                | PITCH_MSB  |
| 4                | ROLL_LSB   |
| 5                | ROLL_MSB   |
| 6                | XACCEL_LSB |
| 7                | XACCEL_MSB |
| 8                | YACCEL_LSB |
| 9                | YACCEL_MSB |
| 10               | ZACCEL_LSB |
| 11               | ZACCEL_MSB |
| 12               | Checksum   |
If the return byte Checksum is calculated as sum of bytes 0-11. 

## MPU IMU Commands (Breakout IMU)
The MPU6050 IMU uses the board's breakout pins to communicate via I2C DMA. The driver accesses the MPU's data when the command is called. 

| Status |         |
| ------ | ------- |
| 0x00   | Success |
The MPU reports angular velocities and linear accelerations all as 16-bit signed integers. Angular velocity is in degrees/second in increments of 0.01 degrees/s. Linear acceleration is cm/s^2. Gravity is not compensated for.
##### MPU_READ (0xB0)
Accesses the MPU6050's memory via I2C DMA and returns a data packet.

| Byte Index | 0    |
| ---------- | ---- |
| Data       | 0xA0 |

| Data Packet Byte |               |
| ---------------- | ------------- |
| 0                | X_ANG_VEL_LSB |
| 1                | X_ANG_VEL_MSB |
| 2                | Y_ANG_VEL_LSB |
| 3                | Y_ANG_VEL_MSB |
| 4                | Z_ANG_VEL_LSB |
| 5                | Z_ANG_VEL_MSB |
| 6                | X_ACCEL_LSB   |
| 7                | X_ACCEL_MSB   |
| 8                | Y_ACCEL_LSB   |
| 9                | Y_ACCEL_MSB   |
| 10               | Z_ACCEL_LSB   |
| 11               | Z_ACCEL_MSB   |
| 12               | Checksum      |
Checksum is calculated as the sum of bytes 0-11.
