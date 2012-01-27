#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#include "mtypes.h"
#include "instructions.h"
#include "main.h"

void load_program(int fd, proc_t *p) {
	char *f;
	ssize_t fsize;

	fsize = lseek(fd, 0, SEEK_END);
	f = mmap(0, fsize, PROT_READ, MAP_SHARED, fd, 0);

	for (int i = 0; *f != '\n'; f += 33, i++) {
		char n[33];
		memcpy(n, f, 32);
		n[32] = 0;
		p->text_32[i] = atoi_binary(n);
	}

	f++;

	for (int i = 0; *f != '\0'; f += 33, i++) {
		char n[33];
		memcpy(n, f, 32);
		n[32] = 0;
		p->data_32[i] = atoi_binary(n);
	}
}
void print_machine(proc_t *p) {
	int i = 0;
	printf("%d.\t%s\t  0x%08x\n", i+1, "$zero", p->GPR[i]); i++;
	printf("%d.\t%s\t  0x%08x\n", i+1, "$at", p->GPR[i]); i++;
	printf("%d.\t%s\t  0x%08x\n", i+1, "$v0", p->GPR[i]); i++;
	printf("%d.\t%s\t  0x%08x\n", i+1, "$v1", p->GPR[i]); i++;
	printf("%d.\t%s\t  0x%08x\n", i+1, "$a0", p->GPR[i]); i++;
	printf("%d.\t%s\t  0x%08x\n", i+1, "$a1", p->GPR[i]); i++;
	printf("%d.\t%s\t  0x%08x\n", i+1, "$a2", p->GPR[i]); i++;
	printf("%d.\t%s\t  0x%08x\n", i+1, "$a3", p->GPR[i]); i++;
	printf("%d.\t%s\t  0x%08x\n", i+1, "$t0", p->GPR[i]); i++;
	printf("%d.\t%s\t  0x%08x\n", i+1, "$t1", p->GPR[i]); i++;
	printf("%d.\t%s\t  0x%08x\n", i+1, "$t2", p->GPR[i]); i++;
	printf("%d.\t%s\t  0x%08x\n", i+1, "$t3", p->GPR[i]); i++;
	printf("%d.\t%s\t  0x%08x\n", i+1, "$t4", p->GPR[i]); i++;
	printf("%d.\t%s\t  0x%08x\n", i+1, "$t5", p->GPR[i]); i++;
	printf("%d.\t%s\t  0x%08x\n", i+1, "$t6", p->GPR[i]); i++;
	printf("%d.\t%s\t  0x%08x\n", i+1, "$t7", p->GPR[i]); i++;
	printf("%d.\t%s\t  0x%08x\n", i+1, "$s0", p->GPR[i]); i++;
	printf("%d.\t%s\t  0x%08x\n", i+1, "$s1", p->GPR[i]); i++;
	printf("%d.\t%s\t  0x%08x\n", i+1, "$s2", p->GPR[i]); i++;
	printf("%d.\t%s\t  0x%08x\n", i+1, "$s3", p->GPR[i]); i++;
	printf("%d.\t%s\t  0x%08x\n", i+1, "$s4", p->GPR[i]); i++;
	printf("%d.\t%s\t  0x%08x\n", i+1, "$s5", p->GPR[i]); i++;
	printf("%d.\t%s\t  0x%08x\n", i+1, "$s6", p->GPR[i]); i++;
	printf("%d.\t%s\t  0x%08x\n", i+1, "$s7", p->GPR[i]); i++;
	printf("%d.\t%s\t  0x%08x\n", i+1, "$t8", p->GPR[i]); i++;
	printf("%d.\t%s\t  0x%08x\n", i+1, "$t9", p->GPR[i]); i++;
	printf("%d.\t%s\t  0x%08x\n", i+1, "$k0", p->GPR[i]); i++;
	printf("%d.\t%s\t  0x%08x\n", i+1, "$k1", p->GPR[i]); i++;

	printf("%d.\t%s\t  0x%08x\n", i+1, "pc", p->pc);
}
int main(int argc, char *argv[]) {
	int input;
	proc_t p;

	input = open(argv[1], O_RDONLY);
	memset(&p, 0, sizeof(proc_t));

	load_program(input, &p);

	for (p.pc = 0; p.pc < MEM_SIZE; p.pc += 4) {
		instruction_t i;
		i.data = p.mem_32[p.pc/4];

		if (i.data == 0) {
			p.pc += 4;
			print_machine(&p);
			return 0;
		}
		void (*op)(instruction_t, proc_t*) = get_instruction(i);
		op(i, &p);
	}

	return 0;
}


