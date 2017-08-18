#include "twoPass.h"

/* Needs comments */
listEntries *createNewSymbolTable(char *fileName, asmInstruction **instr) {

	uint32_t PC = 0;

	/* We just need the number of lines from the file */
	FILE *file = fopen(fileName, "r");
	checkFile(file, "Failed to open file ", FILE_ERROR);

	uint32_t numberOfLines = countLines(file);

	char *lineArguments = malloc(sizeof(char));
	checkAlloc(lineArguments, "Failed to allocate memory for lineArguments ",
			MEMORY_ALLOCATE_FAILURE);

	/* Create the symbol table */
	listEntries *newSymbolTablePtr = createNewList();
	listIterator listTail = listEnd(newSymbolTablePtr);

	for (int i = 0; i < numberOfLines; i++) {
		strcpy(lineArguments, instr[i]->args[0]);
		if (lineArguments[strlen(lineArguments) - 1] == ':') {
			char *label = malloc(MAX_LINE_LENGTH * sizeof(char));
			strcpy(label, lineArguments);
			insertToList(newSymbolTablePtr, listTail, label, PC);
			continue;
		}
		PC += sizeof(uint32_t);
	}

	fclose(file);
	free(lineArguments);

	return newSymbolTablePtr;
}
