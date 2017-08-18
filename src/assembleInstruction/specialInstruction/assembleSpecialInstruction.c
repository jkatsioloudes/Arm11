/*
 * assembleSpecialInstruction.c
 *
 *  Created on: 12 Jun 2015
 *      Author: nv214
 */
#include <stdint.h>
#include "assembleSpecialInstruction.h"

uint32_t assembleSpecialInstruction(char **tokens, linkedList *list) {
  uint32_t instructionWord = 0;
  char *mnemonic = tokens[0];
  if (strcmp(mnemonic, "andeq") == 0) {
    return instructionWord;
  } else {
    uint8_t destReg = extract(tokens[1], "r%d");
    void *instruction = getElement(list, "mov");
    asmDataProcessing *dpInstruction = (asmDataProcessing*) instruction;
    instructionWord = setBits(instructionWord, 28, 31, dpInstruction->cond);
    instructionWord = setBits(instructionWord, 25, 27, 0);
    instructionWord = setBits(instructionWord, 21, 24, dpInstruction->opcode);
    instructionWord = setBits(instructionWord, 20, 20, dpInstruction->S);
    instructionWord = setBits(instructionWord, 12, 15, destReg);
    instructionWord = setBits(instructionWord, 16, 19, 0);
    char *expression = tokens[2];
    uint8_t shift;
    if (expression[2] == 'x') {
      shift = extract(expression, "#0x%08x");
    } else {
      shift = extract(expression, "#%d");
    }
    /* Sets Rm to destination register */
    instructionWord = setBits(instructionWord, 0, 3, destReg);
    /* Specifies shift is a constant amount */
    instructionWord = setBits(instructionWord, 4, 4, 0);
    /* Sets shift amount */
    instructionWord = setBits(instructionWord, 7, 11, shift);
    return instructionWord;
  }
}

