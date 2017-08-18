#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../error/error.h"

#define GPR_REGISTERS 13  /* The number of General Purpose Registers */
#define MEMORY_SIZE 65536 /* 64KB = 64 * 2^10 bytes */ //64 * (2 << 10)
#define KILO_POWER 10     /* 2^10 is the number of bytes in a KB */

typedef uint32_t reg32; /* 32-bit registers */
typedef bool flag;      /* Boolean flags */

/* CPSR flags struct */
typedef struct {
	flag N; /* Negative flag */
	flag Z; /* Zero flag */
	flag C; /* Carry flag */
	flag V; /* Overflow flag */
} CPSR;

/* ARM1176JZF-S processor struct */
typedef struct {
	reg32 gpr[GPR_REGISTERS];  /* Registers 0 to 11 are gpr (General Purpose Registers) */
	reg32 pc;                  /* Register 15 - The program counter */
	CPSR *cpsr;                /* Register 16 - CPRS register */
	uint8_t *memory;           /* Pointer to 64KB of memory */
} ARM11;

/* Initialises the ARM11 processor; allocating 64KB of memory and clearing all registers */
ARM11* initialiseProcessor();

/* Frees the memory allocated by an ARM11 processor */
void freeProcessor(ARM11 *arm11);

#endif
