#include <stdio.h>
#include "defines.h"
#include "helper.h"
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
	__out char pc_next_ena[1]
	)
{
	int nPcCurrent = 0;

	char Imm_4[32] = {0, 0, 1, 0};


	if (0 == clk) return;


	char32bits2int(pc_current, &nPcCurrent);
	PRINTF("ifu: pc_current 0x%x\n", nPcCurrent);


	adder(pc_current, Imm_4, pc_next);
	pc_next_ena[0] = 1;


	return;
}

