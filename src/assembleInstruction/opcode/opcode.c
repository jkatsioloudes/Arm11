/*
 * opcode.c
 *
 *  Created on: 2 Jun 2015
 *      Author: am5514
 */

#include "opcode.h"
#include <string.h>

#define LABEL 0xFFFFFFFF

uint32_t assembleInstruction(char **tokens, linkedList *list,
    listEntries *symbolTable, asmAddresses *addresses) {
  char *mnemonic = tokens[0];
  if ((strcmp(mnemonic, "mov") == 0) || (strcmp(mnemonic, "add") == 0)
      || (strcmp(mnemonic, "sub") == 0) || (strcmp(mnemonic, "rsb") == 0)
      || (strcmp(mnemonic, "and") == 0) || (strcmp(mnemonic, "orr") == 0)
      || (strcmp(mnemonic, "eor") == 0) || (strcmp(mnemonic, "tst") == 0)
      || (strcmp(mnemonic, "cmp") == 0) || (strcmp(mnemonic, "teq") == 0)) {
    return assembleDataProcessing(tokens, list);
  } else if ((strcmp(mnemonic, "mul") == 0) || (strcmp(mnemonic, "mla") == 0)) {
    return assembleMultiply(tokens, list);
  } else if ((strcmp(mnemonic, "ldr") == 0) || (strcmp(mnemonic, "str") == 0)) {

    return assembleSingleDataTransfer(tokens, list, addresses);

  } else if ((strcmp(mnemonic, "beq") == 0) || (strcmp(mnemonic, "bne") == 0)
      || (strcmp(mnemonic, "bge") == 0) || (strcmp(mnemonic, "blt") == 0)
      || (strcmp(mnemonic, "bgt") == 0) || (strcmp(mnemonic, "ble") == 0)
      || (strcmp(mnemonic, "b") == 0)) {
    return assembleBranch(tokens, list, symbolTable, addresses->currentAddress);
  } else if ((strcmp(mnemonic, "andeq") == 0)
      || (strcmp(mnemonic, "lsl") == 0)) {
    return assembleSpecialInstruction(tokens, list);
  } else {
    return LABEL;
  }
}

void initialiseAddresses(asmAddresses *addresses, uint32_t lastAddress) {
  addresses->numSavedAddresses = 0;
  addresses->currentAddress = 0;
  addresses->lastAddress = lastAddress;
}
