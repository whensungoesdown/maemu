#include <stdio.h>
#include <string.h>
#include "defines.h"
#include "helper.h"

void
decode (
	__in char instr[32]
       )
{

	char ADDI_W[10] = {0, 1, 0, 1, 0, 0, 0, 0, 0, 0};

	char si12[12] = {0};
	char rj[5] = {0};
	//char rk[5] = {0};
	char rd[5] = {0};

	int nSi12 = 0;
	int nRj = 0;
	//int nRk = 0;
	int nRd = 0;


	if (0 == memcmp(instr + 22, ADDI_W, 10))
	{
		memcpy(si12, instr + 10, 12);
		memcpy(rj, instr + 5, 5);
		memcpy(rd, instr + 0, 5); // uty: bug   instr + 10 works, instr + 9 no


		charnbits2int(si12, &nSi12, 12); // todo: need to handle sign
		charnbits2int(rj, &nRj, 5);
		charnbits2int(rd, &nRd, 5);

		PRINTF("ADDI.W $%d, $%d, %d\n", nRd, nRj, nSi12);
	}
	else
	{
		printf("!!!!!!!!!!! Invalid instruction\n");
	}

	return;
}
