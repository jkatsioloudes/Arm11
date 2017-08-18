/*
 * initialise.c
 *
 *  Created on: 3 Jun 2015
 *      Author: am5514
 */

#include "initialise.h"

void addDataProcessingOpcode(linkedList *list, char *mnemonic, uint8_t opcode,
    bool S, uint8_t cond) {
  asmDataProcessing *dp = malloc(sizeof(asmDataProcessing));
  dp->mnemonic = mnemonic;
  dp->opcode = opcode;
  dp->S = S;
  dp->cond = cond;
  insertNode(list, (void*) dp, mnemonic);
}

void addMultiply(linkedList *list, char *mnemonic, bool A, bool S) {
  asmMultiply *mul = malloc(sizeof(asmMultiply));
  mul->mnemonic = mnemonic;
  mul->A = A;
  mul->S = S;
  insertNode(list, (void*) mul, mnemonic);
}

void addSingleDataTransferOpcode(linkedList *list, char *mnemonic, bool L) {
  asmSingleDataTransfer *sdt = malloc(sizeof(asmSingleDataTransfer));
  sdt->mnemonic = mnemonic;
  sdt->L = L;
  insertNode(list, (void*) sdt, mnemonic);
}

void addBranchOpcode(linkedList *list, char *mnemonic, uint8_t cond) {
  asmBranch *b = malloc(sizeof(asmBranch));
  b->mnemonic = mnemonic;
  b->cond = cond;
  insertNode(list, (void*) b, mnemonic);
}

void initialise(linkedList *list) {
  addDataProcessingOpcode(list, "and", AND, false, 14);
  addDataProcessingOpcode(list, "eor", EOR, false, 14);
  addDataProcessingOpcode(list, "sub", SUB, false, 14);
  addDataProcessingOpcode(list, "rsb", RSB, false, 14);
  addDataProcessingOpcode(list, "add", ADD, false, 14);
  addDataProcessingOpcode(list, "orr", ORR, false, 14);
  addDataProcessingOpcode(list, "mov", MOV, false, 14);
  addDataProcessingOpcode(list, "tst", TST, true, 14);
  addDataProcessingOpcode(list, "teq", TEQ, true, 14);
  addDataProcessingOpcode(list, "cmp", CMP, true, 14);

  addMultiply(list, "mul", false, false);
  addMultiply(list, "mla", true, false);

  addSingleDataTransferOpcode(list, "ldr", true);
  addSingleDataTransferOpcode(list, "str", false);

  addBranchOpcode(list, "beq", EQUAL);
  addBranchOpcode(list, "bne", NOT_EQUAL);
  addBranchOpcode(list, "bge", GREATER_OR_EQUAL);
  addBranchOpcode(list, "blt", LESS_THAN);
  addBranchOpcode(list, "bgt", GREATER_THAN);
  addBranchOpcode(list, "ble", LESS_THAN_OR_EQUAL);
  addBranchOpcode(list, "b", ALWAYS);
}
