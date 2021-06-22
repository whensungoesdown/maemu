#include <stdio.h>
#include <string.h>
#include "defines.h"
#include "helper.h"

void alu0 (
	__in  char alu0_issue_e[1],
	__in  char alu0_op_e[4],
	__in  char alu0_rj_e[32],
	__in  char alu0_rk_e[32],
	__in  char alu0_rob_e[3],
	__out char alu0_result_w[32],
	__out char alu0_rob_w[3]
	)
{
	int nRj = 0;
	int nRk = 0;
	int nResult = 0;

	//
	// uty: bug
	//  only adder
	//
	if (1 == alu0_issue_e[0])
	{
		memcpy(alu0_rob_w, alu0_rob_e, 3);
		char32bits2int(alu0_rj_e, &nRj);
		char32bits2int(alu0_rk_e, &nRk);

		nResult = nRj + nRk;
		int2char32bits(nResult, alu0_result_w);
	}
	return;
}	


void alu1 (
	__in  char alu1_issue_e[1],
	__in  char alu1_op_e[4],
	__in  char alu1_rj_e[32],
	__in  char alu1_rk_e[32],
	__in  char alu1_rob_e[3],
	__out char alu1_result_w[32],
	__out char alu1_rob_w[3]
	)
{
	int nRj = 0;
	int nRk = 0;
	int nResult = 0;

	//
	// uty: bug
	//  only adder
	//
	if (1 == alu1_issue_e[0])
	{
		memcpy(alu1_rob_w, alu1_rob_e, 3);
		char32bits2int(alu1_rj_e, &nRj);
		char32bits2int(alu1_rk_e, &nRk);

		nResult = nRj + nRk;
		int2char32bits(nResult, alu1_result_w);
	}
	return;
}	
