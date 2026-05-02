import struct
import serial
from time import sleep
import keyboard

#Name of serial port
port = "COM3"
ser = serial.Serial(port, 115200, timeout = 1);

def send_command(com):
	ser.write(com)
	ser.flush()
	ret = ser.read(3)
	return ret
	
def send_line(line):
	print(" Sent: " + line)
	values = [int(x, 16) for x in line.split()]

	if len(values) > 10:
		raise ValueError("Too many values (max 10)")

	# Pad with zeros
	values.extend([0x00] * (10 - len(values)))

	data = bytes(values)
	return send_command(data)
	

def print_response(response):
	if(len(response) != 0):
		length = response[2]
		if(length == 0):
			print("Reply: " + response.hex(" "))

states = ["Boot", "Boot", "Boot", "Boot", "Boot", "Boot"]

while True:
	print(f"\n[0]{states[0]} thruster 0\t[1]{states[1]} thruster 1\t[2]{states[2]} thruster 2\n[3]{states[3]} thruster 3\t[4]{states[4]} thruster 4\t[5]{states[5]} thruster 5\n[E] Unboot all and exit\n")
	command = input("Enter command:")
	if(command == "e"):
		for i in range(6):
			print(f"Unbooting thruster {i}")
			print_response(send_line(f"22 {i}"))
		
		print("exit")
		break;
	elif(command == "0" or command == "1" or command == "2" or command == "3" or command == "4" or command == "5"):
		print(f"{states[int(command)]}ing thruster {command}")
		if(states[int(command)] == "Boot"):
			print_response(send_line("22 " + command))
			states[int(command)] = "Unboot"
		else:
			print_response(send_line("24 " + command))
			states[int(command)] = "Boot"
	else:
		print(f"Unknown command '{command}'")
		