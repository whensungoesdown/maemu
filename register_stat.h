#ifndef _REGISTER_STAT_H_
#define _REGISTER_STAT_H_

void
register_stat (
//	__in  char valid[1],
//	__out char ready[1],

	__in  char rj_idx[5],
	__in  char rk_idx[5],
	__out char rj_busy[1],
	__out char rk_busy[1],
	__out char rj_reorder[3],
	__out char rk_reorder[3],

	__in  char rd_wen[1],
	__in  char rd_idx[5],
	__in  char rd_busy[1],
	__in  char rd_reorder[1]
	);

#endif
