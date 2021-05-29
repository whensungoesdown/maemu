#ifndef _RF_H_
#define _RF_H_

extern int* g_rf_data;
//extern int* g_rf_busy;
//extern int* g_rf_reorder;

void
rf (
	__input char rs1_idx[5],
	__input char rs2_idx[5],
	__output char rs1_data[32],
	__output char rs2_data[32],
//	__output char rs1_busy[1],
//	__output char rs2_busy[1],
//	__output char rs1_reorder[3],
//	__output char rs2_reorder[3],

	__input char rd_wen[1],
	__input char rd_idx[5],
	__input char rd_data[32],
//	__input char rd_busy[1],
//	__input char rd_reorder[3],

	__input char clk,
	__input char rising_edge,
	__input char rst
   );

#endif
