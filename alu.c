#include <stdio.h>
#include <string.h>
#include "defines.h"
#include "helper.h"


void alu0 (
	__in  char alu0_issue_e[1],
	__in  char alu0_op_e[4],
	__in  char alu0_rj_e[32],
	__in  char alu0_rk_e[32],

	__out char alu0_result_e[32]
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
		char32bits2int(alu0_rj_e, &nRj);
		char32bits2int(alu0_rk_e, &nRk);

		nResult = nRj + nRk;
		//printf("!!!!! alu0 result 0x%x\n", nResult);
		int2char32bits(nResult, alu0_result_e);
	}

	return;
}	


void alu1 (
	__in  char alu1_issue_e[1],
	__in  char alu1_op_e[4],
	__in  char alu1_rj_e[32],
	__in  char alu1_rk_e[32],

	__out char alu1_result_e[32]
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
		char32bits2int(alu1_rj_e, &nRj);
		char32bits2int(alu1_rk_e, &nRk);

		nResult = nRj + nRk;
		int2char32bits(nResult, alu1_result_e);
	}

	return;
}	
