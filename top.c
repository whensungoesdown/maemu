#include <stdio.h>
#include "defines.h"
#include "ifu.h"
#include "ram_2port.h"
#include "helper.h"
#include "latdff.h"

int top (char bit_clk, int b_rising_edge, int b_falling_edge)
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
	if (b_rising_edge) printf("r");
	if (b_falling_edge) printf("f");

	if (bit_clk)
	{
		printf("-\n");
	}
	else
	{
		printf("_\n");
	}
	

	ram_2port(pc_fetch, read_addr, bit_clk, allzero, write_data, 0, 0, instr, read_data);

	ifu(bit_clk, 0, read_addr, read_data, write_addr, write_data, pc_fetch, pc_next, pc_next_ena, instr); 

	pc_lat(pc_next_ena, pc_next, pc_fetch);

	//printf("read instruction: \n");
	//print_char32bits(instr);

	return 0;	
}
