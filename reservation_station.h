#ifndef _RESERVATION_STATION_H_
#define _RESERVATION_STATION_H_

void
reservation_station (
	//__in  char clk,
	//__in  char rising_edge,
	__in  char in_valid[1],
	__out char in_ready[1],

	__in  char instr[32],

	__in  char rj_busy[1],
	__in  char rj_data[32],
	__in  char rj_reorder[3],

	__in  char rk_busy[1],
	__in  char rk_data[32],
	__in  char rk_reorder[3],

	__in  char rob_idx[3],


	__out char alu0_issue_e[1],
	__out char alu0_op_e[4],
	__out char alu0_rj_e[32],
	__out char alu0_rk_e[32],
	__out char alu0_rob_e[3],


	__out char alu1_issue_e[1],
	__out char alu1_op_e[4],
	__out char alu1_rj_e[32],
	__out char alu1_rk_e[32],
	__out char alu1_rob_e[3]

	);

void display_reservation_station (void);

#endif
