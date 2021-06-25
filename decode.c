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
	__out char simm[32],

	__out char need_rs[1],
	__out char need_rob[1],
	__out char regwrite[1]
       )
{

	//
	// 32 0s is treated as a pipeline bubble
	
	char BUBBLE[32] = {0};

	char ADDI_W[10] = {0, 1, 0, 1, 0, 0, 0, 0, 0, 0};
	char ADD_W[17]  = {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


	int nSimm = 0;
	int nRjIdx = 0;
	int nRkIdx = 0;
	int nRdIdx = 0;


	if (0 == memcmp(instr, BUBBLE, 32))
	{
		PRINTF(ID_PREFIX"  decode: pipeline BUBBLE\n");

		need_rs[0] = 0;
		need_rob[0] = 0;
		regwrite[0] = 0;
	}
	else if (0 == memcmp(instr + 22, ADDI_W, 10))
	{
		memset(simm, 0, 32);
		memcpy(simm, instr + 10, 12);
		memcpy(rj_idx, instr + 5, 5);
		memcpy(rd_idx, instr + 0, 5); // uty: bug   instr + 10 works, instr + 9 no


		charnbits2int(simm, &nSimm, 12); // todo: need to handle sign
		charnbits2int(rj_idx, &nRjIdx, 5);
		charnbits2int(rd_idx, &nRdIdx, 5);

		PRINTF(ID_PREFIX"  decode: ADDI.W $%d, $%d, %d\n", nRdIdx, nRjIdx, nSimm);
		need_rs[0] = 1;
		need_rob[0] = 1;
		regwrite[0] = 1;
	}
	else if (0 == memcmp(instr + 15, ADD_W, 17))
	{
		memcpy(rd_idx, instr + 0, 5);
		memcpy(rj_idx, instr + 5, 5);
		memcpy(rk_idx, instr + 10, 5);	

		charnbits2int(rd_idx, &nRdIdx, 5);
		charnbits2int(rj_idx, &nRjIdx, 5);
		charnbits2int(rk_idx, &nRkIdx, 5);

		PRINTF(ID_PREFIX"  decode: ADD.W $%d, $%d, $%d\n", nRdIdx, nRjIdx, nRkIdx);

		need_rs[0] = 1;
		need_rob[0] = 1;
		regwrite[0] = 1;
	}
	else
	{
		printf(ID_PREFIX"!!!!!!!!!!! Invalid instruction\n");
	}

	return;
}
