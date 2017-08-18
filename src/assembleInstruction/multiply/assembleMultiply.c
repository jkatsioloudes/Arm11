/*
 * assembleMultiply.c
 *
 *  Created on: 3 Jun 2015
 *      Author: am5514
 */

#include "assembleMultiply.h"

uint32_t assembleMultiply(char **tokens, linkedList *list) {
  uint32_t instructionWord = 0;
  instructionWord = setBits(instructionWord, 22, 27, 0);
  char *mnemonic = tokens[0];
  void *instruction = getElement(list, mnemonic);
  asmMultiply *mInstruction = (asmMultiply*) instruction;
  instructionWord = setBits(instructionWord, 28, 31, 14);
  instructionWord = setBits(instructionWord, 20, 20, mInstruction->S);
  instructionWord = setBits(instructionWord, 21, 21, mInstruction->A);
  instructionWord = setBits(instructionWord, 4, 7, 9);
  uint8_t destReg = extract(tokens[1], "r%d");
  uint8_t srcReg1 = extract(tokens[2], "r%d");
  uint8_t srcReg2 = extract(tokens[3], "r%d");
  instructionWord = setBits(instructionWord, 16, 19, destReg);
  instructionWord = setBits(instructionWord, 8, 11, srcReg2);
  instructionWord = setBits(instructionWord, 0, 3, srcReg1);
  if (strcmp(mnemonic, "mul") == 0) {
    return assembleMul(instructionWord, tokens);
  } else {
    return assembleMla(instructionWord, tokens);
  }
}

uint32_t assembleMul(uint32_t instructionWord, char **tokens) {
  instructionWord = setBits(instructionWord, 12, 15, 0);
  return instructionWord;
}

uint32_t assembleMla(uint32_t instructionWord, char **tokens) {
  uint8_t srcReg3 = extract(tokens[4], "r%d");
  instructionWord = setBits(instructionWord, 12, 15, srcReg3);
  return instructionWord;
}
