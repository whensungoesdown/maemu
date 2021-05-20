#include <stdio.h>
#include <string.h>
//#include <assert.h>
#include "defines.h"
#include "helper.h"

int rf_data[32] = {0};    // data 32 bits
int rf_busy[32] = {0};    // busy 1 bit
int rf_reorder[32] = {0}; // reorder 3 bits

int* g_rf_data = rf_data;
int* g_rf_busy = rf_busy;
int* g_rf_reorder = rf_reorder; 

void
rf (
	__input char rs1_idx[5],
	__input char rs2_idx[5],
	__output char rs1_data[32],
	__output char rs2_data[32],
	__output char rs1_busy[1],
	__output char rs2_busy[1],
	__output char rs1_reorder[3],
	__output char rs2_reorder[3],

	__input char rd_wen,
	__input char rd_idx[5],
	__input char rd_data[32],
	__input char rd_busy[1],
	__input char rd_reorder[3],

	__input char clk,
	__input char rst
   )
{
	int nRs1_idx = 0;
	int nRs2_idx = 0;
	int nRs1_data = 0;
	int nRs2_data = 0;
	int nRs1_busy = 0;
	int nRs2_busy = 0;
	int nRs1_reorder = 0;
	int nRs2_reorder = 0;

	int nRd_idx = 0;
	int nRd_data = 0;
	int nRd_busy = 0;
	int nRd_reorder = 0;


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
		nRs1_busy = 0;
		nRs1_reorder = 0;
	}
	else
	{
		nRs1_data = g_rf_data[nRs1_idx];
		nRs1_busy = g_rf_busy[nRs1_idx];
		nRs1_reorder = g_rf_reorder[nRs1_idx];
	}


	if (0 == nRs2_idx)
	{
		nRs2_data = 0;
		nRs2_busy = 0;
		nRs2_reorder = 0;
	}
	else
	{
		nRs2_data = g_rf_data[nRs2_idx];
		nRs2_busy = g_rf_busy[nRs2_idx];
		nRs2_reorder = g_rf_reorder[nRs2_idx];
	}

	int2char32bits(nRs1_data, rs1_data);
	int2char32bits(nRs2_data, rs2_data);
	int2charnbits(nRs1_busy, rs1_busy, 1);
	int2charnbits(nRs2_busy, rs2_busy, 1);
	int2charnbits(nRs1_reorder, rs1_reorder, 3);
	int2charnbits(nRs2_reorder, rs2_reorder, 3);

	PRINTF("rf rs1_data 0x%x, busy %d, reorder %d\n", nRs1_data, nRs1_busy, nRs1_reorder);
	PRINTF("rf rs2_data 0x%x, busy %d, reorder %d\n", nRs2_data, nRs2_busy, nRs2_reorder);



	charnbits2int(rd_idx, &nRd_idx, 5);
	//assert(nRd_idx >= 0 && nRd_idx <= 31);

	char32bits2int(rd_data, &nRd_data);
	charnbits2int(rd_busy, &nRd_busy, 1);
	charnbits2int(rd_reorder, &nRd_reorder, 3);

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
		g_rf_busy[nRd_idx] = nRd_busy;
		g_rf_reorder[nRd_idx] = nRd_reorder;
		PRINTF("rf write 0x%x to reg[%d], busy %d, reorder %d\n", nRd_data, nRd_idx, nRd_busy, nRd_reorder);
	}


	return;
}



