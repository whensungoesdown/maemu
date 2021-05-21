#include <stdio.h>
#include "defines.h"
#include "helper.h"
#include "decode.h"

void
ifu (
	char clk,
	char rst,
	char read_addr[32],
	char read_data[32],
	char write_addr[32],
	char write_data[32],
	char pc[32],
	char instr[32] 
	)
{
	int nPc = 0;
	int nInstr = 0;


	if (0 == clk) return;

	PRINTF("ifu\n");

	char32bits2int(pc, &nPc);
	char32bits2int(instr, &nInstr);

	PRINTF("ifu: pc    0x%x\n", nPc);
	PRINTF("ifu: instr 0x%x\n", nInstr);

	decode(instr);

	return;
}

