/*
 * assembleDataProcessing.h
 *
 *  Created on: 1 Jun 2015
 *      Author: am5514
 */

#ifndef ASSEMBLEDATAPROCESSING_H
#define ASSEMBLEDATAPROCESSING_H

#include <stdint.h>
#include "../opcode/opcode.h"
#include "../../list/singlyLinkedList/singlyLinkedList.h"
#include "../../bitManipulation/bitManipulation.h"
#include "../../instructions/dataProcessing/dataProcessing.h"
#include "../../shifter/shifter.h"

uint32_t assembleDataProcessing(char **tokens, linkedList *list);

uint32_t assembleMov(uint32_t instructionWord, char **tokens);

uint32_t assembleComparison(uint32_t instructionWord, char **tokens);

uint32_t assembleCalculate(uint32_t instructionWord, char **tokens);

#endif
