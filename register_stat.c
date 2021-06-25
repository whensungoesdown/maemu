#include <stdio.h>
#include "defines.h"
#include "helper.h"


int regstat_busy[32] = {0}; // 1 bit
int regstat_reorder[32] = {0}; // 3 bits 

int* g_regstat_busy = regstat_busy;
int* g_regstat_reorder = regstat_reorder;

void
register_stat (
//	__in  char valid[1],
//	__out char ready[1],

	__in  char rj_idx[5],
	__in  char rk_idx[5],
	__out char rj_busy[1],
	__out char rk_busy[1],
	__out char rj_reorder[3],
	__out char rk_reorder[3],

	__in  char rd_wen[1],
	__in  char rd_idx[5],
	__in  char rd_busy[1],
	__in  char rd_reorder[3]
	)
{
	int nRjIdx = 0;
	int nRkIdx = 0;

	int nRjBusy = 0;
	int nRkBusy = 0;


	int nRjReorder = 0;
	int nRkReorder = 0;


	int nRdIdx = 0;
	int nRdBusy = 0;
	int nRdReorder = 0;


	charnbits2int(rj_idx, &nRjIdx, 5);
	charnbits2int(rk_idx, &nRkIdx, 5);



	charnbits2int(rd_idx, &nRdIdx, 5);
	charnbits2int(rd_busy, &nRdBusy, 1);
	charnbits2int(rd_reorder, &nRdReorder, 3);


	if (0 == nRjIdx)
	{
		nRjBusy = 0;
		nRjReorder = 0;
	}
	else
	{
		nRjBusy = g_regstat_busy[nRjIdx];
		nRjReorder = g_regstat_reorder[nRjIdx];
	}

	int2charnbits(nRjBusy, rj_busy, 1);
	int2charnbits(nRjReorder, rj_reorder, 3);

	if (0 == nRkIdx)
	{
		nRkBusy = 0;
		nRkReorder = 0;
	}
	else
	{
		nRkBusy = g_regstat_busy[nRkIdx];
		nRkReorder = g_regstat_reorder[nRkIdx];
	}

	int2charnbits(nRkBusy, rk_busy, 1);
	int2charnbits(nRkReorder, rk_reorder, 3);


	if (0 == rd_wen[0])
	{
		// do nothing
	}
	else if (0 == nRdIdx)
	{
		// do nothing
		printf("regstate: write regs[0]!!!!\n");
	}
	else
	{
		g_regstat_busy[nRdIdx] = nRdBusy;
		g_regstat_reorder[nRdIdx] = nRdReorder;
	}


	PRINTF(ID_PREFIX"  register_stat: rj %d, busy %d, reorder %d\n", nRjIdx, nRjBusy, nRjReorder);
	PRINTF(ID_PREFIX"  register_stat: rk %d, busy %d, reorder %d\n", nRkIdx, nRkBusy, nRkReorder);
	PRINTF(ID_PREFIX"  register_stat: rd %d, busy %d, reorder %d (new)\n", nRdIdx, nRdBusy, nRdReorder);

	return;
}
