#include <stdio.h>
#include "defines.h"
#include "helper.h"

void
adder (
	__in  char a[32],
	__in  char b[32],
	__out char q[32]
      )
{
	int nA = 0;
	int nB = 0;
	int nQ = 0;

	char32bits2int(a, &nA);
	char32bits2int(b, &nB);

	nQ = nA + nB;

	int2char32bits(nQ, q);

	return;
}
