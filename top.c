#include <stdio.h>
#include "defines.h"
#include "ifu.h"
#include "ram_2port.h"
#include "helper.h"
#include "latdff.h"
#include "exu.h"

int top (char clk, int b_rising_edge, int b_falling_edge)
{

	static char pc_next[32] = {0};
	static char pc_next_ena[1] = {0};
	static char pc_fetch[32] = {0}; // pc_current, no cache, pc_current and pc_fetch are the same

	static char instr[32] = {0};

	static char read_addr[32] = {0};
	static char read_data[32] = {0};

	static char write_addr[32] = {0};
	static char write_data[32] = {0};

	char allzero[32] = {0};


	printf("\n");
	if (b_rising_edge) printf("/");
	if (b_falling_edge) printf("\\");

	if (clk)
	{
		printf("~\n");
	}
	else
	{
		printf("_\n");
	}
	

	ram_2port(pc_fetch, read_addr, clk, b_rising_edge, allzero, write_data, 0, 0, instr, read_data);

	ifu(clk, b_rising_edge, 0, read_addr, read_data, write_addr, write_data, pc_fetch, pc_next, pc_next_ena); 

	if (clk && !b_rising_edge)
	{
		// combinational
		pc_lat(pc_next_ena, pc_next, pc_fetch);
	}


	// exu output branch_pc, jump_pc, excp_pc back to ifu to make the decision for next fetching
	exu(clk, b_rising_edge, 0, instr); // later 2 issue, exu(instr0, instr1)

	return 0;	
}
