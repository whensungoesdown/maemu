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





// later, ALU should has a instruciton queue
void
dff_alu0_rs_d2e (
	__in  char clk,
	__in  char rising_edge,
	__in  char rst,
	__in  char alu0_rs_d[3],
	__out char alu0_rs_e[3]
	);

void
dff_alu0_issue_d2e (
	__in  char clk,
	__in  char rising_edge,
	__in  char rst,
	__in  char alu0_issue_d[1],
	__out char alu0_issue_e[1]
	);

void
dff_alu0_op_d2e (
	__in  char clk,
	__in  char rising_edge,
	__in  char rst,
	__in  char alu0_op_d[4],
	__out char alu0_op_e[4]
	);

void
dff_alu0_rj_d2e (
	__in  char clk,
	__in  char rising_edge,
	__in  char rst,
	__in  char alu0_rj_d[32],
	__out char alu0_rj_e[32]
	);
void
dff_alu0_rk_d2e (
	__in  char clk,
	__in  char rising_edge,
	__in  char rst,
	__in  char alu0_rk_d[32],
	__out char alu0_rk_e[32]
	);

void
dff_alu0_rob_d2e (
	__in  char clk,
	__in  char rising_edge,
	__in  char rst,
	__in  char alu0_rob_d[3],
	__out char alu0_rob_e[3]
	);


void
dff_alu1_rs_d2e (
	__in  char clk,
	__in  char rising_edge,
	__in  char rst,
	__in  char alu1_rs_d[3],
	__out char alu1_rs_e[3]
	);

void
dff_alu1_issue_d2e (
	__in  char clk,
	__in  char rising_edge,
	__in  char rst,
	__in  char alu1_issue_d[1],
	__out char alu1_issue_e[1]
	);

void
dff_alu1_op_d2e (
	__in  char clk,
	__in  char rising_edge,
	__in  char rst,
	__in  char alu1_op_d[4],
	__out char alu1_op_e[4]
	);

void
dff_alu1_rj_d2e (
	__in  char clk,
	__in  char rising_edge,
	__in  char rst,
	__in  char alu1_rj_d[32],
	__out char alu1_rj_e[32]
	);

void
dff_alu1_rk_d2e (
	__in  char clk,
	__in  char rising_edge,
	__in  char rst,
	__in  char alu1_rk_d[32],
	__out char alu1_rk_e[32]
	);

void
dff_alu1_rob_d2e (
	__in  char clk,
	__in  char rising_edge,
	__in  char rst,
	__in  char alu1_rob_d[3],
	__out char alu1_rob_e[3]
	);



void
dff_alu0_rs_e2w (
	__in  char clk,
	__in  char rising_edge,
	__in  char rst,
	__in  char alu0_rs_e[3],
	__out char alu0_rs_w[3]
	);

void
dff_alu0_issue_e2w (
	__in  char clk,
	__in  char rising_edge,
	__in  char rst,
	__in  char alu0_issue_e[1],
	__out char alu0_issue_w[1]
	);

void
dff_alu0_result_e2w (
	__in  char clk,
	__in  char rising_edge,
	__in  char rst,
	__in  char alu0_result_e[32],
	__out char alu0_result_w[32]
	);

void
dff_alu0_rob_e2w (
	__in  char clk,
	__in  char rising_edge,
	__in  char rst,
	__in  char alu0_rob_e[3],
	__out char alu0_rob_w[3]
	);

void
dff_alu1_rs_e2w (
	__in  char clk,
	__in  char rising_edge,
	__in  char rst,
	__in  char alu1_rs_e[3],
	__out char alu1_rs_w[3]
	);
void
dff_alu1_issue_e2w (
	__in  char clk,
	__in  char rising_edge,
	__in  char rst,
	__in  char alu1_issue_e[1],
	__out char alu1_issue_w[1]
	);

void
dff_alu1_result_e2w (
	__in  char clk,
	__in  char rising_edge,
	__in  char rst,
	__in  char alu1_result_e[32],
	__out char alu1_result_w[32]
	);

void
dff_alu1_rob_e2w (
	__in  char clk,
	__in  char rising_edge,
	__in  char rst,
	__in  char alu1_rob_e[3],
	__out char alu1_rob_w[3]
	);







void
dff_alu0_rs_w2c (
	__in  char clk,
	__in  char rising_edge,
	__in  char rst,
	__in  char alu0_rs_w[3],
	__out char alu0_rs_c[3]
	);

void
dff_alu0_issue_w2c (
	__in  char clk,
	__in  char rising_edge,
	__in  char rst,
	__in  char alu0_issue_w[1],
	__out char alu0_issue_c[1]
	);

void
dff_alu1_rs_w2c (
	__in  char clk,
	__in  char rising_edge,
	__in  char rst,
	__in  char alu1_rs_w[3],
	__out char alu1_rs_c[3]
	);

void
dff_alu1_issue_w2c (
	__in  char clk,
	__in  char rising_edge,
	__in  char rst,
	__in  char alu1_issue_w[1],
	__out char alu1_issue_c[1]
	);

#endif
