#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "../../shifter/shifter.h"
#include "../../bitManipulation/bitManipulation.h"

/* The instruction struct */
/* DO NOT CHANGE THESE BIT FIELDS! */
typedef struct {
  reg32 rn;              /* Register n (Source register) */
  reg32 rd;              /* Register d (Destination register) */
  reg32 rs;              /* Rs */
  reg32 rm;              /* Rm */
  flag I :1;             /* Immediate flag*/
  flag P :1;             /* Pre/Post indexing flag */
  flag U :1;             /* Up flag */
  flag L :1;             /* Load/Store flag */
  flag S :1;             /* Set-condition flag */
  flag A :1;             /* Accumulate flag */
  uint32_t cond :4;      /* 4-bit condition code */
  uint32_t opcode :4;    /* 4-bit opcode */
  uint32_t operand2 :12; /* 12-bit operand for operation*/
  /* CHANGED FROM UINT32_T to INT32_T */
  int32_t offset :24;   /* Offset 24-bits*/
  uint32_t id;           /* The integer representation of the instruction */
} instruction;

/* Here lies the strange bug; we can't remove INSTR without some error! */
typedef enum {
  DATA_PROCESSING_INSTR,
  MULTIPLY_INSTR,
  SINGLE_DATA_TRANSFER_INSTR,
  BRANCH_INSTR
} instructionType;

/* Returns the type of an instruction */
instructionType getType(uint32_t instructionWord);

/* Flags of the CPSR register */
#define N_BIT 31 /* Negative flag */
#define Z_BIT 30 /* Zero flag */
#define C_BIT 29 /* Carry flag */
#define V_BIT 28 /* Overflow flag */

/*Rn AND operand2*/
uint32_t and(instruction *instr, ARM11 *arm11);

/*Rn EOR operand2*/
uint32_t eor(instruction *instr, ARM11 *arm11);

/*Rn SUB operand2*/
uint32_t sub(instruction *instr, ARM11 *arm11);

/*operand2 - Rn*/
uint32_t rsb(instruction *instr, ARM11 *arm11);

/*Rn + operand2*/
uint32_t add(instruction *instr, ARM11 *arm11);

/*Same as and() but result not written*/
void tst(instruction *instr, ARM11 *arm11);

/*Same as eor() but result not written*/
void teq(instruction *instr, ARM11 *arm11);

/*Same as sub() but result not written*/
void cmp(instruction *instr, ARM11 *arm11);

/*Rn OR operand2*/
uint32_t orr(instruction *instr, ARM11 *arm11);

/*mov Rd,operand2 */
uint32_t mov(instruction *instr, ARM11 *arm11);

#endif
