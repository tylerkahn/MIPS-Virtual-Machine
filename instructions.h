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
		case 0x3:
			return &jal;
		case 0x2:
			return &j;
		default:
			fprintf(stderr, "Got invalid opcode value in j instruction: %d\n", opcode);
			exit(-1);
	}
}
static inline void (*get_r_instruction(uint32_t opcode)) (instruction_t, proc_t *) {
	switch (opcode) {
		case 0x20:
			return &add;
		case 0x22:
			return &sub;
		case 0x25:
			return &or;
		case 0x24:
			return &and;
		case 0x2a:
			return &slt;
		case 0x0:
			return &sll;
		case 0x2:
			return &srl;
		case 0x8:
			return &jr;
		default:
			fprintf(stderr, "Got invalid opcode value in r instruction: %d\n", opcode);
			exit(-1);

	}
}

static inline void (*get_i_instruction(uint32_t function)) (instruction_t, proc_t *) {
	switch (function) {
		case 0x23:
			return &lw;
		case 0x2b:
			return &sw;
		case 0x8:
			return &addi;
		case 0xd:
			return &ori;
		case 0xc:
			return &andi;
		case 0xa:
			return &slti;
		case 0x4:
			return &beq;
		case 0x5:
			return &bne;
		case 0xf:
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
