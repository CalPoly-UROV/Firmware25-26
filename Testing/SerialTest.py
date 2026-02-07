import struct
import serial
import time
import keyboard

#Name of serial port
port = "COM4"
ser = serial.Serial(port, 115200, timeout = 1);

def send_command(com):
    ser.write(com)
    ser.flush()
    ret = ser.read(2)
    return ret

while True:
    line = input("Enter hex bytes: ")

    # Parse hex values
    values = [int(x, 16) for x in line.split()]

    if len(values) > 10:
        raise ValueError("Too many values (max 10)")

    # Pad with zeros
    values.extend([0x00] * (10 - len(values)))

    data = bytes(values)
    response = send_command(data)
    print(response.hex(" "))
