#ifndef _MAIN_H
#define _MAIN_H

#include "mtypes.h"

static inline uint32_t atoi_binary(char *bs) {
	uint32_t sum = 0;
	for (;*bs != '\0'; bs++)
		sum = (sum << 1) + (*bs == '1' ? 1 : 0);
	return sum;
};
void load_program(int fd, proc_t *p);

void print_machine(proc_t *p);

#endif
