#include <stdio.h>
#include "defines.h"
#include "helper.h"
#include "decode.h"

void
exu (
	__in char clk,
	__in char rst,
	__in char instr0[32]
    )
{
	int nInstr0 = 0;

	if (0 == clk) return;

	char32bits2int(instr0, &nInstr0);
	PRINTF("exu: instr0 0x%x\n", nInstr0);
	
	decode(instr0);

	return;
}
