#ifndef SHIFTER_H
#define SHIFTER_H

#include <stdbool.h>
#include "../processor/processor.h"
#include "../bitManipulation/bitManipulation.h"

#define NUM_BITS 32 /* number of bits in an unsigned int */
#define FIRST_BIT 0 /* first bit of unsigned int */
#define BYTE_END 7 /* last bit of the first byte */

//operand2 shifter fields

#define LAST_BIT_SOURCE_REG 3 /* the last bit of the field containing the source register */
#define SHIFT_AMT_FORM 4 /* bit that describes the format of the shift amount */
#define SHIFT_AMT_START 7 /* first bit describing shift amount */
#define SHIFT_AMT_END 11 /* last bit describing shift amount */
#define SHIFT_TYPE_START 5 /* first bit describing shift type */
#define SHIFT_TYPE_END 6 /* last bit describing shift type */
#define SHIFT_REG_START 8 /* first bit describing shift register */
#define SHIFT_REG_END 11 /* last bit describing shift register */
#define ROT_AMT_START 8 /* first bit describing rotation amount */
#define ROT_AMT_END 11 /* last bit describing rotation amount */

// Shift cases
typedef enum {
	LSL = 0, LSR = 1, ASR = 2, ROR = 3
} shift_type;

/* Shifter signartures */

uint32_t logLeftShift(uint32_t num, uint32_t shift, bool setFlags, ARM11 *arm11);

uint32_t logRightShift(uint32_t num, uint32_t shift, bool setFlags,
		ARM11 *arm11);

uint32_t arithRightShift(int32_t num, uint32_t shift, bool setFlags,
		ARM11 *arm11);

int32_t arithLeftShift(int32_t num, uint32_t shift);

uint32_t rotRight(uint32_t num, uint32_t shift, bool setFlags, ARM11 *arm11);

uint32_t shifterReg(uint32_t operand2, ARM11 *arm11, bool setFlags);

uint32_t shifterImm(uint32_t operand2, ARM11 *arm11, bool setFlags);

uint32_t rotateLeft(uint32_t number);

uint8_t asmRotateLeft(uint32_t number, uint8_t shift);

uint32_t asmRotateRight(uint32_t number, uint8_t shift);

#endif
