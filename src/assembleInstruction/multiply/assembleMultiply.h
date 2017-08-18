/*
 * assembleMultiply.h
 *
 *  Created on: 3 Jun 2015
 *      Author: am5514
 */

#ifndef ASSEMBLEMULTIPLY_H_
#define ASSEMBLEMULTIPLY_H_

#include <string.h>
#include <stdint.h>
#include "../../list/singlyLinkedList/singlyLinkedList.h"
#include "../../bitManipulation/bitManipulation.h"
#include "..//opcode/opcode.h"

uint32_t assembleMultiply(char **tokens, linkedList *list);

uint32_t assembleMul(uint32_t instructionWord, char **tokens);

uint32_t assembleMla(uint32_t instructionWord, char **tokens);

#endif /* ASSEMBLEMULTIPLY_H_ */
