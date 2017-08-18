#ifndef BRANCH_H
#define BRANCH_H

#include "../../processor/processor.h"
#include "../instruction/instruction.h"
#include "../../shifter/shifter.h"

/* Performs a branch instruction */
void branch(instruction *instr, ARM11 *arm11);

#endif
