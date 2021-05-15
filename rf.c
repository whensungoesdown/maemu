#include <stdio.h>
#include <string.h>
//#include <assert.h>
#include "defines.h"
#include "helper.h"

int rf_data[32] = {0};

int* g_rf_data = rf_data;

void
rf (
	__input char rs1_idx[5],
	__input char rs2_idx[5],
	__output char rs1_data[32],
	__output char rs2_data[32],

	__input char rd_wen,
	__input char rd_idx[5],
	__input char rd_data[32],

	__input char clk,
	__input char rst
   )
{
	int nRs1_idx = 0;
	int nRs2_idx = 0;
	int nRs1_data = 0;
	int nRs2_data = 0;

	int nRd_idx = 0;
	int nRd_data = 0;


	if (1 == rst)
	{
		memset(g_rf_data, 0, sizeof(int) * 32);
	}


	if (0 == clk) return; // only works at the rising edge

	charnbits2int(rs1_idx, &nRs1_idx, 5);
	//assert(nRs1_idx >= 0 && nRs1_idx <= 31);
	charnbits2int(rs2_idx, &nRs2_idx, 5);
	//assert(nRs2_idx >= 0 && nRs2_idx <= 31);

	PRINTF("rf rs1_idx 0x%x\n", nRs1_idx);
	PRINTF("rf rs2_idx 0x%x\n", nRs2_idx);


	if (0 == nRs1_idx)
	{
		nRs1_data = 0;
	}
	else
	{
		nRs1_data = g_rf_data[nRs1_idx];
	}


	if (0 == nRs2_idx)
	{
		nRs2_data = 0;
	}
	else
	{
		nRs2_data = g_rf_data[nRs2_idx];
	}

	int2char32bits(nRs1_data, rs1_data);
	int2char32bits(nRs2_data, rs2_data);
	PRINTF("rf rs1_data 0x%x\n", nRs1_data);
	PRINTF("rf rs2_data 0x%x\n", nRs2_data);



	charnbits2int(rd_idx, &nRd_idx, 5);
	//assert(nRd_idx >= 0 && nRd_idx <= 31);

	char32bits2int(rd_data, &nRd_data);

	if (0 == rd_wen)
	{
		// do nothing
	}
	else if (0 == rd_idx)
	{
		// do nothing
		PRINTF("rf write 0x%x to reg[0] !!!!\n", nRd_data);
	}
	else
	{
		g_rf_data[nRd_idx] = nRd_data;
		PRINTF("rf write 0x%x to reg[%d]\n", nRd_data, nRd_idx);
	}


	return;
}



