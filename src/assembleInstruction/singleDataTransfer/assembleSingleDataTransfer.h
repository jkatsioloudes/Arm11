/*
 * assembleSingleDataTransfer.h
 *
 *  Created on: 3 Jun 2015
 *      Author: am5514
 */

#ifndef ASSEMBLESINGLEDATATRANSFER_H_
#define ASSEMBLESINGLEDATATRANSFER_H_

#include <string.h>
#include <stdint.h>
#include "../../bitManipulation/bitManipulation.h"
#include "../../list/singlyLinkedList/singlyLinkedList.h"
#include "../dataProcessing/assembleDataProcessing.h"
#include "../opcode/opcode.h"
#include "../../tokenizer/tokenizer.h"


uint32_t assembleSTR(uint32_t instructionWord, char **tokens, uint32_t currentAddress);

#endif /* ASSEMBLESINGLEDATATRANSFER_H_ */
