#ifndef _RF_H_
#define _RF_H_

extern int* g_rf_data;

void
rf (
	__input char rs1_idx[5],
	__input char rs2_idx[5],
	__output char rs1_data[32],
	__output char rs2_data[32],

	__input char rd_wen,
	__input char rd_idx[5],
	__input char rd_data[32],

	__input char clk,
	__input char rst
   );
#endif
