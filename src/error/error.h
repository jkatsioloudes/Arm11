/*
 * error.h
 *
 *  Created on: 6 Jun 2015
 *      Author: am5514
 */

#ifndef ERROR_H_
#define ERROR_H_

#include <stdio.h>
#include <stdlib.h>
#include "../error/error.h"

/* Error code enum */
typedef enum {
  ARGUMENT_ERROR = -1,
  MEMORY_ALLOCATE_FAILURE = -2,
  FILE_ERROR = -3,
  ASSEMBLER_ERROR = -4,
  DISASSEMBLER_ERROR = -5,
} error;

/* Checks for correct allocation of memory */
void checkAlloc(void *memory,const char *error,int errorCode);

/* Checks for correct file opening */
void checkFile(FILE *file,const char *error,int errorCode);

#endif /* ERROR_H_ */
