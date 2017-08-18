/*
 * opcode.c
 *
 *  Created on: 1 Jun 2015
 *      Author: am5514
 */

#include "assembleDataProcessing.h"

uint32_t assembleDataProcessing(char **tokens, linkedList *list) {
  uint32_t instructionWord = 0;
  instructionWord = setBits(instructionWord, 25, 27, 1);
  char *mnemonic = tokens[0];
  void *instruction = getElement(list, mnemonic);
  asmDataProcessing *dpinstruction = (asmDataProcessing*) instruction;
  uint8_t opcode = dpinstruction->opcode;
  instructionWord = setBits(instructionWord, 21, 24, opcode);
  instructionWord = setBits(instructionWord, 28, 31, dpinstruction->cond);
  instructionWord = setBits(instructionWord, 20, 20, dpinstruction->S);
  switch (opcode) {
  case AND:
  case EOR:
  case SUB:
  case RSB:
  case ADD:
  case ORR:
    return assembleCalculate(instructionWord, tokens);
  case TST:
  case TEQ:
  case CMP:
    return assembleComparison(instructionWord, tokens);
  case MOV:
    return assembleMov(instructionWord, tokens);
  }
  return instructionWord;
}

uint32_t assembleComparison(uint32_t instructionWord, char **tokens) {
  uint8_t srcReg = extract(tokens[1], "r%d");
  uint32_t operand2;
  if (*(tokens[2] + 2) == 'x') {
    operand2 = extract(tokens[2], "#0x%08x");
  } else if (*(tokens[2]) == 'r') {
    operand2 = extract(tokens[2], "r%d");
    instructionWord = setBits(instructionWord, 25, 25, 0);
  } else {
    operand2 = extract(tokens[2], "#%d");
  }
  instructionWord = setBits(instructionWord, 16, 19, srcReg);
  instructionWord = setBits(instructionWord, 12, 15, 0);
  instructionWord = setBits(instructionWord, 0, 11, operand2);
  return instructionWord;
}

uint32_t assembleCalculate(uint32_t instructionWord, char **tokens) {
  uint8_t destReg = extract(tokens[1], "r%d");
  uint8_t srcReg = extract(tokens[2], "r%d");
  uint32_t operand2;
  char *op2 = tokens[3];
  if (op2[2] == 'x') {
    operand2 = extract(tokens[3], "#0x%08x");
  } else if (*(tokens[3]) == 'r') {
    operand2 = extract(tokens[3], "r%d");
    instructionWord = setBits(instructionWord, 25, 25, 0);
  } else {
    operand2 = extract(tokens[3], "#%d");
  }
  instructionWord = setBits(instructionWord, 16, 19, srcReg);
  instructionWord = setBits(instructionWord, 12, 15, destReg);
  instructionWord = setBits(instructionWord, 0, 11, operand2);
  return instructionWord;
}

uint32_t assembleMov(uint32_t instructionWord, char **tokens) {
  uint8_t destReg = extract(tokens[1], "r%d");
  char *op2 = tokens[2];
  uint32_t operand2;
  if (op2[0] == 'r') {
    operand2 = extract(op2, "r%d");
    instructionWord = setBits(instructionWord, 25, 25, 0);
  } else {
    if (op2[2] == 'x') {
      operand2 = extract(op2 + 1, "0x%08x");
    } else {
      operand2 = extract(op2 + 1, "%d");
    }
  }
  instructionWord = setBits(instructionWord, 16, 19, 0); // Sets Rn to zero
  instructionWord = setBits(instructionWord, 12, 15, destReg);

  /* THIS CODE DOES NOT WORK */
  if (operand2 > 0xFF) {
    uint8_t shiftedNum;
    uint8_t rotations;
    for (rotations = 1; rotations <= 32; rotations++) {
      shiftedNum = asmRotateLeft(operand2, rotations);
      uint32_t origNum = asmRotateRight(shiftedNum, rotations);
      if (origNum == operand2) {
        if (rotations % 2 != 0) { //Can't have odd number of rotations
          shiftedNum = asmRotateLeft(operand2, ++rotations);
        }
        break;
      }
    }
    instructionWord = setBits(instructionWord, 0, 7, shiftedNum);
    instructionWord = setBits(instructionWord, 8, 11, rotations / 2);
    return instructionWord;
  }
  /****************************/

  instructionWord = setBits(instructionWord, 0, 11, operand2);
  return instructionWord;
}
