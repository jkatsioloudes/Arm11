/*
 * assembleSpecialInstruction.h
 *
 *  Created on: 12 Jun 2015
 *      Author: nv214
 */

#ifndef ASSEMBLESPECIALINSTRUCTION_H_
#define ASSEMBLESPECIALINSTRUCTION_H_

#include "../../list/singlyLinkedList/singlyLinkedList.h"
#include "../../tokenizer/tokenizer.h"
#include "../opcode/opcode.h"

uint32_t assembleSpecialInstruction(char **tokens, linkedList *list);



#endif /* ASSEMBLESPECIALINSTRUCTION_H_ */
