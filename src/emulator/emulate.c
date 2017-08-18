/*
 *
 * Purpose: This is the main file that contains the emulator
 * Usage: emulate path/to/binary
 *
 */

#include "emulate.h"

#define EMULATE_EXPECTED_ARGUMENTS 1 /* Expected number of arguments passed in should be 1*/

//#define EMULATE 1

#ifdef EMULATE

int main(int argc, char **argv) {
	ARM11 *arm11;
	switch (argc) {
	case EMULATE_EXPECTED_ARGUMENTS + 1:
#ifndef TEST_CASE
	  printf("Emulating %s\n",argv[1]); //Remove this for the test case
#endif
		arm11 = initialiseProcessor();
		loadBinary(argv[1], arm11->memory);
		pipeline(arm11);
		printRegisters(arm11);
		printMemory(arm11);
		freeProcessor(arm11);
		break;
	default:
		fprintf(stderr,
				"Expecting only %d argument(s) which is the binary file but received %d\n",
				EMULATE_EXPECTED_ARGUMENTS ,argc - 1);
		exit(ARGUMENT_ERROR);
	}
	return EXIT_SUCCESS;
}

#endif

