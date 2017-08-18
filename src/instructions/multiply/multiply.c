/*
 *
 * Purpose: The multiply instruction implementation
 *
 */

#include "multiply.h"

/* Multiply. */
void multiply(instruction *instr, ARM11 *arm11) {
	if (instr->A == 0) {
		multiplyWithoutAccumulate(instr, arm11);
	} else {
		multiplyWithAccumulate(instr, arm11);
	}
}

/* Multiply without accumulate. */
void multiplyWithoutAccumulate(instruction *instr, ARM11 *arm11) {
	uint32_t result = arm11->gpr[instr->rm] * arm11->gpr[instr->rs];
	arm11->gpr[instr->rd] = result;
	if (instr->S == 1) {
		arm11->cpsr->N = getBits(result, N_BIT, N_BIT);
		if (result == 0) {
			arm11->cpsr->Z = 1;
		}
	}
}

/* Multiply with accumulate. */
void multiplyWithAccumulate(instruction *instr, ARM11 *arm11) {
	uint32_t result = (arm11->gpr[instr->rm] * arm11->gpr[instr->rs])
			+ arm11->gpr[instr->rn];
	arm11->gpr[instr->rd] = result;
	if (instr->S == 1) {
		arm11->cpsr->N = getBits(result, N_BIT, N_BIT);
		if (result == 0) {
			arm11->cpsr->Z = 1;
		}
	}
}
