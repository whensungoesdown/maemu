#include <stdio.h>
#include <string.h>
#include "helper.h"
#include "ram_2port.h"

int test_char32bits2int(void)
{
	int output = 0;
	char input1[32] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
	char input2[32] = {0};
	char input3[32] = {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1};
	

	char32bits2int(input1, &output);
	if (0xffffffff != output)
	{
		printf("test_char32bits2int input 111....1111, should return int 0xffffffff, result 0x%x\n", output);
		return -1;
	}

	char32bits2int(input2, &output);
	if (0x0 != output)
	{
		printf("test_char32bits2int input 000....0000, should return int 0x00000000, result 0x%x\n", output);
		return -1;
	}

	char32bits2int(input3, &output);
	if (0x55555555 != output)
	{
		printf("test_char32bits2int input 01010....010101, should return int 0x55555555, result 0x%x\n", output);
		return -1;
	}

	return 0;
}


int test_int2char32bits(void)
{
	char output[32] = {0};

	char tmp1[32] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
	char tmp2[32] = {0};
	char tmp3[32] = {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1};
	

	int2char32bits(0xffffffff, output);
	if (0 != memcmp(output, tmp1, 32))
	{
		printf("test_int2char32bits input 0xffffffff, should return char[32] 11111... 1111, result:\n");
		print_char32bits(output);
		return -1;
	}

	int2char32bits(0x00000000, output);
	if (0 != memcmp(output, tmp2, 32))
	{
		printf("test_int2char32bits input 0x00000000, should return char[32] 000...00000, result:\n");
		print_char32bits(output);
		return -1;
	}

	int2char32bits(0x55555555, output);
	if (0 != memcmp(output, tmp3, 32))
	{
		printf("test_int2char32bits input 0x55555555, should return char[32] 0101...0101, result:\n");
		print_char32bits(output);
		return -1;
	}

	return 0;
}


int test_data[MEMORY_SIZE/4] = {0xAAAAAAAA, 0xBBBBBBBB, 0xCCCCCCCC, 0};

int test_ram_2port (void)
{

	int nAddr_a = 0;
	int nAddr_b = 4;

	char address_a[32] = {0};
	char address_b[32] = {0};

	int nData_a = 0;
	int nData_b = 0;

	char data_a[32] = {0};
	char data_b[32] = {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1};

	int nQ_a = 0;
	int nQ_b = 0;

	char q_a[32] = {0};
	char q_b[32] = {0};


	g_memory = test_data;

	int2char32bits(nAddr_a, address_a);
	int2char32bits(nAddr_b, address_b);

	ram_2port(address_a, address_b, 1, data_a, data_b, 0, 0, q_a, q_b);

	char32bits2int(q_a, &nQ_a);
	char32bits2int(q_b, &nQ_b);

	if (0xAAAAAAAA != nQ_a || 0xBBBBBBBB != nQ_b)
	{
		printf("test_ram_2port read address 0x0, address 0x4, should return 0xAAAAAAAA and 0xBBBBBBBB\n");
		printf("returns: 0x%x, 0x%x\n", nQ_a, nQ_b);
		return -1;
	}


	//
	// write 0x55555555 to memory+8
	//

	nAddr_b = 0x8;	
	int2char32bits(nAddr_b, address_b);
	ram_2port(address_a, address_b, 1, data_a, data_b, 0, 1, q_a, q_b);

	// read
	ram_2port(address_a, address_b, 1, data_a, data_b, 0, 0, q_a, q_b);
	char32bits2int(q_b, &nQ_b);
	if (0x55555555 != nQ_b)
	{
		printf("test_ram_2port first write 0x55555555 to address 0x8, then read it out\n");
		printf("returns: 0x%x\n", nQ_b);
		return -1;
	}

	return 0;
}

int main(void)
{
	int ret = 0;

	printf("unit tests:\n");

	ret = test_char32bits2int();
	if (0 != ret)
	{
		printf("test_char32bits2int() failed!\n");
	}
	else
	{
		printf("test_char32bits2int() success!\n");
	}

	ret = test_int2char32bits();
	if (0 != ret)
	{
		printf("test_int2char32bits() failed!\n");
	}
	else
	{
		printf("test_int2char32bits() success!\n");
	}

	ret = test_ram_2port();
	if (0 != ret)
	{
		printf("test_ram_2port() failed!\n");
	}
	else
	{
		printf("test_ram_2port() success!\n");
	}
	printf("end.\n\n");


	return 0;
}
