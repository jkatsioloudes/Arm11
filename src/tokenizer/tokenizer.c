/*
 * tokenizer.c
 *
 *  Created on: 30 May 2015
 *      Author: pk1914
 */

#include "tokenizer.h"

/* Tokenizes a file by first converting it into lines and then tokenizing
 * every line. */
asmInstruction **tokenize(char *fileName) {

  FILE *file = fopen(fileName, "r");
  checkFile(file, "Failed to open file ", FILE_ERROR);

  /* Count the number of lines in the file */
  uint32_t numberOfLines = countLines(file);

  /* Return NULL if the file is empty */
  if (numberOfLines == 0) {
    return NULL;
  } else {

    /* Read the file and convert it to an array of strings */
    char **lines = convertToLines(file, numberOfLines);

    asmInstruction **instructions = malloc(
        numberOfLines * sizeof(asmInstruction*));
    checkAlloc(instructions, "Failed to allocate memory for asmInstruction ",
        MEMORY_ALLOCATE_FAILURE);

    /* Tokenize each line */
    for (int count = 0; count < numberOfLines; ++count) {
      instructions[count] = tokenizeLine(lines[count]);
    }

    /* Added free */
    for (int i = 0; i < numberOfLines; i++) {
      free(lines[i]);
    }
    free(lines);

    fclose(file);
    return instructions;
  }

}

/* Tokenizes a single string */
asmInstruction *tokenizeLine(char *line) {

  /* Allocate enough memory for the structure*/
  asmInstruction *asmInstr = calloc(1, sizeof(*asmInstr));
  checkAlloc(asmInstr, "Failed to allocate memory for asmInstruction ",
      MEMORY_ALLOCATE_FAILURE);

  /* Number of tokens in the string */
  uint32_t numberOfTokens = countTokens(line);

  /* Duplicate the string to not trash the line */
  asmInstr->buffer = strdup(line);

  char *token = strtok(asmInstr->buffer, " ,");
  uint32_t index = 0;

  while (token != NULL) {
    void *nextToken = realloc(asmInstr->args,
        (numberOfTokens + 1) * sizeof(asmInstr->args));
    asmInstr->args = nextToken;
    asmInstr->args[index++] = token;
    token = strtok(NULL, " ,");
  }

  return asmInstr;
}

/* Frees an assembly instruction structure */
void freeasmInstruction(asmInstruction *asmInstr) {
  free(asmInstr->buffer);
  free(asmInstr->args);
  free(asmInstr);
}

void freeTokens(asmInstruction **asmInstr, uint32_t numberOfLines) {
  for (int i = 0; i < numberOfLines; i++) {
    freeasmInstruction(asmInstr[i]);
  }
  free(asmInstr);
}

/* Reads a file and converts it to an array of strings, one for each line. */
char **convertToLines(FILE *file, int numberOfLines) {

  /* Allocate enough memory to hold all the lines */
  char **lines = malloc(numberOfLines * sizeof(char*));
  checkAlloc(lines, "Failed to allocate memory for lines ",
      MEMORY_ALLOCATE_FAILURE);

  for (int i = 0; i < numberOfLines; i++) {
    /* Allocate enough memory for each line */
    lines[i] = malloc(MAX_LINE_LENGTH * sizeof(char));
    if (fgets(lines[i], MAX_LINE_LENGTH - 1, file) == NULL) {
      break;
    }
    lines[i] = removeLastChar(lines[i]);
  }
  /* Reset the file pointer */
  rewind(file);
  return lines;
}

/* Counts the number of tokens in a line */
uint32_t countTokens(char *line) {
  /* The correct way to do this! */
  uint32_t numberOfTokens = 0;

  /* Use a copy of the string */
  char *copy = strdup(line);

  char *tokens = strtok(copy, " ,");
  while (tokens != NULL) {
    tokens = strtok(NULL, " ,");
    numberOfTokens++;
  }

  /* Free the copy*/
  free(copy);
  return numberOfTokens;
}

/* Reads a file and returns the number of lines in this file. */
uint32_t countLines(FILE *file) {
  uint32_t lines = 0;
  int32_t c;
  int32_t last = '\n';
  while (EOF != (c = fgetc(file))) {
    if (c == '\n' && last != '\n') {
      ++lines;
    }
    last = c;
  }
  /* Reset the file pointer to the start of the file */
  rewind(file);
  return lines;
}

/* Removes the last character from a string ONLY IF C/MALLOC'ED()! */
char* removeLastChar(char *str) {
  str[strlen(str) - 1] = '\0';
  return str; //newString;
}

/* Gets last character of a token */
char getEndToken(char *str) {
  return str[strlen(str) - 1];
}

/* Extracts number from token */
/* Returns 0 on failure although I think it should return -1 */
int32_t extract(const char *string, const char *format) {
  uint32_t value;
  if (sscanf(string, format, &value) == 1) {
    return value;
  } else {
    return 0;
  }
}
