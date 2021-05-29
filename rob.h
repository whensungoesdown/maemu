#ifndef _ROB_H_
#define _ROB_H_

void
rob (
	__in  char valid[1],
	__out char ready[1],
	__out char rob_idx[3],
	__in  char instr0[32],
	__in  char rd_idx[5]
    );

void
display_rob (void);

#endif
