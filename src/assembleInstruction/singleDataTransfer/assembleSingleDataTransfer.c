/*
 * assembleSingleDataTransfer.c
 *
 *  Created on: 3 Jun 2015
 *      Author: nv214
 */

#include "assembleSingleDataTransfer.h"

/* This file needs comments */
uint32_t assembleSingleDataTransfer(char **tokens, linkedList *list,
		asmAddresses *addresses) {

	uint32_t instructionWord = 0;
	/* Bits 26-27 represent the decimal value 1 */
	instructionWord = setBits(instructionWord, 26, 27, 1);
	char *mnemonic = tokens[0];
	void *instruction = getElement(list, mnemonic);
	asmSingleDataTransfer *sInstruction = (asmSingleDataTransfer*) instruction;
	instructionWord = setBits(instructionWord, 28, 31, 14);
	instructionWord = setBits(instructionWord, 20, 20, sInstruction->L);
	instructionWord = setBits(instructionWord, 25, 25, 0);
	instructionWord = setBits(instructionWord, 21, 22, 0);
	instructionWord = setBits(instructionWord, 23, 23, 1);
	uint8_t destReg = extract(tokens[1], "r%d");
	instructionWord = setBits(instructionWord, 12, 15, destReg);
	if (strcmp(mnemonic, "ldr") == 0) {
		if ((tokens[2])[0] == '=') {
			if (atoi(tokens[2] + 3) <= 0xFF) { /* Use extract() here */
				char *movTokens[] = { "mov", tokens[1], tokens[2] };
				return assembleDataProcessing(movTokens, list);
			}
		}
		return assembleLDR(instructionWord, tokens, addresses);
	} else {
		return assembleSTR(instructionWord, tokens, addresses->currentAddress);
	}
}

uint32_t assembleLDR(uint32_t instructionWord, char **tokens,
		asmAddresses *addresses) {
	char *address = tokens[2];
	if (address[0] == '=') {
		uint32_t expr = (
				address[2] == 'x' ?
						extract(address, "=0x%08x") : extract(address, "=%d"));

		instructionWord = setBits(instructionWord, 16, 19, 15); // Sets base register to PC
		instructionWord = setBits(instructionWord, 25, 25, 0); // Clears I flag
		instructionWord = setBits(instructionWord, 24, 24, 1); // Sets P flag

		addresses->savedAddresses[addresses->numSavedAddresses] = expr;
		addresses->numSavedAddresses++;
		uint32_t lastSavedAddress = addresses->lastAddress
				+ (addresses->numSavedAddresses * 4);
		int32_t offset = (lastSavedAddress - addresses->currentAddress - 8);
		if (offset < 0) {
			instructionWord = setBits(instructionWord, 23, 23, 0);
		}
		instructionWord = setBits(instructionWord, 0, 11, offset); // Sets offset
	} else {
		instructionWord = setBits(instructionWord, 25, 25, 0); // Sets I flag
		char *baseReg = tokens[2];
		char *offset = tokens[3];
		instructionWord = setBits(instructionWord, 16, 19,
				extract(baseReg, "[r%d]"));
		if (getEndToken(baseReg) == ']' && offset != 0) {
			instructionWord = setBits(instructionWord, 24, 24, 0);
			instructionWord = (
					offset[2] == 'x' ?
							setBits(instructionWord, 0, 11, extract(offset, "#0x%08x")) :
							setBits(instructionWord, 0, 11, extract(offset, "#%d")));
			if (offset[1] == '-') {
				instructionWord = setBits(instructionWord, 23, 23, 0);
			}
			return instructionWord;

		} else {
			instructionWord = setBits(instructionWord, 24, 24, 1);
			if (offset == 0) {
				instructionWord = setBits(instructionWord, 0, 11, 0);
				return instructionWord;
			} else {
				if (offset[1] != '-') {
					instructionWord = (
							offset[2] == 'x' ?
									setBits(instructionWord, 0, 11, extract(offset, "#0x%08x]")) :
									setBits(instructionWord, 0, 11, extract(offset, "#%d]")));
				} else {
					instructionWord = (
							offset[3] == 'x' ?
									setBits(instructionWord, 0, 11,
											extract(offset, "#-0x%08x]")) :
									setBits(instructionWord, 0, 11, extract(offset, "#-%d]")));
					/* Shows negative offset */
					instructionWord = setBits(instructionWord, 23, 23, 0);
				}
				return instructionWord;
			}
		}
	}
	return instructionWord;
}

uint32_t assembleSTR(uint32_t instructionWord, char **tokens,
		uint32_t currentAddress) {
	char *baseReg = tokens[2];
	char *offset = tokens[3];
	instructionWord = setBits(instructionWord, 16, 19, extract(baseReg, "[r%d]"));
	if (getEndToken(baseReg) == ']' && offset != 0) {
		if (offset[0] != 'r') {
			instructionWord = setBits(instructionWord, 24, 24, 0);

			instructionWord = (
					offset[2] == 'x' ?
							setBits(instructionWord, 0, 11, extract(offset, "#0x%08x")) :
							setBits(instructionWord, 0, 11, extract(offset, "#%d")));

			if (offset[1] == '-') {
				instructionWord = setBits(instructionWord, 23, 23, 0);
			}
			return instructionWord;
		} else {
			instructionWord = setBits(instructionWord, 24, 24, 1);
			instructionWord = setBits(instructionWord, 24, 25, 2);
			instructionWord = setBits(instructionWord, 0, 11, extract(offset, "r%d"));
			return instructionWord;
		}
	} else {
		instructionWord = setBits(instructionWord, 24, 24, 1);
		if (offset == 0) {
			instructionWord = setBits(instructionWord, 0, 11, 0);
			return instructionWord;
		} else {
			if (offset[0] != 'r') {
				instructionWord = (
						offset[2] == 'x' ?
								setBits(instructionWord, 0, 11,
										extract(offset, "#0x%08x")) :
								setBits(instructionWord, 0, 11,
										extract(offset, "#%d")));
				if (offset[1] == '-') {
					instructionWord = setBits(instructionWord, 23, 23, 0);
				}
			} else {
				instructionWord = setBits(instructionWord, 0, 11,
						extract(offset, "r%d"));
				instructionWord = setBits(instructionWord, 24, 25, 3);
			}
			return instructionWord;
		}
	}
	return instructionWord;
}
