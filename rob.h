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
rob_writeback (
	__in  char alu0_issue_w[1],
	__in  char alu0_result_w[32],
	__in  char alu0_rob_w[3],
	__in  char alu1_issue_w[1],
	__in  char alu1_result_w[32],
	__in  char alu1_rob_w[3]
	);

void
display_rob (char* prefix);

#endif
