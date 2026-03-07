import struct
import serial
from time import sleep
import keyboard

#Name of serial port
port = "COM7"
ser = serial.Serial(port, 115200, timeout = 5);

def send_command(com):
    ser.write(com)
    ser.flush()
    ret = ser.read(3)
    return ret
    
def parse_bytes(data: bytes, byteorder='little'):
    prefix = '<' if byteorder == 'little' else '>'
    fmt = prefix + '6hB'

    return struct.unpack(fmt, data)

print("Testing at 50 Hz")
run = 1
while True:
    sleep(0.01)
    #line = input("Enter hex bytes: ")
    ser.flush()
    if(run%2 == 0):
        line = "a0"
    else:
        line = "a0"
    run += 1;
    # Parse hex values
    values = [int(x, 16) for x in line.split()]
    values.extend([0x00] * (10 - len(values)))

    data = bytes(values)
    response = send_command(data)
    printout = f"{run:}|{line} : "
    if(len(response) != 0):
        length = response[2]
        if(response[0] != data[0]):
            printout += response.hex(" ") + " | bad response"
        elif(length == bytes([0])):
            printout += response.hex(" ")
        else:
            ser.flush()
            response2 = ser.read(length)
        
            s = 0
            for i in range(length - 1):
                s += response2[i]
            #printout += f"{response.hex(" ")} | {response2.hex(" ")} | {bytes([s % 256]).hex(' ')}"
            printout += f"{response.hex(" ")} | {parse_bytes(response2, byteorder='little')} | {s % 256}"
    else:
        printout += "failed to recieve, reading again"
        ser.flush()

    print(printout)
    