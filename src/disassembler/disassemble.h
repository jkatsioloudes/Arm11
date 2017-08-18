/*
 * disassemble.h
 *
 *  Created on: 14 Jun 2015
 *      Author: am5514
 */

#ifndef DISASSEMBLE_H_
#define DISASSEMBLE_H_

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../error/error.h"
#include "../processor/processor.h"
#include "../tokenizer/tokenizer.h"
#include "../bitManipulation/bitManipulation.h"

#define DISASSEMBLE_EXPECTED_ARGUMENTS 2

/* Disassembles src and writes the output to dst*/
bool disassembleFile(char *src, char *dst);

/* Disassembles a single instruction */
char *disassembleInstruction(uint32_t instructionWord);

/* Loads the binary file into memory */
void loadFile(const char *fileName, uint32_t *memory);

/* Decodes a 32-bit instruction */
instruction* decode(uint32_t instruction);

#endif /* DISASSEMBLE_H_ */
