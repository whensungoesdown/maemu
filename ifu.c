#include <stdio.h>
#include "helper.h"

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


	PRINTF("ifu\n");

	char32bits2int(pc, &nPc);
	char32bits2int(instr, &nInstr);

	PRINTF("ifu: pc    0x%x\n", nPc);
	PRINTF("ifu: instr 0x%x\n", nInstr);

	return;
}

