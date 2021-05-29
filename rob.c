#include <stdio.h>
#include "defines.h"
#include "helper.h"


// 0 indicates that rob is full
//
// 1 2 3 4 5 6 7
// ^       ^
// head    tail


#define ROB_NUM 	8

int rob_dest[ROB_NUM] = {0}; // 5 bits
int rob_opcode[ROB_NUM] = {0}; // 20 bits
int rob_value[ROB_NUM] = {0}; // 32 bits
int rob_ready[ROB_NUM] = {0}; // 1 bit
int rob_busy[ROB_NUM] = {0}; // 1 bit

int* g_rob_dest = rob_dest;
int* g_rob_opcode = rob_opcode;
int* g_rob_value = rob_value; // write back
int* g_rob_ready = rob_ready; // write back
int* g_rob_busy = rob_busy;   // commit



int g_rob_head = 1;
int g_rob_tail = 1;

int g_b_rob_full = 0;

int 
rob_alloc_entry (
	//__out char rob_idx[3]
	)
{
	if (1 == g_b_rob_full)
	{
		//int2charnbits(0, rob_idx, 3);
		return 0;
	}

	if (7 == g_rob_tail)
	{
		g_rob_tail = 1;
	}
	else
	{
		g_rob_tail ++;
	}

	if (g_rob_tail == g_rob_head)
	{
		g_b_rob_full = 1;
	}

	//int2charnbits(g_rob_tail - 1, rob_idx, 3);

	return g_rob_tail - 1;
}

void rob_free_entry ()
{
	if (0 == g_b_rob_full && g_rob_head == g_rob_tail)
	{
		printf("ERROR: rob_free_entry(), rob is already empty\n");
		return;
	}

	g_rob_head += 1;

	if (1 == g_b_rob_full)
	{
		g_b_rob_full = 0;
	}
}

void
rob (
	__in  char valid[1],
	__out char ready[1],
	__out char rob_idx[3],
	__in  char instr[32],
	__in  char rd_idx[5]
    )
{
	int nRobIdx = 0;
	int nInstr = 0;
	int nRdIdx = 0;

	if (0 == valid[0]) return;

	// get rob entry
	//
	nRobIdx = rob_alloc_entry();
	
	char32bits2int(instr, &nInstr);
	charnbits2int(rd_idx, &nRdIdx, 5);

	g_rob_opcode[nRobIdx] = nInstr;
	g_rob_dest[nRobIdx] = nRdIdx;
	g_rob_ready[nRobIdx] = 0; // no
	g_rob_busy[nRobIdx] = 1;


	int2charnbits(nRobIdx, rob_idx, 3);
	ready[0] = 1;


	PRINTF("  rob entry %d, instr 0x%x, regdest %d, ready %d, busy %d\n", 
			nRobIdx, g_rob_opcode[nRobIdx], g_rob_dest[nRobIdx],
			g_rob_ready[nRobIdx], g_rob_busy[nRobIdx]);

	return;
}

void
display_rob (void)
{
	int i = 0;


	PRINTF("          @@@@@@@@@@@@@@@@@@@@@  REORDER BUFFER  @@@@@@@@@@@@@@@@@@@@\n");
	PRINTF("  ____________________________________________________________________________\n");
	PRINTF("  || Busy    ||");
	for (i = 1; i < ROB_NUM; i++)
	{
		if (1 == g_rob_busy[i])
		{
			PRINTF(" %-7s|", "yes");
		}
		else
		{
			PRINTF(" %-7s|", "no");
		}
	}
	PRINTF("\n");

	PRINTF("  || RegDest ||");
	for (i = 1; i < ROB_NUM; i++)
	{
		PRINTF(" %-7d|", g_rob_dest[i]);
	}
	PRINTF("\n");

	PRINTF("  || Instr   ||");
	for (i = 1; i < ROB_NUM; i++)
	{
		PRINTF(" %-7x|", g_rob_opcode[i]);
	}
	PRINTF("\n");

	PRINTF("  || Value   ||");
	for (i = 1; i < ROB_NUM; i++)
	{
		if (0 == g_rob_ready[i])
		{
			PRINTF(" %-7s|", "");
		}
		else
		{
			PRINTF(" %-7x|", g_rob_value[i]);
		}
	}
	PRINTF("\n");
	
	PRINTF("  || Ready   ||");
	for (i = 1; i < ROB_NUM; i++)
	{
		if (1 == g_rob_ready[i])
		{
			PRINTF(" %-7s|", "yes");
		}
		else
		{
			PRINTF(" %-7s|", "no");
		}
	}
	PRINTF("\n");
	PRINTF("  ____________________________________________________________________________\n");
	PRINTF("          @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
}
