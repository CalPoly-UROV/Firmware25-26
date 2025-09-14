/*
 * commands.h
 *
 *  Created on: Nov 9, 2024
 *      Author: root
 */

#ifndef COMMANDS_H_
#define COMMANDS_H_
	/*
	 * 0x00 none
	 * 0x42 (B)link			(1 byte)
	 * 0x4D (M)anipulator	(3 bytes)
	 * 0x53	(S)ensor read	(upto 2 + number of sensors bytes)
	 * 0x54 (T)hrusters set (9 bytes)
	 */
#define CMD_NONE 	(0x00)
#define CMD_BLINK 	(0x42)
#define CMD_MANIP	(0x4D)
#define CMD_SENSR	(0x53)
#define CMD_THRSET	(0x54)

#define CMD_SIZE_NONE	(0x01)
#define CMD_SIZE_3BYTE	(0x03)
#define CMD_SIZE_9BYTE	(0x09)


#endif /* COMMANDS_H_ */
