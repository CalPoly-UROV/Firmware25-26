# Command packet structure
 Commands are always sent as 10 bytes: 1 command byte + 9 argument bytes. 
 If a command uses fewer than 9 arguments, remaining argument bytes must be set to 0x00 (and are ignored by the receiver).

 An example of this if formatted below: 

| Byte Index | 0            | 1-9       |
| ---------- | ------------ | --------- |
| Data       | Command Byte | Arguments |

All commands return 2 byte
Byte 0 = echoed command byte, Byte 1 = return value (0x00 = success unless otherwise specified).

| Byte Index |  0                | 1            |
| ---------- | ----------------- | ------------ |
| Data       | Command Byte Echo | Return Value |


# Commands

## LED Commands
#### LED_BLNK (0x10)
Toggles LED state
Returns 0x00

## THS (Thruster) Commands

#### THS_SET (0x20)
Sets individual thrusters. Speed is an unsigned 8-bit value. 0 is full negative thrust, 255 is full forward thrust, 127 is zero thrust. Thrusters must be first booted before their speed can be changed.

| Byte Index | 0    | 1              | 2     |
| ---------- | ---- | -------------- | ----- |
| Data       | 0x20 | Thruster Index | Speed |

| Return Byte |                     |
| ----------- | ------------------- |
| 0           | Success             |
| 1           | Thruster not booted |

#### THS_SET_A (0x21)
Sets all thrusters. Speed is an unsigned 8-bit value. 0 is full negative thrust, 255 is full forward thrust, 127 is zero thrust. Thrusters must be first booted before their speed can be changed.

| Byte Index | 0    | 1                | 2                | 3                | 4                | 5                | 6                |
| ---------- | ---- | ---------------- | ---------------- | ---------------- | ---------------- | ---------------- | ---------------- |
| Data       | 0x21 | Thruster 0 Speed | Thruster 1 Speed | Thruster 2 Speed | Thruster 3 Speed | Thruster 4 Speed | Thruster 5 Speed |

| Return Byte |                                     |
| ----------- | ----------------------------------- |
| 0x00        | Success                             |
| 0x01        | At least one thruster is not booted |
#### THS_BT (0x22)
Boots individual thrusters by setting their PWM pulse widths to 1500ms. Thruster should do its boot up beeps.
Returns 0x00 on success. Returns 0x02 if thruster index is invalid.

| Byte Index | 0    | 1              |
| ---------- | ---- | -------------- |
| Data       | 0x22 | Thruster Index |
#### THS_BT_A (0x23)
Boots all thrusters.
Returns 0x00.

| Byte Index | 0    |
| ---------- | ---- |
| Data       | 0x23 |
#### THS_UNBT (0x24)
Unboots individual thrusters by setting their PWM pulse widths to 0ms. 
Returns 0x00 on success. Returns 0x02 if thruster index is invalid.

| Byte Index | 0    | 1              |
| ---------- | ---- | -------------- |
| Data       | 0x24 | Thruster Index |
#### THS_UNBT_A (0x25)
Unboots all thrusters.
Returns 0x00.

| Byte Index | 0    |
| ---------- | ---- |
| Data       | 0x25 |


## SEV (Servo) Commands
Servo commands use an angle in degrees (0–270).  
Angles are transmitted as **16-bit unsigned integers (uint16_t)** in command packets.

pulse_us = 500 + angle * 2000 / 270

| Angle (deg) | Approx. Pulse (µs)  | Meaning                   |
|------------:|--------------------:|--------------------------|
| 0           | 500                 | Minimum                  |
| 135         | ~1500               | Neutral (approximate)    |
| 270         | ~2500               | Maximum                  |

#### Return Codes

| Value | Meaning                       |
| ----- | ----------------------------- |
| 0x00  | Success                       |
| 0x01  | Not booted                    |
| 0x02  | Invalid index                 |
| 0x03  | Invalid angle                 |

#### SEV_SET (0x30)
Sets a single servo angle (degrees).

Command Packet (10 Bytes)
| Byte Index | 0    | 1                 | 2–3                    | 4–9                       |
|-----------:|------|-------------------|------------------------|---------------------------|
| Data       | 0x30 | Servo Index (0–3) | Angle (uint16, 0–270)  | Unused (0x00 recommended) |

Response (2 Bytes)
| Byte Index | 0           | 1           |
|-----------:|-------------|-------------|
| Data       | 0x30 (Echo) | Return Code |

Angle is transmitted as a 16-bit unsigned integer (uint16_t) (endianness per comms layer).
Valid range: 0–270 degrees.

#### SEV_SET_A (0x31)
Sets all servo angles (degrees).

Command Packet (10 Bytes)

| Byte Index | 0    | 1–2                      | 3–4                      | 5–6                      | 7–8                      | 9                         |
|-----------:|------|--------------------------|--------------------------|--------------------------|--------------------------|---------------------------|
| Data       | 0x31 | Servo 0 Angle (uint16)   | Servo 1 Angle (uint16)   | Servo 2 Angle (uint16)   | Servo 3 Angle (uint16)   | Unused (0x00 recommended) |

Response (2 Bytes)

| Byte Index | 0           | 1           |
|-----------:|-------------|-------------|
| Data       | 0x31 (Echo) | Return Code |

Servo angles are transmitted as 16-bit unsigned integers (uint16_t).  
Valid range per servo: 0–270 degrees.

#### SEV_BT (0x32)
Boots one servo channel.  
Booting sets the servo output to **1500 µs (neutral position)**.

Command Packet (10 Bytes)

| Byte Index | 0    | 1                 | 2–9                       |
|-----------:|------|-------------------|---------------------------|
| Data       | 0x32 | Servo Index (0–3) | Unused (0x00 recommended) |

Response (2 Bytes)

| Byte Index | 0           | 1           |
|-----------:|-------------|-------------|
| Data       | 0x32 (Echo) | Return Code |

#### SEV_BT_A (0x33)
Boots all servo channels.  
Booting sets all servo outputs to **1500 µs (neutral position)** and sets the global boot flag.

Command Packet (10 Bytes)

| Byte Index | 0    | 1–9                       |
|-----------:|------|---------------------------|
| Data       | 0x33 | Unused (0x00 recommended) |

Response (2 Bytes)

| Byte Index | 0           | 1           |
|-----------:|-------------|-------------|
| Data       | 0x33 (Echo) | Return Code |

#### SEV_UNBT (0x34)
Unboots (disables) one servo channel.  
Unbooting sets the servo output to **0 µs (output disabled)**.

Command Packet (10 Bytes)

| Byte Index | 0    | 1                 | 2–9                       |
|-----------:|------|-------------------|---------------------------|
| Data       | 0x34 | Servo Index (0–3) | Unused (0x00 recommended) |

Response (2 Bytes)

| Byte Index | 0           | 1           |
|-----------:|-------------|-------------|
| Data       | 0x34 (Echo) | Return Code |

#### SEV_UNBT_A (0x35)
Unboots (disables) all servo channels.  
Unbooting sets all servo outputs to **0 µs (output disabled)** and clears the global boot flag.

Command Packet (10 Bytes)

| Byte Index | 0    | 1–9                       |
|-----------:|------|---------------------------|
| Data       | 0x35 | Unused (0x00 recommended) |

Response (2 Bytes)

| Byte Index | 0           | 1           |
|-----------:|-------------|-------------|
| Data       | 0x35 (Echo) | Return Code |

## BOP (Breakout Output Pin) Commands

##### BOP_HIGH (0x40)

Sets breakout pins HIGH.

Pins Affected:
PB6, PB7
PE2, PE4, PE5, PE6
PF0, PF1

Command Packet
| Byte Index | 0    | 1–9    |
| ---------- | ---- | ------ |
| Data       | 0x40 | Unused |

Respnse
| Byte Index | 0           | 1    |
| ---------- | ----------- | ---- |
| Data       | 0x40 (Echo) | 0x00 |

#### BOP_LOW (0x41)

Sets breakout pins LOW.

Pins Affected:
PB6, PB7
PE2, PE4, PE5, PE6
PF0, PF1

Command Packet
| Byte Index | 0    | 1–9    |
| ---------- | ---- | ------ |
| Data       | 0x41 | Unused |

Response Packet
| Byte Index | 0           | 1    |
| ---------- | ----------- | ---- |
| Data       | 0x41 (Echo) | 0x00 |

#### Boot Requirement

Set commands return error if: sev_boot == 0
