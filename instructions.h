#ifndef _INSTRUCTIONS_H
#define _INSTRUCTIONS_H

#include "mtypes.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// I Type
void lw(instruction_t i, proc_t *p);
void sw(instruction_t i, proc_t *p);
void addi(instruction_t i, proc_t *p);
void ori(instruction_t i, proc_t *p);
void andi(instruction_t i, proc_t *p);
void slti(instruction_t i, proc_t *p);
void beq(instruction_t i, proc_t *p);
void bne(instruction_t i, proc_t *p);
void lui(instruction_t i, proc_t *p);

// R Type
void add(instruction_t i, proc_t *p);
void sub(instruction_t i, proc_t *p);
void or(instruction_t i, proc_t *p);
void and(instruction_t i, proc_t *p);
void slt(instruction_t i, proc_t *p);
void sll(instruction_t i, proc_t *p);
void srl(instruction_t i, proc_t *p);
void jr(instruction_t i, proc_t *p);

// J Type
void j(instruction_t i, proc_t *p);
void jal(instruction_t i, proc_t *p);

static inline void (*get_j_instruction(uint32_t opcode)) (instruction_t, proc_t *) {
	switch (opcode) {
		case 0b000011:
			return &jal;
		case 0b000010:
			return &j;
		default:
			fprintf(stderr, "Got invalid opcode value in j instruction: %d\n", opcode);
			exit(-1);
	}
}
static inline void (*get_r_instruction(uint32_t opcode)) (instruction_t, proc_t *) {
	switch (opcode) {
		case 0b100000:
			return &add;
		case 0b100010:
			return &sub;
		case 0b100101:
			return &or;
		case 0b100100:
			return &and;
		case 0b101010:
			return &slt;
		case 0b000000:
			return &sll;
		case 0b000010:
			return &srl;
		case 0b001000:
			return &jr;
		default:
			fprintf(stderr, "Got invalid opcode value in r instruction: %d\n", opcode);
			exit(-1);

	}
}

static inline void (*get_i_instruction(uint32_t function)) (instruction_t, proc_t *) {
	switch (function) {
		case 0b100011:
			return &lw;
		case 0b101011:
			return &sw;
		case 0b001000:
			return &addi;
		case 0b001101:
			return &ori;
		case 0b001100:
			return &andi;
		case 0b001010:
			return &slti;
		case 0b000100:
			return &beq;
		case 0b000101:
			return &bne;
		case 0b001111:
			return &lui;
		default:
			fprintf(stderr, "Got invalid function value in i instruction: %d\n", function);
			exit(-1);
	}
}

static inline void (*get_instruction(instruction_t i)) (instruction_t, proc_t *) {
	switch (i.opcode) {
			case 0:
				return get_r_instruction(i.function);
			case 2:
			case 3:
				return get_j_instruction(i.opcode);
			default:
				return get_i_instruction(i.opcode);
	}

}
#endif
