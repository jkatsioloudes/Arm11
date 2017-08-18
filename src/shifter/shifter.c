/*
 *
 * Purpose: Shifter function implementations
 *
 */

#include "shifter.h"

/* Performs left shift on number by specified amount */

uint32_t logLeftShift(uint32_t num, uint32_t shift, bool setFlags, ARM11 *arm11) {
	if (setFlags) {
		uint32_t discardedBit = (
				(shift == 0) ? 0 : getBits(num, NUM_BITS - shift, NUM_BITS - shift));
		arm11->cpsr->C = discardedBit;
	}
	return num << shift;
}

/* Performs right shift on number by specified amount */

uint32_t logRightShift(uint32_t num, uint32_t shift, bool setFlags,
		ARM11 *arm11) {
	if (setFlags) {
		uint32_t discardedBit = (
				(shift == 0) ? 0 : getBits(num, (shift - 1), (shift - 1)));
		arm11->cpsr->C = discardedBit;
	}
	return num >> shift;
}

/* Performs right shift on number by specified amount,
 * preserves signs */

uint32_t arithRightShift(int32_t num, uint32_t shift, bool setFlags,
		ARM11 *arm11) {
	if (setFlags) {
		uint32_t discardedBit = (
				(shift == 0) ? 0 : getBits(num, (shift - 1), (shift - 1)));
		arm11->cpsr->C = discardedBit;
	}
	return num >> shift;
}

/* Performs right shift on number by specified amount,
 * least significant bits rotated round to most significant positions*/

uint32_t rotRight(uint32_t num, uint32_t shift, bool setFlags, ARM11 *arm11) {
	if (setFlags) {
		uint32_t discardedBit = (
				(shift == 0) ? 0 : getBits(num, (shift - 1), (shift - 1)));
		arm11->cpsr->C = discardedBit;
	}
	if (shift == 0) {
		return num;
	}
	uint32_t endBits = getBits(num, FIRST_BIT, shift - 1);
	endBits <<= (NUM_BITS - shift);
	return endBits | (logRightShift(num, shift, setFlags, arm11));
}

/* Shifts, treating operand2 as register */

uint32_t shifterReg(uint32_t operand2, ARM11 *arm11, bool setFlags) {
	reg32 reg = getBits(operand2, FIRST_BIT, LAST_BIT_SOURCE_REG);
	if (getBits(operand2, SHIFT_AMT_FORM, SHIFT_AMT_FORM) == 0) {
		uint32_t shiftAmount = getBits(operand2, SHIFT_AMT_START, SHIFT_AMT_END);
		uint32_t shiftType = getBits(operand2, SHIFT_TYPE_START, SHIFT_TYPE_END);
		switch (shiftType) {
		case LSL:
			return logLeftShift(arm11->gpr[reg], shiftAmount, setFlags, arm11);
		case LSR:
			return logRightShift(arm11->gpr[reg], shiftAmount, setFlags, arm11);
		case ASR:
			return arithRightShift(arm11->gpr[reg], shiftAmount, setFlags, arm11);
		case ROR:
			return rotRight(arm11->gpr[reg], shiftAmount, setFlags, arm11);
		default:
			return operand2;
		}
	} else {
		uint32_t shiftAmount = getBits(
				arm11->gpr[getBits(operand2, SHIFT_REG_START, SHIFT_REG_END)],
				FIRST_BIT, BYTE_END);
		uint32_t shiftType = getBits(operand2, SHIFT_TYPE_START, SHIFT_TYPE_END);
		switch (shiftType) {
		case LSL:
			return logLeftShift(arm11->gpr[reg], shiftAmount, setFlags, arm11);
		case LSR:
			return logRightShift(arm11->gpr[reg], shiftAmount, setFlags, arm11);
		case ASR:
			return arithRightShift(arm11->gpr[reg], shiftAmount, setFlags, arm11);
		case ROR:
			return rotRight(arm11->gpr[reg], shiftAmount, setFlags, arm11);
		default:
			return operand2;
		}
	}
	return operand2;
}

/* Shifts, treating operand2 as immediate constant */

uint32_t shifterImm(uint32_t operand2, ARM11 *arm11, bool setFlags) {
	uint32_t val = getBits(operand2, FIRST_BIT, BYTE_END);
	uint32_t rotAmount = getBits(operand2, ROT_AMT_START, ROT_AMT_END);
	return rotRight(val, 2 * rotAmount, setFlags, arm11);
}

/* Performs left shift on number by specified amount and preserves the sign */
int32_t arithLeftShift(int32_t num, uint32_t shift) {
	return num << shift;
}

uint8_t asmRotateLeft(uint32_t number, uint8_t shift) {
  uint32_t endBits = getBits(number, NUM_BITS-shift, NUM_BITS-1);
  return endBits | (number << shift);
}

uint32_t asmRotateRight(uint32_t number, uint8_t shift) {
  uint32_t endBits = getBits(number, FIRST_BIT, shift-1);
  endBits <<= (NUM_BITS - shift);
  return endBits | (number >> shift);
}

uint32_t rotateLeft(uint32_t number)	{
	uint32_t lastBit = getBits(number,31,31);
	number <<= 1;
	number |= lastBit;
	return number;
}


