/*
 * opcode.h
 *
 *  Created on: 1 Jun 2015
 *      Author: am5514
 */

#ifndef OPCODE_H
#define OPCODE_H

#include <stdint.h>
#include "../../list/singlyLinkedList/singlyLinkedList.h"
#include "../dataProcessing/assembleDataProcessing.h"
#include "../singleDataTransfer/assembleSingleDataTransfer.h"
#include "../multiply/assembleMultiply.h"
#include "../branch/assembleBranch.h"
#include "../../list/doublyLinkedList/doublyLinkedList.h"
#include "../specialInstruction/assembleSpecialInstruction.h"

typedef struct {
	char *mnemonic; /* Instruction mnemonic */
	uint8_t opcode; /* Opcode value */
	uint8_t S;      /* S flag */
	uint8_t cond;   /* Condition */
} asmDataProcessing;

typedef struct {
	char *mnemonic; /* Instruction mnemonic */
	uint8_t cond;   /* Condition */
} asmBranch;

typedef struct {
	char *mnemonic; /* Instruction mnemonic */
	uint8_t A;      /* A flag */
	uint8_t S;      /* S flag */
} asmMultiply;

typedef struct {
	char *mnemonic; /* Instruction mnemonic */
	uint8_t U;      /* U flag */
	uint8_t L;      /* L flag */
} asmSingleDataTransfer;


typedef struct {
  uint32_t currentAddress;
  uint32_t lastAddress;
  uint32_t *savedAddresses;
  uint32_t numSavedAddresses;
} asmAddresses;

uint32_t assembleSingleDataTransfer(char **tokens, linkedList *list, asmAddresses *addresses);

uint32_t assembleLDR(uint32_t instructionWord, char **tokens, asmAddresses *addresses);

uint32_t assembleInstruction(char **tokens, linkedList *list, listEntries *symbolTable, asmAddresses *addresses);

void initialiseAddresses(asmAddresses *addresses, uint32_t lastAddress);

#endif
