# Command packet structure
 All commands are 10 bytes formatted like below. Not all commands require all 9 argument bytes.

| Byte Index | 0            | 1-9       |
| ---------- | ------------ | --------- |
| Data       | Command Byte | Arguments |
All commands return 2 byte

| Byte Index |                   |              |
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
| Data       | 0x21 | Thruster 1 Speed | Thruster 2 Speed | Thruster 3 Speed | Thruster 4 Speed | Thruster 5 Speed | Thruster 6 Speed |

| Return Byte |                                     |
| ----------- | ----------------------------------- |
| 0x00        | Success                             |
| 0x01        | At least one thruster is not booted |
#### THS_BT (0x22)
Boots individual thrusters.
Returns 0x00.

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
Unboots individual thrusters.
Returns 0x00.

| Byte Index | 0    | 1              |
| ---------- | ---- | -------------- |
| Data       | 0x22 | Thruster Index |
#### THS_UNBT_A (0x25)
Unboots all thrusters.
Returns 0x00.

| Byte Index | 0    |
| ---------- | ---- |
| Data       | 0x23 |
