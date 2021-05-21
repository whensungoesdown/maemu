#include <stdio.h>
#include "defines.h"
#include "helper.h"
#include "decode.h"
#include "adder.h"

void
ifu (
	__in  char clk,
	__in  char rst,
	__out char read_addr[32],
	__in  char read_data[32],
	__out char write_addr[32],
	__out char write_data[32],
	__in  char pc_current[32],
	__out char pc_next[32],
	__out char pc_next_ena[1],
	__in  char instr[32] 
	)
{
	int nPcCurrent = 0;
	int nInstr = 0;

	char Imm_4[32] = {0, 0, 1, 0};


	if (0 == clk) return;

	PRINTF("ifu\n");

	char32bits2int(pc_current, &nPcCurrent);
	char32bits2int(instr, &nInstr);

	PRINTF("ifu: pc_current 0x%x\n", nPcCurrent);
	PRINTF("ifu: instr 0x%x\n", nInstr);

	decode(instr);

	adder(pc_current, Imm_4, pc_next);
	pc_next_ena[0] = 1;

	print_char32bits(pc_next);

	return;
}

