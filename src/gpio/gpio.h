/*
 * gpio.h
 *
 *  Created on: 13 Jun 2015
 *      Author: am5514
 */

#ifndef GPIO_H_
#define GPIO_H_


/* Physical addresses of the pin accesses in memory */
#define GPIO_PINS_20_29 0x20200008
#define GPIO_PINS_10_19 0x20200004
#define GPIO_PINS_0_9 0x20200000

/* Addreses of the control and setting pins */
#define GPIO_CONTROL_CLEAR 0x20200028 /* Clears a pin */
#define GPIO_CONTROL_SET 0x2020001C /* Sets a pin (turns it on) */

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

/* Checks for GPIO memory accesses, returns true on access */
bool checkGPIOAccess(uint32_t memoryAddress);

/* Prints which GPIO pin was triggered */
void checkGPIOPin(uint32_t memoryAddress);

#endif /* GPIO_H_ */
