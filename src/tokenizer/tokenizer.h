/*
 * tokenizer.h
 *
 *  Created on: 30 May 2015
 *      Author: pk1914
 */

#ifndef TOKENIZER_H_
#define TOKENIZER_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "../error/error.h"

#define MAX_LINE_LENGTH 511 /* Maximum possible length of a line */
#define MAX_INSTRUCTION_LENGTH 6
#define MAX_WORD_LENGTH 4
#define MAX_INSTRUCTIONS 10


/* The asmInstruction struct */
typedef struct {
	char **args; /* An array of strings*/
	char *buffer; /* Temporary buffer for tokenizer */
} asmInstruction;

/* Tokenizes a file and returns an array of pointers to asmInstruction */
asmInstruction **tokenize(char *file);

/* Tokenizes a line (string) and returns a pointer to an asmInstruction */
asmInstruction *tokenizeLine(char *line);

/* Frees an assembly instruction structure */
void freeasmInstruction(asmInstruction *asmInstr);

void freeTokens(asmInstruction **asmInstr,uint32_t numberOfLines);

/* Reads a file and converts it to an array of strings */
char **convertToLines(FILE *file, int numberOfLines);

/* Removes the last character from a string ONLY IF C/MALLOC'ED()! */
char* removeLastChar(char *str);

/* Counts the number of lines in a file, excluding any empty lines. */
uint32_t countLines(FILE *file);

/* Counts the number of tokens in a string */
uint32_t countTokens(char line[]);

/* Tokenizes a string */
char** tokenizeString(char *str);

/* Gets last character of a token */
char getEndToken(char *str);

/* Extracts number from token */
int32_t extract(const char *string, const char *format);

#endif /* TOKENIZER_H_ */
