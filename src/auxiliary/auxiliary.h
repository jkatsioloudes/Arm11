#ifndef AUXILIARY_H
#define AUXILIARY_H

#include <stdio.h>
#include "../loader/loader.h"
#include "../bitManipulation/bitManipulation.h"

/* Prints the contents of all registers */
void printRegisters(ARM11 *arm11);

/* Prints the contents of all non-zero memory locations */
void printMemory(ARM11 *arm11);

#endif
