/*
 *
 * Purpose: The ARM11 processor
 *
 */

#include "processor.h"

/* Initialises the ARM11 processor  */
ARM11* initialiseProcessor() {

	/* Allocate memory for the processor */
	ARM11 *arm11 = calloc(sizeof(ARM11), 1);
	checkAlloc(arm11, "Failed to allocate memory for arm11 processor ",
	    MEMORY_ALLOCATE_FAILURE);

	/* Allocate 64KB of memory and clear */
	arm11->memory = calloc(MEMORY_SIZE, sizeof(uint32_t));
	checkAlloc(arm11->memory, "Failed to allocate memory for arm11 64KB memory ",
	    MEMORY_ALLOCATE_FAILURE);

	/* Allocate memory for the CPSR register */
	arm11->cpsr = calloc(sizeof(CPSR), 1);
	checkAlloc(arm11->cpsr, "Failed to allocate memory for arm11 CPSR register ",
	    MEMORY_ALLOCATE_FAILURE);

	return arm11;
}

/* Frees the memory allocated by an ARM11 processor */
void freeProcessor(ARM11 *arm11) {

	/* Free the CPSR register first otherwise we will have a memory leak */
	free(arm11->cpsr);

	/* Now the 64KB of memory */
	free(arm11->memory);

	/* Finally the processor */
	free(arm11);

}
