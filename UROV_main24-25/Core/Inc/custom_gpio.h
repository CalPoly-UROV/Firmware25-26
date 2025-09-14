/*
 * initpin.h
 *
 *  Created on: Apr 19, 2024
 *      Author: liamduckworth
 */

#ifndef SRC_GPIO_H_
#define SRC_GPIO_H_
#include "stm32f4xx_hal.h"
/* */
#ifndef MSK4B
#define MSK4B		(0xF)
#endif

#ifndef MSK2B
#define MSK2B		(0x3)
#endif

#ifndef MSK1B
#define MSK1B		(0x1)
#endif


#define MINPUT		(0x0)
#define MOUTPUT		(0x1)
#define MAF			(0x2)
#define MANALOG		(0x3)

#define OTPUSHPULL	(0x0)
#define OTOPENDRAIN (0x1)

#define OSLOW		(0x0)
#define OSMIDLOW	(0x1)
#define OSMIDHIGH	(0x2)
#define OSHIGH		(0x3)

#define PUPDNONE	(0x0)
#define PUPDUP		(0x1)
#define PUPDDOWN	(0x2)

/*for use in a function already decerning high and low AFSEL registers*/
typedef enum AFSEL{ AF0, AF1, AF2, AF3, AF4, AF5, AF6, AF7, AF8,
			AF9, AF10, AF11, AF13, AF14, AF15, AF16
} AFSEL_t;

//configure a pin as an output
void initGPO(GPIO_TypeDef *port, uint32_t pin, uint32_t type,
					uint32_t speed, uint32_t pupd);

//configure a pin as an input
void initGPI(GPIO_TypeDef *port, uint32_t pin,
				uint32_t speed, uint32_t pupd);

//configure a pin generically
void initpin(GPIO_TypeDef *port, uint32_t pin, uint32_t mode, uint32_t type,
				uint32_t speed, uint32_t pupd, AFSEL_t afsel);

//configure multiple pins on a port in the same way
void mpininit(GPIO_TypeDef *port, uint32_t *pins, uint32_t pincount,
				uint32_t mode, uint32_t type, uint32_t speed, uint32_t pupd,
				AFSEL_t afsel);

void setpin(GPIO_TypeDef *port, uint32_t pin);

void resetpin(GPIO_TypeDef *port, uint32_t pin);



#endif /* SRC_GPIO_H_ */
