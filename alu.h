#ifndef _ALU_H_
#define _ALU_H_

void alu0 (
	__in  char alu0_issue_e[1],
	__in  char alu0_op_e[4],
	__in  char alu0_rj_e[32],
	__in  char alu0_rk_e[32],
	__in  char alu0_rob_e[3],
	__out char alu0_result_w[32],
	__out char alu0_rob_w[3]
	);

void alu1 (
	__in  char alu1_issue_e[1],
	__in  char alu1_op_e[4],
	__in  char alu1_rj_e[32],
	__in  char alu1_rk_e[32],
	__in  char alu1_rob_e[3],
	__out char alu1_result_w[32],
	__out char alu1_rob_w[3]
	);

#endif
