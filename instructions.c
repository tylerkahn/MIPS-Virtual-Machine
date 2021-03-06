#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "mtypes.h"
#include "instructions.h"

void add(instruction_t i, proc_t *p) {
#ifdef DEBUG
	printf("add $%d $%d $%d", i.rd, i.rs, i.rt);
#endif
	p->GPR[i.rd] = p->GPR[i.rs] + p->GPR[i.rt];
}

void sub(instruction_t i, proc_t *p) {
#ifdef DEBUG
	printf("sub $%d $%d $%d", i.rd, i.rs, i.rt);
#endif
	p->GPR[i.rd] = p->GPR[i.rs] - p->GPR[i.rt];
}

void or(instruction_t i, proc_t *p) {
#ifdef DEBUG
	printf("or $%d $%d $%d", i.rd, i.rs, i.rt);
#endif
	p->GPR[i.rd] = p->GPR[i.rs] | p->GPR[i.rt];
}

void and(instruction_t i, proc_t *p) {
#ifdef DEBUG
	printf("and $%d $%d $%d", i.rd, i.rs, i.rt);
#endif
	p->GPR[i.rd] = p->GPR[i.rs] & p->GPR[i.rt];
}

void slt(instruction_t i, proc_t *p) {
#ifdef DEBUG
	printf("slt $%d $%d $%d", i.rd, i.rs, i.rt);
#endif
	p->GPR[i.rd] = (p->GPR[i.rs] < p->GPR[i.rt]);
}

void sll(instruction_t i, proc_t *p) {
#ifdef DEBUG
	printf("sll $%d $%d %d", i.rd, i.rt, i.sa);
#endif
	p->GPR[i.rd] = p->GPR[i.rt] << i.sa;
}

void srl(instruction_t i, proc_t *p) {
#ifdef DEBUG
	printf("srl $%d $%d %d", i.rd, i.rt, i.sa);
#endif
	p->GPR[i.rd] = p->GPR[i.rt] >> i.sa;
}

void jr(instruction_t i, proc_t *p) {
#ifdef DEBUG
	printf("jr $%d", i.rs);
#endif
	p->pc = p->GPR[i.rs] - 4;
}


void lw(instruction_t i, proc_t *p) {
#ifdef DEBUG
	printf("lw $%d 0x%X($%d)", i.rt, i.s_immediate, i.rs);
#endif
	p->GPR[i.rt] = p->mem_32[(p->GPR[i.rs] + i.s_immediate)/4];
}

void sw(instruction_t i, proc_t *p) {
#ifdef DEBUG
	printf("sw $%d 0x%X($%d)", i.rt, i.s_immediate, i.rs);
#endif
	p->mem_32[(p->GPR[i.rs] + i.s_immediate)/4] = p->GPR[i.rt];
}

void addi(instruction_t i, proc_t *p) {
#ifdef DEBUG
	printf("addi $%d $%d 0x%X", i.rt, i.rs, i.s_immediate);
#endif
	p->GPR[i.rt] = p->GPR[i.rs] + i.s_immediate;
}

void ori(instruction_t i, proc_t *p) {
#ifdef DEBUG
	printf("ori $%d $%d 0x%X", i.rt, i.rs, i.z_immediate);
#endif
	p->GPR[i.rt] = p->GPR[i.rs] | i.z_immediate;
}

void andi(instruction_t i, proc_t *p) {
#ifdef DEBUG
	printf("andi $%d $%d 0x%X", i.rt, i.rs, i.s_immediate);
#endif
p->GPR[i.rt] = p->GPR[i.rs] & i.s_immediate;
}


void slti(instruction_t i, proc_t *p) {
#ifdef DEBUG
	printf("slti $%d $%d 0x%X", i.rt, i.rs, i.s_immediate);
#endif
p->GPR[i.rt] = (p->GPR[i.rs] < i.s_immediate);
}

void beq(instruction_t i, proc_t *p) {
#ifdef DEBUG
	printf("beq $%d $%d 0x%X", i.rt, i.rs, i.s_immediate);
#endif
if (p->GPR[i.rs] == p->GPR[i.rt]) {
		p->pc = p->pc + (i.s_immediate << 2);
	}
}

void bne(instruction_t i, proc_t *p) {
#ifdef DEBUG
	printf("bne $%d $%d 0x%X", i.rt, i.rs, i.s_immediate);
#endif
if (p->GPR[i.rs] != p->GPR[i.rt]) {
		p->pc = p->pc + (i.s_immediate << 2);
	}
}

void lui(instruction_t i, proc_t *p) {
#ifdef DEBUG
	printf("lui $%d 0x%X", i.rt, i.z_immediate);
#endif
	p->GPR[i.rt] = (i.z_immediate << 16);
}

void j(instruction_t i, proc_t *p) {
#ifdef DEBUG
	printf("j 0x%X", i.instr_index);
#endif
	p->pc = ((p->pc >> 28) | (i.instr_index << 2)) - 4;
}

void jal(instruction_t i, proc_t *p) {
#ifdef DEBUG
	printf("jal 0x%X", i.instr_index);
#endif
	p->GPR[31] = p->pc + 4;
	p->pc = ((p->pc >> 28) | (i.instr_index << 2)) - 4;
}
