import struct
import serial
from time import sleep
import keyboard

#Name of serial port
port = "COM7"
ser = serial.Serial(port, 115200, timeout = 1);

def send_command(line):
	values = [int(x, 16) for x in line.split()]
	values.extend([0x00] * (10 - len(values)))
	com = bytes(values)

	ser.write(com)
	ser.flush()
	ret = ser.read(3)
	return ret
	
def parse_bytes(data: bytes, byteorder='little'):
	prefix = '<' if byteorder == 'little' else '>'
	fmt = prefix + '6hB'

	return struct.unpack(fmt, data)

print("Testing at 100 Hz")
run = 1
send_command("b2")
sleep(1)
send_command("b3")
sleep(1)

while True:
	sleep(1/100)
	#line = input("Enter hex bytes: ")
	ser.flush()
	if(run%4==0):
		line = "b0"
	elif(run%4==1):
		line = "b1"
	elif(run%4==2):
		line = "10"
	elif(run%4==3):
		line = "21 7 7"
	run += 1;
	
	values = [int(x, 16) for x in line.split()]
	values.extend([0x00] * (10 - len(values)))
	com = bytes(values)
	ser.write(com)
	ser.flush()
	response = ser.read(3)
	
	printout = f"{run:}|{line} : "
	if(len(response) != 0):
		length = response[2]
		if(response[0] != com[0]):
			printout += response.hex(" ") + " | bad response"
			ser.flush()
		elif(length == 0):
			printout += response.hex(" ")
			ser.flush()
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
	