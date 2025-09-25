## Command packet structure
 All commands are 3 bytes formatted like so:

| Byte index | 0          | 1       | 2       |
| ---------- | ---------- | ------- | ------- |
| Data       | Command ID | Value 1 | Value 2 |
There is a special motor command which is formatted like so:

| Byte index | 0           | 1             | 2             | 3             | 4             | 5             | 6             | 7             | 8             |
| ---------- | ----------- | ------------- | ------------- | ------------- | ------------- | ------------- | ------------- | ------------- | ------------- |
| Data       | MOT_ALL_SET | motor 0 value | motor 1 value | motor 2 value | motor 3 value | motor 4 value | motor 5 value | motor 6 value | motor 7 value |
## Commands
As a note, command macros should ideally be formatted as DEVICE_ACTION for clarity and consistency.
#### MOT_SET
Set an individual motor to a value. Returns an echo packet upon success, on failure the 0 byte will be set to 0.

| Byte index | 0          | 1           | 2     |
| ---------- | ---------- | ----------- | ----- |
| Data       | 0x4D ('M') | Motor Index | Value |

#### MOT_ALL_SET
Set all motors to new values. Returns an echo packet upon success, on failure the 0 byte will be set to the index where it failed first.

| Byte index | 0          | 1             | 2             | 3             | 4             | 5             | 6             | 7             | 8             |
| ---------- | ---------- | ------------- | ------------- | ------------- | ------------- | ------------- | ------------- | ------------- | ------------- |
| Data       | 0x57 ('W') | motor 0 value | motor 1 value | motor 2 value | motor 3 value | motor 4 value | motor 5 value | motor 6 value | motor 7 value |

#### SENS_RD
Read a sensor's value. Returns the sensor's data in little endian byte order (least significant byte in index 0). Return data will be padded to 32 bits wide (if none of the sensors return more than 16 bits, we'll just zero pad to 24 bits so that its the same size as an echo packet, but I cant remember and I'm too lazy to check rn)

| Byte index | 0          | 1            | 2   |
| ---------- | ---------- | ------------ | --- |
| Data       | 0x53 ('S') | Sensor Index | N/A |

Sensor Index Table

| Index | Sensor               | Data width (bytes) |
| ----- | -------------------- | ------------------ |
| 0     | IMU                  | ?                  |
| 1     | External Temperature | ?                  |
| 2     | Internal Temperature | ?                  |
| 3     | Internal Pressure    | ?                  |
| 4     | Internal Humidity    | ?                  |
#### LED_BLNK
Blink the orange LED on the STM devboard. Purely for debug purposes. Returns an echo packet.

| Byte index | 0          | 1            | 2   |
| ---------- | ---------- | ------------ | --- |
| Data       | 0x42 ('B') | N/A | N/A |
