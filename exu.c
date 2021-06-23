#include <stdio.h>
#include <string.h>
#include "defines.h"
#include "helper.h"
#include "decode.h"
#include "rf.h"
#include "reservation_station.h"
#include "rob.h"
#include "register_stat.h"
#include "latdff.h"
#include "alu.h"

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
	char alloc_rs_d[1] = {0};
	char alloc_rob_d[1] = {0};
	char regwrite[1] = {0};



	static char alu0_rs_d[3] = {0};
	static char alu0_issue_d[1] = {0};
	static char alu0_op_d[4] = {0};
	static char alu0_rj_d[32] = {0};
	static char alu0_rk_d[32] = {0};
	static char alu0_rob_d[3] = {0};

	static char _alu0_rs_d[3] = {0};
	static char _alu0_issue_d[1] = {0};
	static char _alu0_op_d[4] = {0};
	static char _alu0_rj_d[32] = {0};
	static char _alu0_rk_d[32] = {0};
	static char _alu0_rob_d[3] = {0};


	static char alu1_rs_d[3] = {0};
	static char alu1_issue_d[1] = {0};
	static char alu1_op_d[4] = {0};
	static char alu1_rj_d[32] = {0};
	static char alu1_rk_d[32] = {0};
	static char alu1_rob_d[3] = {0};

	static char _alu1_rs_d[3] = {0};
	static char _alu1_issue_d[1] = {0};
	static char _alu1_op_d[4] = {0};
	static char _alu1_rj_d[32] = {0};
	static char _alu1_rk_d[32] = {0};
	static char _alu1_rob_d[3] = {0};

	//static char alu0_rs_e[3] = {0};
	static char alu0_issue_e[1] = {0};
	static char alu0_op_e[4] = {0};
	static char alu0_rj_e[32] = {0};
	static char alu0_rk_e[32] = {0};
	static char alu0_rob_e[3] = {0};

	//static char alu1_rs_e[3] = {0};
	static char alu1_issue_e[1] = {0};
	static char alu1_op_e[4] = {0};
	static char alu1_rj_e[32] = {0};
	static char alu1_rk_e[32] = {0};
	static char alu1_rob_e[3] = {0};


	static char alu0_result_e[32] = {0};

	static char _alu0_issue_e[1] = {0};
	static char _alu0_result_e[32] = {0};
	static char _alu0_rob_e[3] = {0};


	static char alu1_result_e[32] = {0};

	static char _alu1_issue_e[1] = {0};
	static char _alu1_result_e[32] = {0};
	static char _alu1_rob_e[3] = {0};




	static char alu0_issue_w[1] = {0};
	static char alu0_result_w[32] = {0};
	static char alu0_rob_w[3] = {0};


	static char alu1_issue_w[1] = {0};
	static char alu1_result_w[32] = {0};
	static char alu1_rob_w[3] = {0};




	if (0 == clk)
	{
		// after the high cycle, in the low cycle
		// update the signals that send to next stage registers
		
		memcpy(_alu0_rs_d, alu0_rs_d, 3);
		memcpy(_alu0_issue_d, alu0_issue_d, 1);
		memcpy(_alu0_op_d, alu0_op_d, 3);
		memcpy(_alu0_rj_d, alu0_rj_d, 32);
		memcpy(_alu0_rk_d, alu0_rk_d, 32);
		memcpy(_alu0_rob_d, alu0_rob_d, 3);
	
//		PRINTF("!!!!!!!!!alu0_issue_d:");
//		print_charnbits(alu0_issue_d, 1);
//		PRINTF("!!!!!!!!!alu0_rob_d:");
//		print_charnbits(alu0_rob_d, 3);

		memcpy(_alu1_rs_d, alu1_rs_d, 3);
		memcpy(_alu1_issue_d, alu1_issue_d, 1);
		memcpy(_alu1_op_d, alu1_op_d, 3);
		memcpy(_alu1_rj_d, alu1_rj_d, 32);
		memcpy(_alu1_rk_d, alu1_rk_d, 32);
		memcpy(_alu1_rob_d, alu1_rob_d, 3);

//		PRINTF("  test: register:\n");
//		PRINTF("      alu0_issue_d:");
//		print_charnbits(alu0_issue_d, 1);
//		PRINTF("      alu0_rj_d:");
//		print_char32bits(alu0_rj_d);
//		PRINTF("      alu0_rk_d:");
//		print_char32bits(alu0_rk_d);
//		PRINTF("      alu0_rob_d:");
//		print_charnbits(alu0_rob_d, 3);

		// next stage

		memcpy(_alu0_issue_e, alu0_issue_e, 1);
		memcpy(_alu0_result_e, alu0_result_e, 32);
		memcpy(_alu0_rob_e, alu0_rob_e, 3);

		memcpy(_alu1_issue_e, alu1_issue_e, 1);
		memcpy(_alu1_result_e, alu1_result_e, 32);
		memcpy(_alu1_rob_e, alu1_rob_e, 3);

		return;
	}

	if (rising_edge)
	{
		//
		// sequential logic
		//

		PRINTF("\nID stage: **********************************************\n");

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

		PRINTF("\nID stage: **********************************************\n");
		//
		// decode
		//
		decode(instr_d, rj_idx_d, rk_idx_d, rd_idx, simm, 
				alloc_rs_d, alloc_rob_d,
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

		rob_valid[0] = alloc_rob_d[0];


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

		//rs_valid[0] = rob_valid[0] & rob_ready[0] & alloc_rs_d[0];
		rs_valid[0] = alloc_rs_d[0];

		// now only sends in one instructin but sents out two to ALU
		// 
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

				rob_idx,

				// issue to alu
				alu0_rs_d,
				alu0_issue_d,
				alu0_op_d,
				alu0_rj_d,
				alu0_rk_d,
				alu0_rob_d,

				alu1_rs_d,
				alu1_issue_d,
				alu1_op_d,
				alu1_rj_d,
				alu1_rk_d,
				alu1_rob_d
				);

		display_reservation_station();

		//
		// Check conflicts, then issue to funtional units such as ALU 
		//
		// For now, we only have 2 ALUs, alu0 alu1
		// each of them has pipleline registers for the operation and operands
		//

	}

	//
	// Next stage
	//  EX
	//
	
	if (rising_edge)
	{
		//
		// sequential logic
		//

//		PRINTF("!!!!!!!!!_alu0_issue_d:");
//		print_charnbits(_alu0_issue_d, 1);
//		PRINTF("!!!!!!!!!_alu0_rob_d:");
//		print_charnbits(_alu0_rob_d, 3);

		//dff_alu0_rs_d2e(clk, rising_edge, rst, _alu0_rs_d, alu0_rs_e);
		dff_alu0_issue_d2e(clk, rising_edge, rst, _alu0_issue_d, alu0_issue_e);
		dff_alu0_op_d2e(clk, rising_edge, rst, _alu0_op_d, alu0_op_e);
		dff_alu0_rj_d2e(clk, rising_edge, rst, _alu0_rj_d, alu0_rj_e);
		dff_alu0_rk_d2e(clk, rising_edge, rst, _alu0_rk_d, alu0_rk_e);
		dff_alu0_rob_d2e(clk, rising_edge, rst, _alu0_rob_d, alu0_rob_e);

//		PRINTF("!!!!!!!!!alu0_issue_e:");
//		print_charnbits(alu0_issue_e, 1);
//		PRINTF("!!!!!!!!!alu0_rob_e:");
//		print_charnbits(alu0_rob_e, 3);
//
//		PRINTF("  EX: Pipeline register:\n");
//		PRINTF("      _alu0_issue_d:");
//		print_charnbits(_alu0_issue_d, 1);
//		PRINTF("      _alu0_rj_d:");
//		print_char32bits(_alu0_rj_d);
//		PRINTF("      _alu0_rk_d:");
//		print_char32bits(_alu0_rk_d);
//		PRINTF("      _alu0_rob_d:");
//		print_charnbits(_alu0_rob_d, 3);
//
//
//		PRINTF("  EX: Pipeline register:\n");
//		PRINTF("      alu1_issue_e:");
//		print_charnbits(alu1_issue_e, 1);
//		PRINTF("      alu1_rj_e:");
//		print_char32bits(alu1_rj_e);
//		PRINTF("      alu1_rk_e:");
//		print_char32bits(alu1_rk_e);
//		PRINTF("      alu1_rob_e:");
//		print_charnbits(alu1_rob_e, 3);



		//dff_alu1_rs_d2e(clk, rising_edge, rst, _alu1_rs_d, alu1_rs_e);
		dff_alu1_issue_d2e(clk, rising_edge, rst, _alu1_issue_d, alu1_issue_e);
		dff_alu1_op_d2e(clk, rising_edge, rst, _alu1_op_d, alu1_op_e);
		dff_alu1_rj_d2e(clk, rising_edge, rst, _alu1_rj_d, alu1_rj_e);
		dff_alu1_rk_d2e(clk, rising_edge, rst, _alu1_rk_d, alu1_rk_e);
		dff_alu1_rob_d2e(clk, rising_edge, rst, _alu1_rob_d, alu1_rob_e);

	}
	else
	{
		//
		// combinational logic
		//
		PRINTF("\nEX stage: **********************************************\n");

		alu0(alu0_issue_e, alu0_op_e, alu0_rj_e, alu0_rk_e, alu0_result_e);
		PRINTF("  ALU0 issue %d\n", alu0_issue_e[0]);
		PRINTF("           rj:");
		print_char32bits(alu0_rj_e);
		PRINTF("           rk:");
		print_char32bits(alu0_rk_e);
		PRINTF("       result:");
		print_char32bits(alu0_result_e);
		PRINTF("          rob:");
		print_charnbits(alu0_rob_e, 3);

		alu1(alu1_issue_e, alu1_op_e, alu1_rj_e, alu1_rk_e, alu1_result_e);
		PRINTF("  ALU1 issue %d\n", alu1_issue_e[0]);
		PRINTF("           rj:");
		print_char32bits(alu1_rj_e);
		PRINTF("           rk:");
		print_char32bits(alu1_rk_e);
		PRINTF("       result:");
		print_char32bits(alu1_result_e);
		PRINTF("          rob:");
		print_charnbits(alu1_rob_e, 3);

	}

	//
	// Next stage
	//  WB
	//
	
	if (rising_edge)
	{
		//
		// sequential logic
		//
		dff_alu0_issue_e2w(clk, rising_edge, rst, _alu0_issue_e, alu0_issue_w);
		dff_alu0_result_e2w(clk, rising_edge, rst, _alu0_result_e, alu0_result_w);
		dff_alu0_rob_e2w(clk, rising_edge, rst, _alu0_rob_e, alu0_rob_w);

		dff_alu1_issue_e2w(clk, rising_edge, rst, _alu1_issue_e, alu1_issue_w);
		dff_alu1_result_e2w(clk, rising_edge, rst, _alu1_result_e, alu1_result_w);
		dff_alu1_rob_e2w(clk, rising_edge, rst, _alu1_rob_e, alu1_rob_w);
	}
	else
	{
		//
		// combinational logic
		//

		// rob_commit should take at least 2 clock cycles,
		// one for write data, one for commit and release rob entry 
		// but, it is difficult to emulate using C.
		

		PRINTF("\nWB stage: **********************************************\n");

		reservation_station_writeback(
				alu0_issue_w,
				alu0_result_w,
				alu0_rob_w,
				alu1_issue_w,
				alu1_result_w,
				alu1_rob_w
				);


		display_reservation_station();

		rob_writeback(
				alu0_issue_w, 
				alu0_result_w, 
				alu0_rob_w, 
				alu1_issue_w, 
				alu1_result_w,
				alu1_rob_w 
				);

		display_rob();

	}
	return;
}
