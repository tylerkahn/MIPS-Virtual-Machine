#ifndef _MTYPES_H
#define _MTYPES_H

#include <stdint.h>

#define MEGABYTE (1024 * 1024)
#define MEM_SIZE (4 * MEGABYTE)
#define TEXT_SIZE 0x2000
#define DATA_SIZE (MEM_SIZE - TEXT_SIZE)

typedef struct {
	union {
		uint32_t data; // getter/setter and to ensure alignment
		struct { // R Type
			uint32_t function : 6;
			uint32_t sa : 5;
			uint32_t rd : 5;
			uint32_t rt : 5;
			uint32_t rs : 5;
			uint32_t opcode : 6;
		};
		struct { // I Type
			union {
				int32_t s_immediate : 16; // sign extended
				uint32_t z_immediate : 16;// zero extended
			};
			uint32_t rt : 5;
			uint32_t rs : 5;
			uint32_t opcode : 6;
		};
		struct { // J Type
			uint32_t instr_index : 26;
			uint32_t opcode : 6;
		};
	};
} instruction_t;

typedef struct {
	union {
		uint8_t mem[MEM_SIZE];
		uint32_t mem_32[MEM_SIZE/4];
		struct {
			uint8_t text_8[TEXT_SIZE];
			uint8_t data_8[DATA_SIZE];
		};
		struct {
			uint32_t text_32[TEXT_SIZE/4];
			uint32_t data_32[DATA_SIZE/4];
		};
	};
	union {
		uint32_t GPR[32];
		struct {
			uint32_t __nothing__[28];
			uint32_t gp;
			uint32_t sp;
			uint32_t fp;
			uint32_t ra;
		};
	};
	uint32_t pc;

} proc_t;

#endif
