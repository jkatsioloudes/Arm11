/*
 **
 ** Purpose: The three stage implementation of pipeline; fetch decoded execute
 **
 */

#include "pipeline.h"

/* The three-stage pipeline */
void pipeline(ARM11 *arm11) {

	/* Initially fetched and decoded are "uninitialised" to some unused value */
	uint32_t fetched = UNINITIALISED;
	instruction *decodedInstruction = NULL;

	//Keep filling the pipeline
	for (;;) {
		if (decodedInstruction != NULL) {
			if (decodedInstruction->id == HALT) {
				execute(decodedInstruction, arm11);
				free(decodedInstruction);
				break;
			}
			// Execute a decoded instruction
			bool isExecuted = execute(decodedInstruction, arm11);
			free(decodedInstruction);

			if (getType(decodedInstruction->id) == BRANCH_INSTR && isExecuted) {
				decodedInstruction = NULL;
				fetched = UNINITIALISED;
			}
		}
		if (fetched != UNINITIALISED) {
			decodedInstruction = decode(fetched);
		}
		/* Fetch an instruction from memory */
		fetched = fetch(arm11);
	}
}

/* Fetches a 32-bit instruction from memory */
uint32_t fetch(ARM11 *arm11) {
	/* Since memory is stored as bytes; read 4 bytes*/
	uint32_t nextInstruction = readWord(arm11->memory + arm11->pc);
	arm11->pc += sizeof(uint32_t);
	return nextInstruction;
}

/* Decodes a 32-bit instruction */
instruction* decode(uint32_t fetched) {

	/* Allocate memory for each instruction but remember to call free()! */
	instruction *type = malloc(sizeof(instruction));
	checkAlloc(type, "Failed to allocate memory for instruction ",
			MEMORY_ALLOCATE_FAILURE);
	type->id = fetched;
	type->cond = getBits(fetched, COND_BIT_START, COND_BIT_END);

	switch (getType(fetched)) {
	case BRANCH_INSTR:
		type->offset = getBits(fetched, OFFSET_BIT_START_B, OFFSET_BIT_END_B);
		break;
	case MULTIPLY_INSTR:
		type->A = getBits(fetched, A_BIT, A_BIT);
		type->S = getBits(fetched, S_BIT, S_BIT);
		type->rd = getBits(fetched, RD_BIT_START_M, RD_BIT_END_M);
		type->rn = getBits(fetched, RN_BIT_START_M, RN_BIT_END_M);
		type->rs = getBits(fetched, RS_BIT_START_M, RS_BIT_END_M);
		type->rm = getBits(fetched, RM_BIT_START_M, RM_BIT_END_M);
		break;
	case DATA_PROCESSING_INSTR:
		type->I = getBits(fetched, I_BIT, I_BIT);
		type->S = getBits(fetched, S_BIT, S_BIT);
		type->opcode = getBits(fetched, OPCODE_BIT_START, OPCODE_BIT_END);
		type->rn = getBits(fetched, RN_BIT_START_DP, RN_BIT_END_DP);
		type->rd = getBits(fetched, RD_BIT_START_DP, RD_BIT_END_DP);
		type->operand2 = getBits(fetched, OPERAND2_BIT_START, OPERAND2_BIT_END);
		break;
	case SINGLE_DATA_TRANSFER_INSTR:
		type->I = getBits(fetched, I_BIT, I_BIT);
		type->P = getBits(fetched, P_BIT, P_BIT);
		type->U = getBits(fetched, U_BIT, U_BIT);
		type->L = getBits(fetched, L_BIT, L_BIT);
		type->rn = getBits(fetched, RN_BIT_START_SDT, RN_BIT_END_SDT);
		type->rd = getBits(fetched, RD_BIT_START_SDT, RD_BIT_END_SDT);
		type->offset = getBits(fetched, OFFSET_BIT_START_SDT, OFFSET_BIT_END_SDT);
		break;
	default: //This case is never reached though; ensured by getType()
		type->id = 0;
	}
	return type;
}

/* Executes an instruction */
bool execute(instruction *decoded, ARM11 *arm11) {
	uint32_t condition = decoded->cond;

	if (checkCondition(condition, arm11)) {
		instructionType type = getType(decoded->id);
		switch (type) {
		case BRANCH_INSTR:
			branch(decoded, arm11);
			break;
		case MULTIPLY_INSTR:
			multiply(decoded, arm11);
			break;
		case DATA_PROCESSING_INSTR:
			dataProcessing(decoded, arm11);
			break;
		case SINGLE_DATA_TRANSFER_INSTR:
			singleDataTransfer(decoded, arm11);
			break;
		default:
			fprintf(stderr,
					"Unknown condition code 0x%08X\nNot executing instruction\n",
					decoded->cond);
			return false;
		}
		return true;
	}
	return false;
}

/* Checks the condition */
bool checkCondition(uint32_t cond, ARM11 *arm11) {
	condition condition = cond;
	switch (condition) {
	case EQUAL:
		return eq(arm11);
	case NOT_EQUAL:
		return ne(arm11);
	case GREATER_OR_EQUAL:
		return ge(arm11);
	case LESS_THAN:
		return lt(arm11);
	case GREATER_THAN:
		return gt(arm11);
	case LESS_THAN_OR_EQUAL:
		return le(arm11);
	case ALWAYS:
		return al(arm11);
	default:
		fprintf(stderr, "Unknown condition 0x%08X\n", cond);
		return false;
	}
}
