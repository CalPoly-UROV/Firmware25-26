## Command packet structure
 All commands are 10 bytes formatted like so: Empty values are not considered.

A 3-byte command is formatted like this:
| Byte index | 0           | 1             | 2             | 3             | 4             | 5             | 6             | 7             | 8             | 9 |
| ---------- | ----------- | ------------- | ------------- | ------------- | ------------- | ------------- | ------------- | ------------- | ------------- | ---------- |
| Data       | Command ID | Value 1 | Value 2 | Empty Value | Empty Value | Empty Value | Empty Value | Empty Value | Empty Value | Empty Value |


There is a special motor command which is formatted like so:

| Byte index | 0           | 1             | 2             | 3             | 4             | 5             | 6             | 7             | 8             | 9 |
| ---------- | ----------- | ------------- | ------------- | ------------- | ------------- | ------------- | ------------- | ------------- | ------------- | ---------- |
| Data       | MOT_ALL_SET | motor 0 value | motor 1 value | motor 2 value | motor 3 value | motor 4 value | motor 5 value | motor 6 value | Empty Value | Empty Value |
## Commands
As a note, command macros should ideally be formatted as DEVICE_ACTION for clarity and consistency.
#### MOT_SET
Set an individual motor to a value. Returns the message "mot_set" upon success.

| Byte index | 0          | 1           | 2     |
| ---------- | ---------- | ----------- | ----- |
| Data       | 0x4D ('M') | Motor Index | Value |

#### MOT_ALL_SET
Set all motors to new values. Returns an the message "mot_all_set" upon success.

| Byte index | 0          | 1             | 2             | 3             | 4             | 5             | 6             | 7             |
| ---------- | ---------- | ------------- | ------------- | ------------- | ------------- | ------------- | ------------- | ------------- |
| Data       | 0x57 ('W') | motor 0 value | motor 1 value | motor 2 value | motor 3 value | motor 4 value | motor 5 value | motor 6 value |


#### LED_BLNK
Blink the orange LED on the STM devboard. Purely for debug purposes. Returns an echo packet and the message "led_blnk".

| Byte index | 0          | 1            | 2   |
| ---------- | ---------- | ------------ | --- |
| Data       | 0x42 ('B') | Emmpty Value | Empty Value |
