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

	__in  char rob_idx[3]


//	__in  char busy[1],
//	__in  char dest[3],
//	__in  char op[20],
//	__in  char vj[32],
//	__in  char vk[32],
//	__in  char qj[32],
//	__in  char qk[32],
//	__in  char a[32],
//	__out char full[1]


//	__out char out_valid[1],
//	__in  char out_ready[1],
//
//	__out char rj[32],
//	__out char rk[32],
//	__out char rd_idx[5]
   );

void display_reservation_station (void);

#endif
