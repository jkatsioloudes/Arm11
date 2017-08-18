/*
 **
 ** Purpose: This file contains auxiliary functions that are required.
 **
 */

#include "auxiliary.h"

/* Prints the contents of all registers */
void printRegisters(ARM11 *arm11) {
	printf("Registers:\n");

	/* General Purpose Registers */
	for (int i = 0; i < GPR_REGISTERS; i++) {
		printf("$%-3d: %10d (0x%08x)\n", i, arm11->gpr[i], arm11->gpr[i]);
	}

	/* Program Counter */
	printf("PC  :  %9d (0x%08x)\n", arm11->pc, arm11->pc);

	/* Display the CPSR register as a combination of shifted flags */
	int32_t cpsr = (int32_t) (arm11->cpsr->N << N_BIT)
			| (int32_t) (arm11->cpsr->Z << Z_BIT)
			| (int32_t) (arm11->cpsr->C << C_BIT)
			| (int32_t) (arm11->cpsr->V << V_BIT);

	printf("CPSR: %10d (0x%08x)\n", cpsr, cpsr);
}

/* Prints the contents of all non-zero memory locations */
void printMemory(ARM11 *arm11) {
	printf("Non-zero memory:\n");
	for (int i = 0; i < MEMORY_SIZE; i += sizeof(uint32_t)) {
		if (readWord(arm11->memory + i) != 0) {
			printf("0x%08x: 0x%08x\n", (uint32_t) (i * sizeof(uint8_t)),
					changeEndianness(readWord(arm11->memory + i)));
		}
	}
}
