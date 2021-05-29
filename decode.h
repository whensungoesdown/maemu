#ifndef _DECODE_H_
#define _DECODE_H_

void
decode (
	__in  char instr[32],
	__out char rj_idx[5],
	__out char rk_idx[5],
	__out char rd_idx[5],
	__out char simm[32],

	__out char need_rs[1],
	__out char need_rob[1],
	__out char regwrite[1]
       );
#endif
