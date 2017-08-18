#ifndef SINGLE_DATA_TRANSFER_H
#define SINGLE_DATA_TRANSFER_H

#include <stdio.h>
#include <stdbool.h>
#include "../instruction/instruction.h"
#include "../../loader/loader.h"
#include "../../gpio/gpio.h"

/* Single Data Transfer signatures */

void ldr(instruction *instr, ARM11 *arm11, bool isPreIndex);

void str(instruction *instr, ARM11 *arm11, bool isPreIndex);

void singleDataTransfer(instruction *instr, ARM11 *arm11);

#endif
