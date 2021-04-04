#include <stdio.h>
#include <assert.h>

// Function to set the kth bit of n
int setBit(int n, int k)
{
    return (n | (1 << (k - 1)));
}
  
// Function to clear the kth bit of n
int clearBit(int n, int k)
{
    return (n & (~(1 << (k - 1))));
}
  
// Function to toggle the kth bit of n
int toggleBit(int n, int k)
{
    return (n ^ (1 << (k - 1)));
}

// Function to get the kth bit of n, 0 or 1
int getBit(int n, int k)
{
	int result = 0;

	result = (n & (1 << (k - 1)));

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
