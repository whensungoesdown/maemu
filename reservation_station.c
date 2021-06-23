#include <stdio.h>
#include "defines.h"
#include "helper.h"

#define RS_NUM	8

int rs_busy[RS_NUM] = {0}; // 1 bit
int rs_issue[RS_NUM] = {0}; // 1 bit
int rs_dest[RS_NUM] = {0}; // 3 bits
int rs_op[RS_NUM] = {0}; // 20 bits
int rs_vj[RS_NUM] = {0}; // 32 bits
int rs_vk[RS_NUM] = {0}; // 32 bits
int rs_qj[RS_NUM] = {0}; // 32 bits
int rs_qk[RS_NUM] = {0}; // 32 bits
int rs_a[RS_NUM] = {0}; // 32 bits

int* g_rs_busy = rs_busy;
int* g_rs_issue = rs_issue;
int* g_rs_dest = rs_dest;
int* g_rs_op = rs_op;
int* g_rs_vj = rs_vj;
int* g_rs_vk = rs_vk;
int* g_rs_qj = rs_qj;
int* g_rs_qk = rs_qk;
int* g_rs_a = rs_a;


//
// 0 indicates that reservation station is full
//

int
rs_alloc_entry (void)
{
	int i = 0;

	for (i = 1; i < RS_NUM; i++)
	{
		if (0 == g_rs_busy[i])
		{
			return i;
		}
	}

	return i;
}

void
reservation_station (
	//__in  char clk,
	//__in  char rising_edge,
	__in  char in_valid[1],
	__out char in_ready[1],

	__in  char instr[32],

	__in  char rj_busy[1],
	__in  char rj_data[32],
	__in  char rj_reorder[3],

	__in  char rk_busy[1],
	__in  char rk_data[32],
	__in  char rk_reorder[3],

	__in  char rob_idx[3],


	__out char alu0_rs_d[3],
	__out char alu0_issue_d[1],
	__out char alu0_op_d[4],
	__out char alu0_rj_d[32],
	__out char alu0_rk_d[32],
	__out char alu0_rob_d[3],


	__out char alu1_rs_d[3],
	__out char alu1_issue_d[1],
	__out char alu1_op_d[4],
	__out char alu1_rj_d[32],
	__out char alu1_rk_d[32],
	__out char alu1_rob_d[3]



//	__in  char busy[1],
//	__in  char dest[3],
//	__in  char op[20],
//	__in  char vj[32],
//	__in  char vk[32],
//	__in  char qj[32],
//	__in  char qk[32],
//	__in  char a[32],
//	__out char full[1]


//	__out char out_valid[1],
//	__in  char out_ready[1],
//
//	__out char rj[32],
//	__out char rk[32],
//	__out char rd_idx[5]
   )
{
	// always @ (posedge valid)
	//
	
//	int slot = 0;

	//if (1 == valid)
	//{
	//}
	
	// slot returning 0 indicates rs is full
	//slot = get_slot();

	// assign ready = slot	if (0 == slot)
//	{
//		full[1] = 0;
//		return;
//	}
//
//	g_rs_busy[slot] = busy;
//	g_rs_op[slot] = op;
//	g_rs_vj[slot] = vj;
//	g_rs_vk[slot] = vk;
//	g_rs_qj[slot] = qj;
//	g_rs_qk[slot] = qk;
//	g_rs_a[slot] = a;

	//char r[3] = {0};

	int nR = 0;

	int nInstr = 0;

	int nRjBusy = 0;
	int nRjData = 0;
	int nRjReorder = 0;

	int nRkBusy = 0;
	int nRkData = 0;
	int nRkReorder = 0;

	int nRobIdx = 0;

	int i = 0;


	//if (0 == in_valid[0]) return;
	// get a new entry, suppose r
	
	//charnbits2int(r, &nR, 3);
	nR = rs_alloc_entry();	

	char32bits2int(instr, &nInstr);

	charnbits2int(rj_busy, &nRjBusy, 1);
	char32bits2int(rj_data, &nRjData);
	charnbits2int(rj_reorder, &nRjReorder, 3);

	charnbits2int(rk_busy, &nRkBusy, 1);
	char32bits2int(rk_data, &nRkData);
	charnbits2int(rk_reorder, &nRkReorder, 3);

	charnbits2int(rob_idx, &nRobIdx, 3);


	if (1 == nRjBusy)
	{
		g_rs_qj[nR] = nRjReorder;
		g_rs_vj[nR] = 0;
	}
	else
	{
		g_rs_qj[nR] = 0;
		g_rs_vj[nR] = nRjData;
	}


	if (1 == nRkBusy)
	{
		g_rs_qk[nR] = nRkReorder;
		g_rs_vk[nR] = 0;
	}
	else
	{
		g_rs_qk[nR] = 0;
		g_rs_vk[nR] = nRkData;
	}

	g_rs_busy[nR] = 1;
	g_rs_issue[nR] = 0;
	g_rs_dest[nR] = nRobIdx;
	g_rs_op[nR] = nInstr;


	//
	// In the program, alu0_issue_d is a static string.
	// In circuit, it's value should comes from a register, which is one
	// reservation station entry.
	//
	// Here, we need to clear alu0_issue_d and alu1_issue_d.
	// Because there may be no rs entry need to issue.
	//
	alu0_issue_d[0] = 0;
	alu1_issue_d[0] = 0;



	//
	// issue to the functional units when 2 operands both are available
	//
	
	// uty: bug
	// the reservation station slot need to release itself
	// after issuing. The V and Q fields should maintain the setup time
	// for the next stage pipleline register. But the busy bit may be 
	// cleared.
	// It looks like forming a loop in this way, maybe the reservation
	// station slots can be released when committing.

	i = 0;
	while (i < RS_NUM)
	{
		i ++;

		if ((1 == g_rs_busy[i]) && (0 == g_rs_issue[i]) && (0 == g_rs_qj[i]) && (0 == g_rs_qk[i]))
		{
			PRINTF("  Issue ALU0: add  rob_%d, 0x%x, 0x%x\n", g_rs_dest[i], g_rs_vj[i], g_rs_vk[i]);
			alu0_issue_d[0] = 1;
			// alu0_op_d
			int2char32bits(g_rs_vj[i], alu0_rj_d);
			int2char32bits(g_rs_vk[i], alu0_rk_d);
			int2charnbits(g_rs_dest[i], alu0_rob_d, 3);
			int2charnbits(i, alu0_rs_d, 3);

			// bug: clear self busy bit
			//g_rs_busy[i] = 0;
			//g_rs_dest[i] = 0;
			//g_rs_vj[i] = 0;
			//g_rs_vk[i] = 0;
			// fix: release rs at reservation_station_writeback()
			//  think again, the busy has to be clear in this cycle
			//  otherwise, the next coming cycle will issue this again
			//

			// only set issue field, commit will release this entry
			g_rs_issue[i] = 1;  
			break;
		}
	}

	
	while (i < RS_NUM)
	{
		i ++;

		if ((1 == g_rs_busy[i]) && (0 == g_rs_issue[i]) && (0 == g_rs_qj[i]) && (0 == g_rs_qk[i]))
		{
			PRINTF("  Issue ALU1: add  rob_%d, 0x%x, 0x%x\n", g_rs_dest[i], g_rs_vj[i], g_rs_vk[i]);
			alu1_issue_d[0] = 1;
			// alu1_op_d
			int2char32bits(g_rs_vj[i], alu1_rj_d);
			int2char32bits(g_rs_vk[i], alu1_rk_d);
			int2charnbits(g_rs_dest[i], alu1_rob_d, 3);
			int2charnbits(i, alu1_rs_d, 3);

			// bug: clear self busy bit
			//g_rs_busy[i] = 0;
			//g_rs_dest[i] = 0;
			//g_rs_vj[i] = 0;
			//g_rs_vk[i] = 0;
			// fix: release rs at reservation_station_writeback()
			//  think again, the busy has to be clear in this cycle
			//  otherwise, the next coming cycle will issue this again
			//

			// only set issue field, commit will release this entry
			g_rs_issue[i] = 1;  
			break;
		}
	}

	return;
}


void
reservation_station_writeback (
	__in  char alu0_issue_w[1],
	__in  char alu0_result_w[32],
	__in  char alu0_rob_w[3],

	__in  char alu1_issue_w[1],
	__in  char alu1_result_w[32],
	__in  char alu1_rob_w[3]
	)
{
	int nAlu0Result = 0;
	int nAlu0Rob = 0;

	int nAlu1Result = 0;
	int nAlu1Rob = 0;

	int i = 0;


	char32bits2int(alu0_result_w, &nAlu0Result);
	charnbits2int(alu0_rob_w, &nAlu0Rob, 3);

	//PRINTF("  reservation_station_writeback(): alu0_result_w 0x%x\n", nAlu0Result);
	//PRINTF("  reservation_station_writeback(): alu0_rob_w 0x%x\n", nAlu0Rob);

	if (1 == alu0_issue_w[0])
	{
		// clear rs entry
	//	g_rs_busy[nAlu0Rs] = 0;
	//	g_rs_dest[nAlu0Rs] = 0;
	//	g_rs_vj[nAlu0Rs] = 0;
	//	g_rs_vk[nAlu0Rs] = 0;


		for (i = 1; i < RS_NUM; i++)
		{
			if (nAlu0Rob == g_rs_qj[i])
			{
				g_rs_qj[i] = 0;
				g_rs_vj[i] = nAlu0Result;
			}
			if (nAlu0Rob == g_rs_qk[i])
			{
				g_rs_qk[i] = 0;
				g_rs_vk[i] = nAlu0Result;
			}
		}
	}


	char32bits2int(alu1_result_w, &nAlu1Result);
	charnbits2int(alu1_rob_w, &nAlu1Rob, 3);


	if (1 == alu1_issue_w[0])
	{
		// clear rs entry
	//	g_rs_busy[nAlu1Rs] = 0;
	//	g_rs_dest[nAlu1Rs] = 0;
	//	g_rs_vj[nAlu1Rs] = 0;
	//	g_rs_vk[nAlu1Rs] = 0;


		for (i = 1; i < RS_NUM; i++)
		{
			if (nAlu1Rob == g_rs_qj[i])
			{
				g_rs_qj[i] = 0;
				g_rs_vj[i] = nAlu1Result;
			}
			if (nAlu1Rob == g_rs_qk[i])
			{
				g_rs_qk[i] = 0;
				g_rs_vk[i] = nAlu1Result;
			}
		}
	}

	return;
}

void display_reservation_station (void)
{
	int i = 0;

	PRINTF("          ######################  RESERVATION STATION  #####################\n");
	PRINTF("  ======================================================================================\n");
	PRINTF("  %5s %9s %9s %9s %9s %9s %9s %9s %9s\n", "Busy", "Issue", "ROB", "Instr", "Vj", "Vk", "Qj", "Qk", "A");
	PRINTF("  ======================================================================================\n");

	for (i = 1; i < RS_NUM; i++)
	{
		PRINTF("  %5s %9s %9d %9x %9x %9x %9d %9d %9x\n", g_rs_busy[i] ? "yes":"no ", g_rs_issue[i] ? "yes":"no ",g_rs_dest[i], g_rs_op[i], g_rs_vj[i], g_rs_vk[i], g_rs_qj[i], g_rs_qk[i], g_rs_a[i]);
	}	

	PRINTF("  ______________________________________________________________________________________\n");
	PRINTF("          #################################################################\n");

	return;
}
