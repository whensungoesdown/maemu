#ifndef _LATDFF_H_
#define _LATDFF_H_

void
pc_lat (
	__in  char pc_ena[1],
	__in  char pc_next[32],
	__out char q[32]
       );

void
dff_instr_f2d (
	__in  char clk,
	__in  char rising_edge,
	__in  char rst,
	__in  char instr_f[32],
	__out char instr_d[32]
	);

#endif
