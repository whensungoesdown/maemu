#include <stdio.h>
#include <string.h>
#include "defines.h"
#include "helper.h"

void
decode (
	__in  char instr[32],
	__out char rj_idx[5],
	__out char rk_idx[5],
	__out char rd_idx[5],
	__out char simm[32]
       )
{

	char ADDI_W[10] = {0, 1, 0, 1, 0, 0, 0, 0, 0, 0};


	int nSimm = 0;
	int nRjIdx = 0;
	int nRkIdx = 0;
	int nRdIdx = 0;


	if (0 == memcmp(instr + 22, ADDI_W, 10))
	{
		memset(simm, 0, 32);
		memcpy(simm, instr + 10, 12);
		memcpy(rj_idx, instr + 5, 5);
		memcpy(rd_idx, instr + 0, 5); // uty: bug   instr + 10 works, instr + 9 no


		charnbits2int(simm, &nSimm, 12); // todo: need to handle sign
		charnbits2int(rj_idx, &nRjIdx, 5);
		charnbits2int(rd_idx, &nRdIdx, 5);

		PRINTF("ADDI.W $%d, $%d, %d\n", nRdIdx, nRjIdx, nSimm);
	}
	else
	{
		printf("!!!!!!!!!!! Invalid instruction\n");
	}

	return;
}
