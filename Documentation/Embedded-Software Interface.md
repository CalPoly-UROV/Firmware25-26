## Command packet structure
 All commands are 10 bytes formatted like so: 

| Byte Index | 0            | 1-9       |
| ---------- | ------------ | --------- |
| Data       | Command Byte | Arguments |
All commands return 1 byte: the command byte

## Commands
#### MOT_SET
Set an individual motor to a value. 

| Byte index | 0          | 1           | 2     | 3    | 4    | 5    | 6    | 7    | 8    | 9    |
| ---------- | ---------- | ----------- | ----- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| Data       | 0x4D ('M') | Motor Index | Value | NULL | NULL | NULL | NULL | NULL | NULL | NULL |

#### MOT_ALL_SET
Set all motors to new values. 

| Byte index | 0          | 1             | 2             | 3             | 4             | 5             | 6             | 7             | 8    | 9    |
| ---------- | ---------- | ------------- | ------------- | ------------- | ------------- | ------------- | ------------- | ------------- | ---- | ---- |
| Data       | 0x57 ('W') | motor 0 value | motor 1 value | motor 2 value | motor 3 value | motor 4 value | motor 5 value | motor 6 value | NULL | NULL |


#### LED_BLNK
Blink the orange LED on the STM devboard. Purely for debug purposes. 

| Byte index | 0          | 1            | 2           | 3    | 4    | 5    | 6    | 7    | 8    | 9    |
| ---------- | ---------- | ------------ | ----------- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| Data       | 0x42 ('B') | Emmpty Value | Empty Value | NULL | NULL | NULL | NULL | NULL | NULL | NULL |
