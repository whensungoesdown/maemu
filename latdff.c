#include <stdio.h>
#include <string.h>
#include "defines.h"
#include "helper.h"

//
// all the latch and dff go here
//

void
pc_lat (
	__in  char pc_ena[1],
	__in  char pc_next[32],
	__out char q[32]
       )
{
	static char pc_reg[32] = {0};
	int nPcNext = 0;
	int nPcReg = 0;

	if (1 == pc_ena[0])
	{
		char32bits2int(pc_next, &nPcNext);
		int2char32bits(nPcNext, pc_reg);
	}

	char32bits2int(pc_reg, &nPcReg);
	int2char32bits(nPcReg, q);

	//PRINTF("pc_lat: pc_reg 0x%x\n", nPcReg);
}

void
dff_instr_f2d (
	__in  char clk,
	__in  char rising_edge,
	__in  char rst,
	__in  char instr_f[32],
	__out char instr_d[32]
	)
{
	static char instr_reg[32] = {0};

	if (0 == clk || 0 == rising_edge) return; // regester write only works at the rising edge

	memcpy(instr_reg, instr_f, 32);
	memcpy(instr_d, instr_reg, 32);
}

// later, ALU should has a instruciton queue
void
dff_alu0_rs_d2e (
	__in  char clk,
	__in  char rising_edge,
	__in  char rst,
	__in  char alu0_rs_d[3],
	__out char alu0_rs_e[3]
	)
{
	static char alu0_rs_reg[3] = {0};

	if (0 == clk || 0 == rising_edge) return; // regester write only works at the rising edge

	memcpy(alu0_rs_reg, alu0_rs_d, 3);
	memcpy(alu0_rs_e, alu0_rs_reg, 3);

	return;
}

void
dff_alu0_issue_d2e (
	__in  char clk,
	__in  char rising_edge,
	__in  char rst,
	__in  char alu0_issue_d[1],
	__out char alu0_issue_e[1]
	)
{
	static char alu0_issue_reg[1] = {0};

	if (0 == clk || 0 == rising_edge) return; // regester write only works at the rising edge

	memcpy(alu0_issue_reg, alu0_issue_d, 1);
	memcpy(alu0_issue_e, alu0_issue_reg, 1);

	return;
}

void
dff_alu0_op_d2e (
	__in  char clk,
	__in  char rising_edge,
	__in  char rst,
	__in  char alu0_op_d[4],
	__out char alu0_op_e[4]
	)
{
	static char alu0_op_reg[4] = {0};

	if (0 == clk || 0 == rising_edge) return; // regester write only works at the rising edge

	memcpy(alu0_op_reg, alu0_op_d, 4);
	memcpy(alu0_op_e, alu0_op_reg, 4);

	return;
}

void
dff_alu0_rj_d2e (
	__in  char clk,
	__in  char rising_edge,
	__in  char rst,
	__in  char alu0_rj_d[32],
	__out char alu0_rj_e[32]
	)
{
	static char alu0_rj_reg[32] = {0};

	if (0 == clk || 0 == rising_edge) return; // regester write only works at the rising edge

	memcpy(alu0_rj_reg, alu0_rj_d, 32);
	memcpy(alu0_rj_e, alu0_rj_reg, 32);

	return;
}

void
dff_alu0_rk_d2e (
	__in  char clk,
	__in  char rising_edge,
	__in  char rst,
	__in  char alu0_rk_d[32],
	__out char alu0_rk_e[32]
	)
{
	static char alu0_rk_reg[32] = {0};

	if (0 == clk || 0 == rising_edge) return; // regester write only works at the rising edge

	memcpy(alu0_rk_reg, alu0_rk_d, 32);
	memcpy(alu0_rk_e, alu0_rk_reg, 32);

	return;
}

void
dff_alu0_rob_d2e (
	__in  char clk,
	__in  char rising_edge,
	__in  char rst,
	__in  char alu0_rob_d[3],
	__out char alu0_rob_e[3]
	)
{
	static char alu0_rob_reg[3] = {0};

	if (0 == clk || 0 == rising_edge) return; // regester write only works at the rising edge

	memcpy(alu0_rob_reg, alu0_rob_d, 3);
	memcpy(alu0_rob_e, alu0_rob_reg, 3);

	return;
}


void
dff_alu1_rs_d2e (
	__in  char clk,
	__in  char rising_edge,
	__in  char rst,
	__in  char alu1_rs_d[3],
	__out char alu1_rs_e[3]
	)
{
	static char alu1_rs_reg[3] = {0};

	if (0 == clk || 0 == rising_edge) return; // regester write only works at the rising edge

	memcpy(alu1_rs_reg, alu1_rs_d, 3);
	memcpy(alu1_rs_e, alu1_rs_reg, 3);

	return;
}

void
dff_alu1_issue_d2e (
	__in  char clk,
	__in  char rising_edge,
	__in  char rst,
	__in  char alu1_issue_d[1],
	__out char alu1_issue_e[1]
	)
{
	static char alu1_issue_reg[1] = {0};

	if (0 == clk || 0 == rising_edge) return; // regester write only works at the rising edge

	memcpy(alu1_issue_reg, alu1_issue_d, 1);
	memcpy(alu1_issue_e, alu1_issue_reg, 1);

	return;
}

void
dff_alu1_op_d2e (
	__in  char clk,
	__in  char rising_edge,
	__in  char rst,
	__in  char alu1_op_d[4],
	__out char alu1_op_e[4]
	)
{
	static char alu1_op_reg[4] = {0};

	if (0 == clk || 0 == rising_edge) return; // regester write only works at the rising edge

	memcpy(alu1_op_reg, alu1_op_d, 4);
	memcpy(alu1_op_e, alu1_op_reg, 4);

	return;
}

void
dff_alu1_rj_d2e (
	__in  char clk,
	__in  char rising_edge,
	__in  char rst,
	__in  char alu1_rj_d[32],
	__out char alu1_rj_e[32]
	)
{
	static char alu1_rj_reg[32] = {0};

	if (0 == clk || 0 == rising_edge) return; // regester write only works at the rising edge

	memcpy(alu1_rj_reg, alu1_rj_d, 32);
	memcpy(alu1_rj_e, alu1_rj_reg, 32);

	return;
}

void
dff_alu1_rk_d2e (
	__in  char clk,
	__in  char rising_edge,
	__in  char rst,
	__in  char alu1_rk_d[32],
	__out char alu1_rk_e[32]
	)
{
	static char alu1_rk_reg[32] = {0};

	if (0 == clk || 0 == rising_edge) return; // regester write only works at the rising edge

	memcpy(alu1_rk_reg, alu1_rk_d, 32);
	memcpy(alu1_rk_e, alu1_rk_reg, 32);

	return;
}

void
dff_alu1_rob_d2e (
	__in  char clk,
	__in  char rising_edge,
	__in  char rst,
	__in  char alu1_rob_d[3],
	__out char alu1_rob_e[3]
	)
{
	static char alu1_rob_reg[3] = {0};

	if (0 == clk || 0 == rising_edge) return; // regester write only works at the rising edge

	memcpy(alu1_rob_reg, alu1_rob_d, 3);
	memcpy(alu1_rob_e, alu1_rob_reg, 3);

	return;
}




void
dff_alu0_rs_e2w (
	__in  char clk,
	__in  char rising_edge,
	__in  char rst,
	__in  char alu0_rs_e[3],
	__out char alu0_rs_w[3]
	)
{
	static char alu0_rs_e2w_reg[3] = {0};

	if (0 == clk || 0 == rising_edge) return; // regester write only works at the rising edge

	memcpy(alu0_rs_e2w_reg, alu0_rs_e, 3);
	memcpy(alu0_rs_w, alu0_rs_e2w_reg, 3);

	return;
}

void
dff_alu0_issue_e2w (
	__in  char clk,
	__in  char rising_edge,
	__in  char rst,
	__in  char alu0_issue_e[1],
	__out char alu0_issue_w[1]
	)
{
	static char alu0_issue_e2w_reg[1] = {0};

	if (0 == clk || 0 == rising_edge) return; // regester write only works at the rising edge

	memcpy(alu0_issue_e2w_reg, alu0_issue_e, 1);
	memcpy(alu0_issue_w, alu0_issue_e2w_reg, 1);

	return;
}

void
dff_alu0_result_e2w (
	__in  char clk,
	__in  char rising_edge,
	__in  char rst,
	__in  char alu0_result_e[32],
	__out char alu0_result_w[32]
	)
{
	static char alu0_result_e2w_reg[32] = {0};

	if (0 == clk || 0 == rising_edge) return; // regester write only works at the rising edge

	memcpy(alu0_result_e2w_reg, alu0_result_e, 32);
	memcpy(alu0_result_w, alu0_result_e2w_reg, 32);

	return;
}

void
dff_alu0_rob_e2w (
	__in  char clk,
	__in  char rising_edge,
	__in  char rst,
	__in  char alu0_rob_e[3],
	__out char alu0_rob_w[3]
	)
{
	static char alu0_rob_e2w_reg[3] = {0};

	if (0 == clk || 0 == rising_edge) return; // regester write only works at the rising edge

	memcpy(alu0_rob_e2w_reg, alu0_rob_e, 3);
	memcpy(alu0_rob_w, alu0_rob_e2w_reg, 3);

	return;
}


void
dff_alu1_rs_e2w (
	__in  char clk,
	__in  char rising_edge,
	__in  char rst,
	__in  char alu1_rs_e[3],
	__out char alu1_rs_w[3]
	)
{
	static char alu1_rs_e2w_reg[3] = {0};

	if (0 == clk || 0 == rising_edge) return; // regester write only works at the rising edge

	memcpy(alu1_rs_e2w_reg, alu1_rs_e, 3);
	memcpy(alu1_rs_w, alu1_rs_e2w_reg, 3);

	return;
}

void
dff_alu1_issue_e2w (
	__in  char clk,
	__in  char rising_edge,
	__in  char rst,
	__in  char alu1_issue_e[1],
	__out char alu1_issue_w[1]
	)
{
	static char alu1_issue_e2w_reg[1] = {0};

	if (0 == clk || 0 == rising_edge) return; // regester write only works at the rising edge

	memcpy(alu1_issue_e2w_reg, alu1_issue_e, 1);
	memcpy(alu1_issue_w, alu1_issue_e2w_reg, 1);

	return;
}

void
dff_alu1_result_e2w (
	__in  char clk,
	__in  char rising_edge,
	__in  char rst,
	__in  char alu1_result_e[32],
	__out char alu1_result_w[32]
	)
{
	static char alu1_result_e2w_reg[32] = {0};

	if (0 == clk || 0 == rising_edge) return; // regester write only works at the rising edge

	memcpy(alu1_result_e2w_reg, alu1_result_e, 32);
	memcpy(alu1_result_w, alu1_result_e2w_reg, 32);

	return;
}

void
dff_alu1_rob_e2w (
	__in  char clk,
	__in  char rising_edge,
	__in  char rst,
	__in  char alu1_rob_e[3],
	__out char alu1_rob_w[3]
	)
{
	static char alu1_rob_e2w_reg[3] = {0};

	if (0 == clk || 0 == rising_edge) return; // regester write only works at the rising edge

	memcpy(alu1_rob_e2w_reg, alu1_rob_e, 3);
	memcpy(alu1_rob_w, alu1_rob_e2w_reg, 3);

	return;
}






void
dff_alu0_rs_w2c (
	__in  char clk,
	__in  char rising_edge,
	__in  char rst,
	__in  char alu0_rs_w[3],
	__out char alu0_rs_c[3]
	)
{
	static char alu0_rs_w2c_reg[3] = {0};

	if (0 == clk || 0 == rising_edge) return; // regester write only works at the rising edge

	memcpy(alu0_rs_w2c_reg, alu0_rs_w, 3);
	memcpy(alu0_rs_c, alu0_rs_w2c_reg, 3);

	return;
}

void
dff_alu0_issue_w2c (
	__in  char clk,
	__in  char rising_edge,
	__in  char rst,
	__in  char alu0_issue_w[1],
	__out char alu0_issue_c[1]
	)
{
	static char alu0_issue_w2c_reg[1] = {0};

	if (0 == clk || 0 == rising_edge) return; // regester write only works at the rising edge

	memcpy(alu0_issue_w2c_reg, alu0_issue_w, 1);
	memcpy(alu0_issue_c, alu0_issue_w2c_reg, 1);

	return;
}

void
dff_alu1_rs_w2c (
	__in  char clk,
	__in  char rising_edge,
	__in  char rst,
	__in  char alu1_rs_w[3],
	__out char alu1_rs_c[3]
	)
{
	static char alu1_rs_w2c_reg[3] = {0};

	if (0 == clk || 0 == rising_edge) return; // regester write only works at the rising edge

	memcpy(alu1_rs_w2c_reg, alu1_rs_w, 3);
	memcpy(alu1_rs_c, alu1_rs_w2c_reg, 3);

	return;
}

void
dff_alu1_issue_w2c (
	__in  char clk,
	__in  char rising_edge,
	__in  char rst,
	__in  char alu1_issue_w[1],
	__out char alu1_issue_c[1]
	)
{
	static char alu1_issue_w2c_reg[1] = {0};

	if (0 == clk || 0 == rising_edge) return; // regester write only works at the rising edge

	memcpy(alu1_issue_w2c_reg, alu1_issue_w, 1);
	memcpy(alu1_issue_c, alu1_issue_w2c_reg, 1);

	return;
}
