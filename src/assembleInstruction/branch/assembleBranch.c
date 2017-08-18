/*
 * branch.c
 *
 *  Created on: 3 Jun 2015
 *      Author: am5514
 */

#include "assembleBranch.h"

uint32_t assembleBranch(char **tokens, linkedList *list,
    listEntries *symbolTable, uint32_t currentAddress) {
  uint32_t instructionWord = 0;
  /* 10 = 0xA (1010) */
  instructionWord = setBits(instructionWord, BRANCH_BIT_24, BRANCH_BIT_27, 10);
  char *mnemonic = tokens[0];
  void *instruction = getElement(list, mnemonic);
  asmBranch *bInstruction = (asmBranch*) instruction;
  uint8_t cond = bInstruction->cond;
  instructionWord = setBits(instructionWord, COND_BIT_START, COND_BIT_END,
      cond);
  char *label = tokens[1];
  uint32_t labelAddress = findLabelAddress(label, symbolTable);
  int32_t offset = labelAddress - currentAddress - 8;
  offset >>= 2;
  instructionWord = setBits(instructionWord, OFFSET_BIT_START, OFFSET_BIT_END,
      offset);
  return instructionWord;

}

