#include <stdio.h>
#include "defines.h"
#include "helper.h"

#define RS_NUM	8

int rs_busy[RS_NUM] = {0}; // 1 bit
int rs_dest[RS_NUM] = {0}; // 3 bits
int rs_op[RS_NUM] = {0}; // 20 bits
int rs_vj[RS_NUM] = {0}; // 32 bits
int rs_vk[RS_NUM] = {0}; // 32 bits
int rs_qj[RS_NUM] = {0}; // 32 bits
int rs_qk[RS_NUM] = {0}; // 32 bits
int rs_a[RS_NUM] = {0}; // 32 bits

int* g_rs_busy = rs_busy;
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

	__in  char rob_idx[3]


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


	if (0 == in_valid[0]) return;
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
	}
	else
	{
		g_rs_qj[nR] = 0;
		g_rs_vj[nR] = nRjData;
	}


	if (1 == nRkBusy)
	{
		g_rs_qk[nR] = nRkReorder;
	}
	else
	{
		g_rs_qk[nR] = 0;
		g_rs_vk[nR] = nRkData;
	}

	g_rs_busy[nR] = 1;
	g_rs_dest[nR] = nRobIdx;
	g_rs_op[nR] = nInstr;

	return;
}


void display_reservation_station (void)
{
	int i = 0;

	PRINTF("          ##################  RESERVATION STATION  ##################\n");
	PRINTF("  =============================================================================\n");
	PRINTF("  %5s %9s %9s %9s %9s %9s %9s %9s\n", "Busy", "ROB", "Instr", "Vj", "Vk", "Qj", "Qk", "A");
	PRINTF("  =============================================================================\n");

	for (i = 1; i < RS_NUM; i++)
	{
		PRINTF("  %5s %9d %9x %9x %9x %9d %9d %9x\n", g_rs_busy[i] ? "yes":"no ", g_rs_dest[i], g_rs_op[i], g_rs_vj[i], g_rs_vk[i], g_rs_qj[i], g_rs_qk[i], g_rs_a[i]);
	}	

	PRINTF("  _____________________________________________________________________________\n");
	PRINTF("          ###########################################################\n");

	return;
}
