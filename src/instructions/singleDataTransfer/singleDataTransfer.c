/*
 *
 * Purpose: Single data transfer instructions
 *
 */

#include "singleDataTransfer.h"

#define PC 15 /* Program counter is register 15 */

/* Loads data from a memory address to a register */
void ldr(instruction *instr, ARM11 *arm11, bool isPreIndex) {
	uint32_t memoryAddress;
	if (instr->U == 1) {
		if (instr->rn == PC) {
			memoryAddress = (isPreIndex ? arm11->pc + instr->offset : arm11->pc);
		} else {
			memoryAddress = (
					isPreIndex ?
							arm11->gpr[instr->rn] + instr->offset : arm11->gpr[instr->rn]);
		}
	} else {
		if (instr->rn == PC) {
			memoryAddress = (isPreIndex ? arm11->pc - instr->offset : arm11->pc);
		} else {
			memoryAddress = (
					isPreIndex ?
							arm11->gpr[instr->rn] - instr->offset : arm11->gpr[instr->rn]);
		}
	}

	/* Trying to read from memory addresses outside of 64KB */
	if (memoryAddress < MEMORY_SIZE) {
		// Read 4-bytes from memory + memoryAddress
		arm11->gpr[instr->rd] = readWord(arm11->memory + memoryAddress);
	} else {
		/* Check for trigger a GPIO pin */
		if (!checkGPIOAccess(memoryAddress)) {
			printf("Error: Out of bounds memory access at address 0x%08x\n",
					memoryAddress);
		} else {
			checkGPIOPin(memoryAddress);
		}
	}

	if (!isPreIndex) {
		if (instr->rn == PC) {
			arm11->pc =
					(instr->U == 1 ? arm11->pc + instr->offset : arm11->pc - instr->offset);
		} else {
			arm11->gpr[instr->rn] = (
					instr->U == 1 ?
							arm11->gpr[instr->rn] + instr->offset :
							arm11->gpr[instr->rn] - instr->offset);
		}
	}
}

/* Stores data from a register to another register */
void str(instruction *instr, ARM11 *arm11, bool isPreIndex) {
	uint32_t memoryAddress;
	if (instr->U == 1) {
		memoryAddress = (
				isPreIndex ?
						arm11->gpr[instr->rn] + instr->offset : arm11->gpr[instr->rn]);
	} else {
		memoryAddress = (
				isPreIndex ?
						arm11->gpr[instr->rn] - instr->offset : arm11->gpr[instr->rn]);
	}
	/* Check for writes to GPIO pins/illegal memory access */

	if (memoryAddress > MEMORY_SIZE) {
		if (!checkGPIOAccess(memoryAddress)) {
			printf("Error: Out of bounds memory access at address 0x%08x\n",
					memoryAddress);
		} else {
			checkGPIOPin(memoryAddress);
		}

	} else {
		/* Write 4 bytes to memory */
		writeWord(arm11->memory + memoryAddress, arm11->gpr[instr->rd]);
		if (!isPreIndex) {
			arm11->gpr[instr->rn] = (
					instr->U == 1 ?
							arm11->gpr[instr->rn] + instr->offset :
							arm11->gpr[instr->rn] - instr->offset);
		}

	}
}

/* Single data transfer instruction */
void singleDataTransfer(instruction *instr, ARM11 *arm1111) {
	if (instr->I == 1) {
		instr->offset = shifterReg(instr->offset, arm1111, false);
	}
	if (instr->L == 1) {
		ldr(instr, arm1111, instr->P == 1);
	} else {
		str(instr, arm1111, instr->P == 1);
	}
}
