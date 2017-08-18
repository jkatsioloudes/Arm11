/*
 * twoPass.h
 *
 *  Created on: 4 Jun 2015
 *      Author: am5514
 */

#ifndef TWOPASS_H_
#define TWOPASS_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "../tokenizer/tokenizer.h"
#include "../list/doublyLinkedList/doublyLinkedList.h"

listEntries *createNewSymbolTable(char *fileName, asmInstruction **instr);

#endif /* TWOPASS_H_ */
