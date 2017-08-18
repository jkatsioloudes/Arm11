/*
 * initialise.h
 *
 *  Created on: 3 Jun 2015
 *      Author: am5514
 */

#ifndef INITIALISE_H_
#define INITIALISE_H_

#include "../conditions/conditions.h"
#include "../assembleInstruction/opcode/opcode.h"
#include "../assembler/assemble.h"
#include "../instructions/dataProcessing/dataProcessing.h"

void addDataProcessingOpcode(linkedList *list, char *mnemonic, uint8_t opcode, bool S, uint8_t cond);

void initialise(linkedList *list);

void addMultiply(linkedList *list, char *mnemonic, bool A, bool S);

void addSingleDataTransferOpcode(linkedList *list, char *mnemonic, bool L);

#endif /* INITIALISE_H_ */
