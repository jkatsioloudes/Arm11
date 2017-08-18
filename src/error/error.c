/*
 * error.c
 *
 *  Created on: 6 Jun 2015
 *      Author: am5514
 */

#include "error.h"

/* Checks for correct allocation of memory */
void checkAlloc(void *memory, const char *error, int errorCode) {
  if (memory == NULL) {
    perror(error);
    exit(errorCode);
  }
}

/* Checks for correct file opening */
void checkFile(FILE *file, const char *error, int errorCode) {
  if (file == NULL) {
    perror(error);
    exit(errorCode);
  }
}
