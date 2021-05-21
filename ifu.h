#ifndef _IFU_H_
#define _IFU_H_

void
ifu (
	__in  char clk,
	__in  char rst,
	__out char read_addr[32],
	__in  char read_data[32],
	__out char write_addr[32],
	__out char write_data[32],
	__in  char pc_current[32],
	__out char pc_next[32],
	__out char pc_next_ena[1],
	__in  char instr[32] 
	);

#endif
