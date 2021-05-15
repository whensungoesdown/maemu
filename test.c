#include <stdio.h>
#include <string.h>
#include "defines.h"
#include "helper.h"
#include "ram_2port.h"
#include "rf.h"

int test_opBit (void)
{
	int n = 0;

	n = setBit(n, 0);

	if (0x1 != n)
	{
		printf("test_opBit set bit 0, result 0x%x\n", n);
		return -1;
	}

	return 0;
}

int test_char32bits2int(void)
{
	int output = 0;
	char input1[32] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
	char input2[32] = {0};
	char input3[32] = {0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1};
	

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
	if (0xaaaaaa0a != output)
	{
		printf("test_char32bits2int input 01010....010101, should return int 0xaaaaaa0a, result 0x%x\n", output);
		return -1;
	}

	return 0;
}


int test_int2char32bits(void)
{
	char output[32] = {0};

	char tmp1[32] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
	char tmp2[32] = {0};
	char tmp3[32] = {0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1};
	

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

	int2char32bits(0xaaaaaa0a, output);
	if (0 != memcmp(output, tmp3, 32))
	{
		printf("test_int2char32bits input 0x55555555, should return char[32] 0101 0000 ... 0101, result:\n");
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
	char data_b[32] = {0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1};

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
	// write 0xaaaaaaa0 to memory+8
	//

	nAddr_b = 0x8;	
	int2char32bits(nAddr_b, address_b);
	ram_2port(address_a, address_b, 1, data_a, data_b, 0, 1, q_a, q_b);

	// read
	ram_2port(address_a, address_b, 1, data_a, data_b, 0, 0, q_a, q_b);
	char32bits2int(q_b, &nQ_b);
	if (0xaaaaaaa0 != nQ_b)
	{
		printf("test_ram_2port first write 0xaaaaaaa0 to address 0x8, then read it out\n");
		printf("returns: 0x%x\n", nQ_b);
		return -1;
	}

	return 0;
}

int test_rf (void)
{
	int nRs1_idx = 0;
	int nRs2_idx = 0;
	char rs1_idx[5] = {0};
	char rs2_idx[5] = {0};
	int nRs1_data = 0;
	int nRs2_data = 0;
	char rs1_data[32] = {0};
	char rs2_data[32] = {0};

	int nRd_idx = 0;
	char rd_idx[5] = {0};
	int nRd_data = 0;
	char rd_data[32] = {0};

	// write 0xaaaaaaaa to reg[1]
	nRd_idx = 1;
	int2charnbits(nRd_idx, rd_idx, 5);
	print_charnbits(rd_idx, 5);

	nRd_data = 0xaaaaaaaa;
	int2char32bits(nRd_data, rd_data);

	rf(
		rs1_idx, 
		rs2_idx,
		rs1_data, 
		rs2_data,
		1, // rd_wen
		rd_idx, 
		rd_data,
		1, // clk
		0  // rst
	  );

	// write 0xbbbbbbbb to reg[31]
	nRd_idx = 31;
	int2charnbits(nRd_idx, rd_idx, 5);
	print_charnbits(rd_idx, 5);

	nRd_data = 0xbbbbbbbb;
	int2char32bits(nRd_data, rd_data);

	rf(
		rs1_idx, 
		rs2_idx,
		rs1_data, 
		rs2_data,
		1, // rd_wen
		rd_idx, 
		rd_data,
		1, // clk
		0  // rst
	  );


	// read reg[1] reg[31]
	nRs1_idx = 1;
	int2charnbits(nRs1_idx, rs1_idx, 5);
	nRs2_idx = 31;
	int2charnbits(nRs2_idx, rs2_idx, 5);

	rf(
		rs1_idx,
		rs2_idx,
		rs1_data,
		rs2_data,
		0, // rd_wen
		rd_idx, 
		rd_data,
		1, // clk
		0  // rst
	  );


	// check result
	char32bits2int(rs1_data, &nRs1_data);
	char32bits2int(rs2_data, &nRs2_data);


	if (0xaaaaaaaa != nRs1_data || 0xbbbbbbbb != nRs2_data)
	{
		printf("rf read reg[1] reg[31]\n");
		printf("returns 0x%x, 0x%x\n", nRs1_data, nRs2_data);
		return -1;
	}

	return 0;
}

int main(void)
{
	int ret = 0;

	printf("unit tests:\n");

	ret = test_opBit();
	if (0 != ret)
	{
		printf("test_opBit() failed!\n");
	}
	else
	{
		printf("test_opBit() success!\n");
	}

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


	ret = test_rf();
	if (0 != ret)
	{
		printf("test_rf() failed!\n");
	}
	else
	{
		printf("test_rf() success!\n");
	}



	printf("end.\n\n");


	return 0;
}
