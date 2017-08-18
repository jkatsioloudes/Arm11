/*
 * branch.h
 *
 *  Created on: 3 Jun 2015
 *      Author: am5514
 */

#ifndef ASSEMBLE_BRANCH_H
#define ASSEMBLE_BRANCH_H

#define BRANCH_BIT_24 24
#define BRANCH_BIT_27 27

#define COND_BIT_START 28
#define COND_BIT_END 31

#define OFFSET_BIT_START 0
#define OFFSET_BIT_END 23

#include <string.h>
#include <stdint.h>
#include "../../list/singlyLinkedList/singlyLinkedList.h"
#include "../../list/doublyLinkedList/doublyLinkedList.h"
#include "../opcode/opcode.h"
#include "../../conditions/conditions.h"
#include "../../pipeline/pipeline.h"

uint32_t assembleBranch(char **tokens, linkedList *list, listEntries *symbolTable, uint32_t currentAddress);

#endif /* ASSEMBLE_BRANCH_H */
