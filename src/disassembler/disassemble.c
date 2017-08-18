/*
 * disassemble.c
 *
 *  Created on: 14 Jun 2015
 *      Author: am5514
 */

#include "disassemble.h"

/* Decodes a 32-bit instruction */
instruction* decode(uint32_t fetched) {

	/* Allocate memory for each instruction but remember to call free()! */
	instruction *type = malloc(sizeof(instruction));
	checkAlloc(type, "Failed to allocate memory for instruction ",
			MEMORY_ALLOCATE_FAILURE);
	type->id = fetched;
	type->cond = getBits(fetched, COND_BIT_START, COND_BIT_END);

	switch (getType(fetched)) {
	case BRANCH_INSTR:
		type->offset = getBits(fetched, OFFSET_BIT_START_B, OFFSET_BIT_END_B);
		break;
	case MULTIPLY_INSTR:
		type->A = getBits(fetched, A_BIT, A_BIT);
		type->S = getBits(fetched, S_BIT, S_BIT);
		type->rd = getBits(fetched, RD_BIT_START_M, RD_BIT_END_M);
		type->rn = getBits(fetched, RN_BIT_START_M, RN_BIT_END_M);
		type->rs = getBits(fetched, RS_BIT_START_M, RS_BIT_END_M);
		type->rm = getBits(fetched, RM_BIT_START_M, RM_BIT_END_M);
		break;
	case DATA_PROCESSING_INSTR:
		type->I = getBits(fetched, I_BIT, I_BIT);
		type->S = getBits(fetched, S_BIT, S_BIT);
		type->opcode = getBits(fetched, OPCODE_BIT_START, OPCODE_BIT_END);
		type->rn = getBits(fetched, RN_BIT_START_DP, RN_BIT_END_DP);
		type->rd = getBits(fetched, RD_BIT_START_DP, RD_BIT_END_DP);
		type->operand2 = getBits(fetched, OPERAND2_BIT_START, OPERAND2_BIT_END);
		break;
	case SINGLE_DATA_TRANSFER_INSTR:
		type->I = getBits(fetched, I_BIT, I_BIT);
		type->P = getBits(fetched, P_BIT, P_BIT);
		type->U = getBits(fetched, U_BIT, U_BIT);
		type->L = getBits(fetched, L_BIT, L_BIT);
		type->rn = getBits(fetched, RN_BIT_START_SDT, RN_BIT_END_SDT);
		type->rd = getBits(fetched, RD_BIT_START_SDT, RD_BIT_END_SDT);
		type->offset = getBits(fetched, OFFSET_BIT_START_SDT, OFFSET_BIT_END_SDT);
		break;
	default: //This case is never reached though; ensured by getType()
		type->id = 0;
	}
	return type;
}

/* Disassembles a single instruction */
char *disassembleInstruction(uint32_t instructionWord) {

	/* The assembly source line */
	char *instructionWord = malloc(MAX_LINE_LENGTH);

	/* The mnemonic*/
	char *mnemonic = malloc(10);
	char *op1 = malloc(10);
	char *op2 = malloc(10);
	char *op3 = malloc(10);

	/* Decode the instruction */
	instruction *instruction = decode(instructionWord);

	/* Get the type*/
	uint32_t type = getType(instruction->id);

	switch (type) {
	case DATA_PROCESSING_INSTR:

		switch (instruction->opcode) {

		case AND:
			strcpy(mnemonic,"and");
			break;
		case EOR:
			strcpy(mnemonic,"eor");
			break;
		case SUB:
			strcpy(mnemonic,"sub");
			break;
		case RSB:
			strcpy(mnemonic,"rsb");
			break;
		case ADD:
			strcpy(mnemonic,"add");
			break;
		case TST:
			strcpy(mnemonic,"tst");
			break;
		case TEQ:
			strcpy(mnemonic,"teq");
			break;
		case CMP:
			strcpy(mnemonic,"cmp");
			break;
		case ORR:
			strcpy(mnemonic,"orr");
			break;
		case MOV:
			strcpy(mnemonic,"mov");
			break;
		}


		/* First operand */




		break;

	case BRANCH_INSTR:

		break;

	case SINGLE_DATA_TRANSFER_INSTR:

		break;

	case MULTIPLY_INSTR:

		break;


	default:

		break
	}

	return NULL;
}

/* Loads the binary file into memory */
void loadFile(const char *fileName, uint32_t *memory) {

	FILE* file = fopen(fileName, "r");
	checkFile(file, "Failed to open file ", FILE_ERROR);

	/* The file read loop */
	fread(memory, 1, MEMORY_SIZE, file);
	fclose(file);

}

/* Disassembles src and writes the output to dst */
bool disassembleFile(char *src, char *dst) {

	/* The assembly source file */
		FILE *inputFile = fopen(src, "r");
		checkFile(inputFile, "Failed to open input file ", FILE_ERROR);

		uint32_t numberOfLines = countLines(inputFile);

		/* But counts empty spaces too */
		if (numberOfLines == 0) {
			fprintf(stderr, "Source file %s is empty\n", src);
			return false;
		}

		/* The output file */
		FILE *outputFile = fopen(dst, "wb");
		checkFile(outputFile, "Failed to open file ", FILE_ERROR);

		uint32_t instruction;
		uint32_t *memory = malloc(MEMORY_SIZE * sizeof(uint32_t));

		/* Load the binary into memory */
		loadFile(src,memory);

		/* Disassemble each instruction and write it to file */
		for (int i = 0; i<numberOfLines; i++) {
			/* Read an instruction from memory (file) */
			instruction = memory[i];
			/* Decode the instruction */
			char *instructionWord = disassembleInstruction(instruction);

			/* Write it to file */
			printf("%s\n",instructionWord);
			//fwrite(&instructionWord, sizeof(instructionWord), 1, outputFile);
		}

		free(memory);
		fclose(inputFile);
		fclose(outputFile);

		return true;
}

int main(int argc, char *argv[]) {

	char *src = argv[1];
	char *dst = argv[2];

	switch (argc) {
	case DISASSEMBLE_EXPECTED_ARGUMENTS + 1:
		if (disassembleFile(src, dst) != true) {
			fprintf(stderr, "Failed to disassemble source file %s\n", src);
			exit(DISASSEMBLER_ERROR);
		}
		break;
	default:
		fprintf(stderr, "Expecting only %d argument(s) but received %d\n",
				DISASSEMBLE_EXPECTED_ARGUMENTS, argc - 1);
		exit(DISASSEMBLER_ERROR);
		break;
	}

	return EXIT_SUCCESS;
}
