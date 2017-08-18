/*
 * gpio.c
 *
 *  Created on: 13 Jun 2015
 *      Author: am5514
 */

#include "gpio.h"

/* Checks for GPIO memory accesses*/
bool checkGPIOAccess(uint32_t memoryAddress) {
	switch (memoryAddress) {
	case GPIO_PINS_20_29:
		printf("One GPIO pin from 20 to 29 has been accessed\n");
		break;
	case GPIO_PINS_10_19:
		printf("One GPIO pin from 10 to 19 has been accessed\n");
		break;
	case GPIO_PINS_0_9:
		printf("One GPIO pin from 0 to 9 has been accessed\n");
		break;
	case GPIO_CONTROL_CLEAR:
		printf("PIN OFF\n");
		break;
	case GPIO_CONTROL_SET:
		printf("PIN ON\n");
		break;
	default:
		return false;
		break;
	}
	return true;
}

/* Prints which GPIO pin was triggered */
void checkGPIOPin(uint32_t memoryAddress) {

	/* The mask for checking which pin was accessed */
	/* 001 sets a pin */
	/* bits 0-29 are used */
	uint32_t PIN_MASK = 0x00000001;
	uint32_t ITERATIONS = 10;
	uint32_t pin = 0;
	for (int i=0; i<ITERATIONS; i++) {
		if ((memoryAddress & PIN_MASK) == 1) {
			switch (memoryAddress) {
			case GPIO_PINS_0_9:
				pin = (i > 0 ? i - 1 : i);
				break;
			case GPIO_PINS_10_19:
				pin = 10 + i;
				break;
			case GPIO_PINS_20_29:
				pin = 20 + i;
				break;
			default:
				printf("Unknown memory address 0x%08X\n",memoryAddress);
				return;
			}
			printf("Pin %d has been accessed\n",pin);
		}
		PIN_MASK <<= 3;
	}

}
