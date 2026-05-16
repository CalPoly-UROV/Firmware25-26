import struct
import serial
from time import sleep
import keyboard

#Name of serial port
port = "COM7"
ser = serial.Serial(port, 115200, timeout = 1);

def send_command(com):
    ser.write(com)
    ser.flush()
    ret = ser.read(3)
    return ret

while True:
    sleep(0.01)
    ser.flush()
    line = input("Enter hex bytes: ")
    #line = "a0"

    # Parse hex values
    values = [int(x, 16) for x in line.split()]

    if len(values) > 10:
        raise ValueError("Too many values (max 10)")

    # Pad with zeros
    values.extend([0x00] * (10 - len(values)))

    data = bytes(values)
    response = send_command(data)
    if(len(response) != 0):
        length = response[2]
        if(response[0] != data[0]):
            print(response.hex(" ") + " | bad response")
        elif(length == bytes([0])):
            print(response.hex(" "))
        else:
            ser.flush()
            response2 = ser.read(length)
        
            s = 0
            for i in range(length - 1):
                s += response2[i]
            print(response.hex(" ") + " | " + response2.hex(" ") + " | " + f"{bytes([s % 256]).hex(" ")}")