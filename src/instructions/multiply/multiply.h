#ifndef MULTIPLY_H
#define MULTIPLY_H

#include "../instruction/instruction.h"

/* Multiply. */
void multiply(instruction *instr, ARM11 *arm11);

/* Multiply without accumulate. */
void multiplyWithoutAccumulate(instruction *instr, ARM11 *arm11);

/* Multiply with accumulate. */
void multiplyWithAccumulate(instruction *instr, ARM11 *arm11);

#endif
