#include <stdio.h>
#include "defines.h"
#include "helper.h"
#include "decode.h"
#include "rf.h"
#include "reservation_station.h"
#include "rob.h"
#include "register_stat.h"
#include "latdff.h"

void
exu (
	__in char clk,
	__in char rising_edge,
	__in char rst,
	__in char instr0[32]
    )
{
	int nInstr_d = 0;


	static char instr_d[32] = {0};

	static char rd[32] = {0};
	static char rd_wen[1] = {0};
	static char rj_d[32] = {0};
	static char rk_d[32] = {0};

	static char rj_idx_d[5] = {0};
	static char rk_idx_d[5] = {0};
	static char rd_idx[5] = {0};

	static char rj_busy_d[1] = {0};
	static char rk_busy_d[1] = {0};
//	static char rd_busy[1] = {0};

	static char rj_reorder_d[3] = {0};
	static char rk_reorder_d[3] = {0};
//	static char rd_reorder[3] = {0};

	static char simm[32] = {0};


	int nRdIdx = 0;
	int nRd = 0;
	int nRj_d = 0;
	int nRk_d = 0;
	int nRdWen = 0;
	

	char rob_valid[1] = {0};
	char rob_ready[1] = {0};

	char rs_valid[1] = {0};
	char rs_ready[1] = {0};

	char rob_idx[3] = {0};
	
	//char const1[1] = {1};


	// control signals
	char need_rs[1] = {0};
	char need_rob[1] = {0};
	char regwrite[1] = {0};


	if (0 == clk) return;

	if (rising_edge)
	{
		//
		// sequential logic
		//


		dff_instr_f2d(clk, rising_edge, rst, instr0, instr_d);
		char32bits2int(instr_d, &nInstr_d);
		PRINTF("EXU ID\n");
		PRINTF("  instr_d: 0x%x\n", nInstr_d);

		
		//
		// register file has two parts
		//  read is asynchronous, write is synchronous

		rf(
				rj_idx_d,
				rk_idx_d,
				rj_d,
				rk_d,
				//		rj_busy,
				//		rk_busy,
				//		rj_reorder,
				//		rk_reorder,

				rd_wen,
				rd_idx,
				rd,
				//		rd_busy,
				//		rd_reorder,

				clk,
				rising_edge,
				rst
		  );


		charnbits2int(rd_idx, &nRdIdx, 5);
		char32bits2int(rd, &nRd);
		charnbits2int(rd_wen, &nRdWen, 1);

		if (1 == nRdWen)
		{
			PRINTF("  WB: rf write rd %d: 0x%x\n", nRdIdx, nRd);
		}
	}
	else

	{
		//
		// combinational logic

		//
		// decode
		//
		decode(instr_d, rj_idx_d, rk_idx_d, rd_idx, simm, 
				need_rs, need_rob,
				regwrite);




		rf(
				rj_idx_d,
				rk_idx_d,
				rj_d,
				rk_d,
				//		rj_busy,
				//		rk_busy,
				//		rj_reorder,
				//		rk_reorder,

				rd_wen,
				rd_idx,
				rd,
				//		rd_busy,
				//		rd_reorder,

				clk,
				rising_edge,
				rst
		  );

		char32bits2int(rj_d, &nRj_d);
		char32bits2int(rk_d, &nRk_d);

		PRINTF("  ID stage: rj_d: 0x%x, rk_d: 0x%x\n", nRj_d, nRk_d);

		rob_valid[0] = need_rob[0];


		//
		// allocat rob
		//
		rob(rob_valid, rob_ready, rob_idx, instr_d, rd_idx);
		display_rob();


		register_stat(
				rj_idx_d,
				rk_idx_d,
				rj_busy_d,
				rk_busy_d,
				rj_reorder_d,
				rk_reorder_d,

				regwrite, // rd_wen  // todo: rdwrite
				rd_idx,
				regwrite, // rd_busy
				rob_idx
			     );

		//rs_valid[0] = rob_valid[0] & rob_ready[0] & need_rs[0];
		rs_valid[0] = need_rs[0];

		reservation_station(
				rs_valid,
				rs_ready,
				
				instr_d,

				rj_busy_d,
				rj_d,
				rj_reorder_d,

				rk_busy_d,
				rk_d,
				rk_reorder_d,
				rob_idx
				);

		display_reservation_station();

	}

	return;
}
