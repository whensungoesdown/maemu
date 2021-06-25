#include <stdio.h>
#include <string.h>
#include "defines.h"
#include "ifu.h"
#include "ram_2port.h"
#include "helper.h"
#include "latdff.h"
#include "exu.h"

void top (char clk, int b_rising_edge, int b_falling_edge)
{

	static char pc_next[32] = {0};
	static char pc_next_ena[1] = {0};
	static char pc_fetch[32] = {0}; // pc_current, no cache, pc_current and pc_fetch are the same

	static char instr[32] = {0};
	static char _instr[32] = {0};

	static char read_addr[32] = {0};
	static char read_data[32] = {0};

	static char write_addr[32] = {0};
	static char write_data[32] = {0};

	char allzero[32] = {0};
	char const0[1] = {0};

	static int nCycles = 0;


	printf("-------------------------------------------------------------------------------------------\n");
	if (b_rising_edge) printf("\n\n\n\n\n# \n# / (rising edge)  CYCLE %d  \n# \n\n", nCycles++);
	if (b_falling_edge) printf("\\ (falling edge)  ");

	if (clk)
	{
		printf("+ clk HIGH\n");
	}
	else
	{
		printf("_ clk LOW\n");
	}

	if (0 == clk) 
	{
		//
		// after each cycle, update wire for synchronous logic
		//  update name to  _name ...
		//
		memcpy(_instr, instr, 32);

		//return;
	}
	

	if (b_rising_edge)
	{
		//
		// sequential logic

		ram_2port(pc_fetch, read_addr, clk, b_rising_edge, allzero, write_data, const0, const0, instr, read_data);
	}
	
	ifu(clk, b_rising_edge, 0, read_addr, read_data, write_addr, write_data, pc_fetch, pc_next, pc_next_ena); 
	
	if (!b_rising_edge)
	{
		int nPcFetch = 0;
		// combinational logic
		pc_lat(pc_next_ena, pc_next, pc_fetch);
		char32bits2int(pc_fetch, &nPcFetch);
		PRINTF(IF_PREFIX"  pc_fetch: 0x%x\n", nPcFetch);
	}

	//
	// pipeline register instr

	// exu output branch_pc, jump_pc, excp_pc back to ifu to make the decision for next fetching
	exu(clk, b_rising_edge, 0, _instr); // later 2 issue, exu(instr0, instr1)

	

	
	return;	
}
