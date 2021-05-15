#include <stdio.h>
#include "core.h"
#include "ram_2port.h"
#include "helper.h"

int top (char bit_clk, int b_rising_edge, int b_falling_edge)
{

	char pc[32] = {0};
	char instr[32] = {0};

	char read_addr[32] = {0};
	char read_data[32] = {0};

	char write_addr[32] = {0};
	char write_data[32] = {0};

	char allzero[32] = {0};


	if (b_rising_edge) printf("r");
	if (b_falling_edge) printf("f");

	if (bit_clk)
	{
		printf("-");
	}
	else
	{
		printf("_");
	}
	
	ifu(bit_clk, 0, read_addr, read_data, write_addr, write_data); 

	ram_2port(pc, read_addr, bit_clk, allzero, write_data, 0, 0, instr, read_data);

	printf("read instruction: \n");
	print_char32bits(instr);

	return 0;	
}
