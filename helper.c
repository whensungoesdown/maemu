#include <stdio.h>
#include <assert.h>
#include "helper.h"


// Function to set the kth bit of n
int setBit(int n, int k)
{
    return (n | (1 << k));
}
  
// Function to clear the kth bit of n
int clearBit(int n, int k)
{
    return (n & (~(1 << k)));
}
  
// Function to toggle the kth bit of n
//int toggleBit(int n, int k)
//{
//    return (n ^ (1 << (k - 1)));
//}

// Function to get the kth bit of n, 0 or 1
int getBit(int n, int k)
{
	int result = 0;

	result = (n & (1 << k));

	return (result == 0? 0 : 1);
}

int char32bits2int (char input[], int* poutput)
{
	int result = 0;
	int i = 0;

	for (i = 0; i < 32; i++)
	{
		assert(input[i] == 0 || input[i] == 1);

		if (1 == input[i])
		{
			result = setBit(result, i);
		}
	}

	*poutput = result;

	return 0;
}

int return_int_char32bits(char input[])
{
	int ret = 0;

	char32bits2int(input, &ret);

	return ret;
}

int int2char32bits (int input, char output[])
{
	int i = 0;

	for (i = 0; i < 32; i++)
	{
		output[i] = getBit(input, i);
	}

	return 0;
}

int print_char32bits (char* input)
{
	int i = 0;

	for (i = 0; i < 32; i++)
	{
		printf("%d ", input[i]);
	}
	printf("\n");

	return 0;
}


int charnbits2int (char input[], int* poutput, int n)
{
	int result = 0;
	int i = 0;

	for (i = 0; i < n; i++)
	{
		assert(input[i] == 0 || input[i] == 1);

		if (1 == input[i])
		{
			result = setBit(result, i);
		}
	}

	*poutput = result;

	return 0;
}

int return_int_charnbits(char input[], int n)
{
	int ret = 0;

	charnbits2int(input, &ret, n);

	return ret;
}

int int2charnbits (int input, char output[], int n)
{
	int i = 0;

	for (i = 0; i < n; i++)
	{
		output[i] = getBit(input, i);
	}

	return 0;
}

int print_charnbits (char* input, int n)
{
	int i = 0;

	for (i = 0; i < n; i++)
	{
		PRINTF("%d ", input[i]);
	}
	PRINTF("\n");

	return 0;
}
