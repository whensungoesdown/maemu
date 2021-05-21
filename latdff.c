#include <stdio.h>
#include "defines.h"
#include "helper.h"

//
// all the latch and dff go here
//

void
pc_lat (
	__in  char pc_ena[1],
	__in  char pc_next[32],
	__out char q[32]
       )
{
	static char pc_reg[32] = {0};
	int nPcNext = 0;
	int nPcReg = 0;

	if (1 == pc_ena[0])
	{
		char32bits2int(pc_next, &nPcNext);
		int2char32bits(nPcNext, pc_reg);
	}

	char32bits2int(pc_reg, &nPcReg);
	int2char32bits(nPcReg, q);

	PRINTF("pc_lat: pc_reg 0x%x\n", nPcReg);
}

