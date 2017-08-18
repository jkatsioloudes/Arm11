/*
 *
 * Purpose: The assembler
 *
 */

#include "assemble.h"

#define ASSEMBLE_EXPECTED_ARGUMENTS 2
#define LABEL 0xFFFFFFFF /* Needs a better name */

/* Assembles a file and return true on success or false on failure */
bool assembleFile(char *src, char *dst) {

	/* The assembly source file */
	FILE *inputFile = fopen(src, "r");
	checkFile(inputFile, "Failed to open input file ", FILE_ERROR);

	uint32_t numberOfLines = countLines(inputFile);

	/* But counts empty spaces too */
	if (numberOfLines == 0) {
		fprintf(stderr, "Source file %s is empty\n", src);
		return false;
	}

	/* What is this list used for again? */
	linkedList *list = createLinkedList();
	initialise(list);

	/* Tokenize the source file */
	asmInstruction **asmInstr = tokenize(src);

	/* If something happened with tokenize */
	if (asmInstr == NULL) {
		fprintf(stderr, "Failed to tokenize source file %s \n", src);
		return false;
	}

	/* Create new symbol table */
	listEntries *symbolTable = createNewSymbolTable(src, asmInstr);

	if (symbolTable == NULL) {
		fprintf(stderr, "Failed to create symbol table\n");
		return false;
	}

	/* This does not take into account the number of labels*/
	/* countLines() counts every line in a file */
	uint32_t lastAddress = ((numberOfLines - 1) * sizeof(uint32_t));
	uint32_t instructionWord = 0;

	/* The output file */
	FILE *outputFile = fopen(dst, "wb");
	checkFile(outputFile, "Failed to open file ", FILE_ERROR);
	asmAddresses *addresses = malloc(sizeof(asmAddresses));
	checkAlloc(addresses, "malloc() failed on addresses ",
			MEMORY_ALLOCATE_FAILURE);

	initialiseAddresses(addresses, lastAddress);
	addresses->savedAddresses = calloc(numberOfLines, sizeof(uint32_t));
	checkAlloc(addresses, "malloc() failed on addresses ",
			MEMORY_ALLOCATE_FAILURE);

	/* Assemble each instruction and write it to file */
	for (int i = 0; i <= (lastAddress / sizeof(uint32_t)); i++) {
		instructionWord = assembleInstruction(asmInstr[i]->args, list, symbolTable,
				addresses);

		/* ASSEMBLING LABELS DOES NOT WORK!*/
		/* Every new label in the source file offsets the ldr instruction */
		if (instructionWord == LABEL) {
			continue;
		}

		addresses->currentAddress += sizeof(uint32_t);
		uint32_t actualInstruction = changeEndianness(instructionWord);
		fwrite(&instructionWord, sizeof(actualInstruction), 1, outputFile);
	}

	/* Write the remaining addresses to the end of file */
	if (addresses->numSavedAddresses != 0) {
		fwrite(addresses->savedAddresses, sizeof(uint32_t),
				addresses->numSavedAddresses, outputFile);
	}

	free(addresses->savedAddresses);
	free(addresses);
	freeLinkedList(list);
	freeList(symbolTable);
	freeTokens(asmInstr, numberOfLines);
	fclose(inputFile);
	fclose(outputFile);
	return true;
}

//#define ASSEMBLER
//#define TEST_CASE

#ifdef ASSEMBLER

int main(int argc, char *argv[]) {

	char *src = argv[1];
	char *dst = argv[2];

	switch (argc) {
	case ASSEMBLE_EXPECTED_ARGUMENTS + 1:
#ifndef TEST_CASE
	  printf("Assembling %s\nOutput file %s\n",src,dst); //Remove this for the test case
#endif
		if (assembleFile(src, dst) != true) {
			fprintf(stderr, "Failed to assemble source file %s\n", src);
			exit(ASSEMBLER_ERROR);
		}
#ifndef TEST_CASE
		printf("All OK!\n"); //Remove this for the test case
#endif
		break;

	default:
		fprintf(stderr, "Expecting only %d argument(s) but received %d\n",
		ASSEMBLE_EXPECTED_ARGUMENTS, argc - 1);
		exit(ARGUMENT_ERROR);
		break;
	}

	return EXIT_SUCCESS;
}
#endif
