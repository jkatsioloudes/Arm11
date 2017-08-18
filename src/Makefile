CC      = gcc
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -Werror -pedantic

.SUFFIXES: .c .o

all: emulate assemble

assemble: assemble.o bitManipulation.o auxiliary.o tokenizer.o singlyLinkedList.o doublyLinkedList.o twoPass.o assembleDataProcessing.o opcode.o error.o assembleMultiply.o assembleSingleDataTransfer.o assembleBranch.o shifter.o assembleSpecialInstruction.o initialise.o
	$(CC) assemble.o bitManipulation.o auxiliary.o tokenizer.o singlyLinkedList.o doublyLinkedList.o twoPass.o assembleDataProcessing.o opcode.o error.o assembleMultiply.o assembleSingleDataTransfer.o assembleBranch.o shifter.o assembleSpecialInstruction.o initialise.o -o assemble
	
assemble.o: assembler/assemble.c  assembler/assemble.h
	$(CC) $(CFLAGS) assembler/assemble.c -c -o assemble.o
	
tokenizer.o: tokenizer/tokenizer.c error/error.h
	$(CC) $(CFLAGS) tokenizer/tokenizer.c -c -o tokenizer.o
	
singlyLinkedList.o: list/singlyLinkedList/singlyLinkedList.c list/singlyLinkedList/node.h
	$(CC) $(CFLAGS) list/singlyLinkedList/singlyLinkedList.c -c -o singlyLinkedList.o

doublyLinkedList.o: list/doublyLinkedList/doublyLinkedList.c 
	$(CC) $(CFLAGS) list/doublyLinkedList/doublyLinkedList.c -c -o doublyLinkedList.o

twoPass.o: twoPass/twoPass.c tokenizer/tokenizer.h list/doublyLinkedList/doublyLinkedList.h
	$(CC) $(CFLAGS) twoPass/twoPass.c -c -o twoPass.o

assembleDataProcessing.o: assembleInstruction/dataProcessing/assembleDataProcessing.c
	$(CC) $(CFLAGS) assembleInstruction/dataProcessing/assembleDataProcessing.c -c -o assembleDataProcessing.o

opcode.o: assembleInstruction/opcode/opcode.c assembleInstruction/dataProcessing/assembleDataProcessing.h assembleInstruction/singleDataTransfer/assembleSingleDataTransfer.h assembleInstruction/multiply/assembleMultiply.h assembleInstruction/branch/assembleBranch.o
	$(CC) $(CFLAGS) assembleInstruction/opcode/opcode.c -c -o opcode.o
	
assembleSingleDataTransfer.o: assembleInstruction/singleDataTransfer/assembleSingleDataTransfer.c assembleInstruction/opcode/opcode.h
	$(CC) $(CFLAGS) assembleInstruction/singleDataTransfer/assembleSingleDataTransfer.c -c -o assembleSingleDataTransfer.o

assembleBranch.o: assembleInstruction/branch/assembleBranch.c
	$(CC) $(CFLAGS) assembleInstruction/branch/assembleBranch.c -c -o assembleBranch.o
	
assembleMultiply.o: assembleInstruction/multiply/assembleMultiply.c
	$(CC) $(CFLAGS) assembleInstruction/multiply/assembleMultiply.c -c -o assembleMultiply.o
	
assembleSpecialInstruction.o: assembleInstruction/specialInstruction/assembleSpecialInstruction.c
	$(CC) $(CFLAGS) assembleInstruction/specialInstruction/assembleSpecialInstruction.c -c -o assembleSpecialInstruction.o
		
initialise.o: initialise/initialise.c conditions/conditions.h assembleInstruction/opcode/opcode.h assembler/assemble.h assembleInstruction/dataProcessing/assembleDataProcessing.h 
	$(CC) $(CFLAGS) initialise/initialise.c -c -o initialise.o

emulate: emulate.o pipeline.o loader.o auxiliary.o bitManipulation.o conditions.o processor.o branch.o dataProcessing.o singleDataTransfer.o multiply.o shifter.o instruction.o error.o
	$(CC) emulate.o pipeline.o loader.o auxiliary.o bitManipulation.o conditions.o processor.o branch.o dataProcessing.o singleDataTransfer.o multiply.o shifter.o instruction.o error.o -o emulate

emulate.o: emulator/emulate.c instructions/instruction/instruction.h auxiliary/auxiliary.h loader/loader.h bitManipulation/bitManipulation.h pipeline/pipeline.h processor/processor.h shifter/shifter.h
	$(CC) $(CFLAGS) emulator/emulate.c -c -o emulate.o

pipeline.o: pipeline/pipeline.c processor/processor.h bitManipulation/bitManipulation.h pipeline/pipeline.h instructions/instruction/instruction.h loader/loader.h instructions/branch/branch.h instructions/dataProcessing/dataProcessing.h instructions/singleDataTransfer/singleDataTransfer.h conditions/conditions.h
	$(CC) $(CFLAGS) pipeline/pipeline.c -c -o pipeline.o

loader.o: loader/loader.c processor/processor.h loader/loader.h bitManipulation/bitManipulation.h
	$(CC) $(CFLAGS) loader/loader.c -c -o loader.o

auxiliary.o: auxiliary/auxiliary.c processor/processor.h loader/loader.h bitManipulation/bitManipulation.h
	$(CC) $(CFLAGS) auxiliary/auxiliary.c -c -o auxiliary.o

bitManipulation.o: bitManipulation/bitManipulation.c 
	$(CC) $(CFLAGS) bitManipulation/bitManipulation.c -c -o bitManipulation.o
	
conditions.o: conditions/conditions.c 
	$(CC) $(CFLAGS) conditions/conditions.c -c -o conditions.o
	
processor.o: processor/processor.c error/error.h
	$(CC) $(CFLAGS) processor/processor.c -c -o processor.o
	
branch.o: instructions/branch/branch.c 
	$(CC) $(CFLAGS) instructions/branch/branch.c -c -o branch.o
	
singleDataTransfer.o: instructions/singleDataTransfer/singleDataTransfer.c 
	$(CC) $(CFLAGS) instructions/singleDataTransfer/singleDataTransfer.c -c -o singleDataTransfer.o
	
dataProcessing.o: instructions/dataProcessing/dataProcessing.c shifter/shifter.h instructions/instruction/instruction.h
	$(CC) $(CFLAGS) instructions/dataProcessing/dataProcessing.c -c -o dataProcessing.o
	
multiply.o: instructions/multiply/multiply.c 
	$(CC) $(CFLAGS) instructions/multiply/multiply.c -c -o multiply.o	
	
shifter.o: shifter/shifter.c 
	$(CC) $(CFLAGS) shifter/shifter.c -c -o shifter.o
	
instruction.o: instructions/instruction/instruction.c 
	$(CC) $(CFLAGS) instructions/instruction/instruction.c -c -o instruction.o
	
error.o: error/error.c 
	$(CC) $(CFLAGS) error/error.c -c -o error.o

clean:
	rm -f $(wildcard *.o)
	rm -f assemble
	rm -f emulate

.PHONY: clean
