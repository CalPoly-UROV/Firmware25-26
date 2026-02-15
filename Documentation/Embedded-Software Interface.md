
# Command Packet Structure

Commands are always sent as **10 bytes total**:

If a command uses fewer than 9 arguments, the remaining argument bytes **must be set to `0x00`** and are ignored by the receiver.

### Packet Format

| Byte Index | 0            | 1–9       |
| ---------- | ------------ | --------- |
| Data       | Command Byte | Arguments |

Note: Multi-byte values (if used) are encoded **little-endian** (LSB first) unless a command specifies otherwise.

### Command Responses

All commands return **2 bytes**:

- **Byte 0** = echoed command byte  
- **Byte 1** = return value (`0x00` = success unless otherwise specified)

| Byte Index | 0                  | 1            |
| ---------- | ------------------ | ------------ |
| Data       | Command Byte Echo  | Return Value |

#### LED_BLNK (0x10)
Toggles LED state
Returns 0x00

# ------------------------THS (Thruster) Commands------------------------

Thruster speed commands are converted to PWM pulse width using:
pulse_us = 1100 + (uint32_t)(speed * 400 / 127)

### Speed Command Reference

| Speed Command | Approx. Pulse (µs) | Meaning |
|--------------:|-------------------:|---------|
| 0   | ~1100 | Full Reverse |
| 127 | 1500  | Neutral |
| 255 | ~1903 | Full Forward |

- Pulse width is computed using integer arithmetic (uint32_t).  
- The mapping produces approximately ±400 µs around neutral.  
- Small rounding error (≈ ±3 µs at extremes) is normal and acceptable for ESC control.

### Return Codes

| Value | Meaning             |
| ----: | ------------------- |
|  0x00 | Success             |
|  0x01 | Thruster not booted |
|  0x02 | Invalid index       |

#### THS_SET (0x20)
Sets individual thrusters. 
Speed is an unsigned 8-bit value. 
- `0` = full reverse
- `127` = neutral
- `255` = full forward
Thrusters must be first booted before their speed can be changed.

Command Packet (10 Bytes)
| Byte Index | 0    | 1                    | 2            | 3–9 |
|-----------:|------|----------------------|--------------|-----|
| Data       | 0x20 | Thruster Index (0–5) | Speed (uint8)| Unused (0x00 recommended) |

Response Packet (2 Bytes)
| Byte Index | 0           | 1           |
|-----------:|-------------|-------------|
| Data       | 0x20 (Echo) | Return Code |

#### THS_SET_A (0x21)
Sets all thrusters at once.
Speed is an unsigned 8-bit value. 
- `0` = full reverse
- `127` = neutral
- `255` = full forward
Thrusters must be first booted before their speed can be changed.

Command Packet (10 Bytes)
| Byte Index | 0    | 1                | 2                | 3                | 4                | 5                | 6                | 7–9 |
|-----------:|------|------------------|------------------|------------------|------------------|------------------|------------------|-----|
| Data       | 0x21 | Thruster 0 Speed | Thruster 1 Speed | Thruster 2 Speed | Thruster 3 Speed | Thruster 4 Speed | Thruster 5 Speed | Unused (0x00 recommended) |

Response Packet (2 Bytes)
| Byte Index | 0           | 1           |
|-----------:|-------------|-------------|
| Data       | 0x21 (Echo) | Return Code |

Return Codes for `THS_SET_A`:
- `0x00` Success
- `0x01` At least one thruster is not booted (requires all booted)

#### THS_BT (0x22)
Boots individual thrusters by setting their PWM pulse widths to 1500µs. 
Thruster should do its boot up beeps.

Command Packet(10 Bytes)
| Byte Index | 0    | 1                    | 2–9 |
|-----------:|------|----------------------|-----|
| Data       | 0x22 | Thruster Index (0–5) | Unused (0x00 recommended) |

Response Packet (2 Bytes)
| Byte Index | 0           | 1           |
|-----------:|-------------|-------------|
| Data       | 0x21 (Echo) | Return Code |

Return Codes for `THS_BT`:
- `0x00` Success
- `0x02` If the thruster index is invalid

#### THS_BT_A (0x23)
Boots all thrusters by setting all PWM outputs to **1500 µs (neutral)** and setting `ths_boot = 0x3F`.

Command Packet (10 Bytes)
| Byte Index | 0    | 1–9 |
|-----------:|------|-----|
| Data       | 0x23 | Unused (0x00 recommended) |

Response Packet (2 Bytes)
| Byte Index | 0           | 1           |
|-----------:|-------------|-------------|
| Data       | 0x23 (Echo) | Return Code |

Return Codes for `THS_BT_A`:
- `0x00` Success

#### THS_UNBT (0x24)
Unboots an individual thruster by setting its PWM pulse width to **0 µs (disabled)** and clearing its boot bit.

Command Packet (10 Bytes)
| Byte Index | 0    | 1                    | 2–9 |
|-----------:|------|----------------------|-----|
| Data       | 0x24 | Thruster Index (0–5) | Unused (0x00 recommended) |

Response Packet (2 Bytes)
| Byte Index | 0           | 1           |
|-----------:|-------------|-------------|
| Data       | 0x24 (Echo) | Return Code |

Return Codes for `THS_UNBT`:
- `0x00` Success
- `0x02` Invalid thruster index

#### THS_UNBT_A (0x25)
Unboots all thrusters by setting all PWM outputs to **0 µs (disabled)** and setting `ths_boot = 0x00`.

Command Packet (10 Bytes)
| Byte Index | 0    | 1–9 |
|-----------:|------|-----|
| Data       | 0x25 | Unused (0x00 recommended) |

Response Packet (2 Bytes)
| Byte Index | 0           | 1           |
|-----------:|-------------|-------------|
| Data       | 0x25 (Echo) | Return Code |

Return Codes for `THS_UNBT_A`:
- `0x00` Success

##  ---------------------------SEV (Servo) Commands---------------------------

### Angle --> Pulse Width Mapping

Servo commands use an angle in degrees (0–270).  
Angles are transmitted as **16-bit unsigned integers (uint16_t)** in command packets.

**pulse_us = 500 + (uint32_t)(angle * 2000 / 270)**

This converts servo angle (0–270 deg) to pulse width (500–2500 us).
Total range is 2000 us over 270 degrees.


| Angle (deg) | Approx. Pulse (µs)  | Meaning                   |
|------------:|--------------------:|--------------------------|
| 0           | 500                 | Minimum                  |
| 135         | ~1500               | Neutral (approximate)    |
| 270         | ~2500               | Maximum                  |

### Return Codes

| Value | Meaning                       |
| ----- | ----------------------------- |
| 0x00  | Success                       |
| 0x01  | Not booted                    |
| 0x02  | Invalid index                 |
| 0x03  | Invalid angle                 |

### Boot Requirement

SEV_SetAngleAll() returns Not booted if sev_boot == 0.
SEV_SetAngle() returns Not booted if the requested channel is not booted (as determined by sev_boot).

### Servo Index / Channel

**Important:** Ensure the protocol’s “servo index” matches the PWM channel numbering used by TIM4 (CCR1–CCR4).  

#### SEV_SET (0x30)
Sets a single servo angle (degrees).

Command Packet (10 Bytes)
| Byte Index | 0    | 1                 | 2                      | 3–9                       |
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
| Byte Index | 0    | 1                      | 2      | 3                      | 4      | 5                      | 6      | 7                      | 8–9    |
| ---------: | ---- | ---------------------- | ------ | ---------------------- | ------ | ---------------------- | ------ | ---------------------- | ------ |
|       Data | 0x31 | Servo 0 Angle (uint8)* | Unused | Servo 1 Angle (uint8)* | Unused | Servo 2 Angle (uint8)* | Unused | Servo 3 Angle (uint8)* | Unused |

Response (2 Bytes)
| Byte Index | 0           | 1           |
|-----------:|-------------|-------------|
| Data       | 0x31 (Echo) | Return Code |

Servo angles are transmitted as 16-bit unsigned integers (uint16_t).  
Valid range per servo: 0–270 degrees.

#### SEV_BT (0x32)
Boots one servo channel. 
Booting sets the servo output to **1500 µs (neutral position)**.
Does not set the global boot flag (sev_boot)

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
Booting sets all servo outputs to **1500 µs (neutral position)** 
Sets the global boot flag.

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
does not clears the global boot flag.

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
Unbooting sets all servo outputs to **0 µs (output disabled)** 
Clears the global boot flag.

Command Packet (10 Bytes)

| Byte Index | 0    | 1–9                       |
|-----------:|------|---------------------------|
| Data       | 0x35 | Unused (0x00 recommended) |

Response (2 Bytes)

| Byte Index | 0           | 1           |
|-----------:|-------------|-------------|
| Data       | 0x35 (Echo) | Return Code |

## ---------------------------BOP (Breakout Output Pin) Commands---------------------------

| Port  | Pins               |
| ----- | ------------------ |
| GPIOB | PB6, PB7           |
| GPIOE | PE2, PE4, PE5, PE6 |
| GPIOF | PF0, PF1           |

##### BOP_HIGH (0x40)

Clears MODER for all affected pins, then sets them to output mode.
Sets each pin’s ODR bit to 1.

Command Packet
| Byte Index | 0    | 1–9    |
| ---------- | ---- | ------ |
| Data       | 0x40 | Unused |

Respnse
| Byte Index | 0           | 1    |
| ---------- | ----------- | ---- |
| Data       | 0x40 (Echo) | 0x00 |

#### BOP_LOW (0x41)

Clears MODER for all affected pins, then sets them to output mode.
Sets each pin’s ODR bit to 0.

Command Packet
| Byte Index | 0    | 1–9    |
| ---------- | ---- | ------ |
| Data       | 0x41 | Unused |

Response Packet
| Byte Index | 0           | 1    |
| ---------- | ----------- | ---- |
| Data       | 0x41 (Echo) | 0x00 |


##### BOP_COM (0x42) 

Configures the listed pins as Alternate Function (not GPIO) and sets their AF mux values,
The pins become comms-related signals instead of breakout outputs.
    Note: This command does not configure OTYPER, OSPEEDR, or PUPDR; those settings remain unchanged.

Sets MODER to alternate function for each affected pin.
Clears the relevant AFR[] nibble fields.

Writes AF selections to respective comms setting:

- PB6, PB7 --> AF7
- PE2, PE4, PE5, PE6 --> AF5
- PF0, PF1 --> AF4

AF fields are 4 bits per pin (‘nibbles’) in AFR; mode fields are 2 bits per pin in MODER.

Command Packet (10 Bytes)
| Byte Index | 0    | 1–9    |
| ---------- | ---- | ------ |
| Data       | 0x42 | Unused |

Response Packet (2 Bytes)
| Byte Index | 0           | 1    |
| ---------- | ----------- | ---- |
| Data       | 0x42 (Echo) | 0x00 |
