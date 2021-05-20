#ifndef _IFU_H_
#define _IFU_H_

void
ifu (
	char clk,
	char rst,
	char read_addr[32],
	char read_data[32],
	char write_addr[32],
	char write_data[32],
	char pc[32],
	char instr[32] 
	);

#endif
