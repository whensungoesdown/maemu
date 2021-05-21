#include <stdio.h>
#include "defines.h"
#include "helper.h"
#include "decode.h"
#include "rf.h"

void
exu (
	__in char clk,
	__in char rising_edge,
	__in char rst,
	__in char instr0[32]
    )
{
	int nInstr0 = 0;


	static char rd[32] = {0};
	static char rd_wen[1] = {0};
	static char rj[32] = {0};
	static char rk[32] = {0};

	static char rj_idx[5] = {0};
	static char rk_idx[5] = {0};
	static char rd_idx[5] = {0};

	static char rj_busy[1] = {0};
	static char rk_busy[1] = {0};
	static char rd_busy[1] = {0};

	static char rj_reorder[3] = {0};
	static char rk_reorder[3] = {0};
	static char rd_reorder[3] = {0};

	static char simm[32] = {0};


	int nRd = 0;
	int nRj = 0;
	int nRk = 0;
	int nRdWen = 0;
	

	if (0 == clk) return;

	if (rising_edge)
	{
		char32bits2int(instr0, &nInstr0);
		PRINTF("exu: instr0 0x%x\n", nInstr0);
	}
	

	rf(
		rj_idx,
		rk_idx,
		rj,
		rk,
		rj_busy,
		rk_busy,
		rj_reorder,
		rk_reorder,

		rd_wen,
		rd_idx,
		rd,
		rd_busy,
		rd_reorder,

		clk,
		rising_edge,
		rst
	  );

	char32bits2int(rd, &nRd);
	char32bits2int(rj, &nRj);
	char32bits2int(rk, &nRk);
	charnbits2int(rd_wen, &nRdWen, 1);

	if (rising_edge)
	{
		PRINTF("exu: rj 0x%x, rk 0x%x,   wen %d, rd 0x%x\n", nRj, nRk, nRdWen, nRd);
	}

	decode(instr0, rj_idx, rk_idx, rd_idx, simm);

	return;
}
