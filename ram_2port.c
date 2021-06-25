#include <stdio.h>
#include <assert.h>
#include "defines.h"
#include "helper.h"
#include "ram_2port.h"

//char data[MEMORY_SIZE/4][32] = {
//	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
//	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
//	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
//	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//
//};

// addi.w $2, $0, 15
// addi.w $3, $0, 271
// addi.w $3, $4, 271 
//int data[MEMORY_SIZE/4] = {0x02803c02, 0x02843c03, 0x02843c83, 0};

// add.w $3, $1, $2
// add.w $4, $0, $3
// add.w $5, $0, $1
int data[MEMORY_SIZE/4] = {0x00100823, 0x00100c04, 0x00100405, 0};

int* g_memory = data; 
int g_memory_size = MEMORY_SIZE;

void
ram_2port (
	__in  char address_a[32],
	__in  char address_b[32],
	__in  char clk,
	__in  char rising_edge,
	__in  char data_a[32],
	__in  char data_b[32],
	__in  char wen_a[1],
	__in  char wen_b[1],
	__out char q_a[32],
	__out char q_b[32]
	)
{
	int nAddr_a = 0;
	int nAddr_b = 0;

	int nData_a = 0;
	int nData_b = 0;

	int nQ_a = 0;
	int nQ_b = 0;


	if (0 == clk || 0 == rising_edge) return; // only works on the rising edge


	char32bits2int(address_a, &nAddr_a);	
	char32bits2int(address_b, &nAddr_b);	
	
	//PRINTF("ram_2port address_a 0x%x\n", nAddr_a);
	//PRINTF("ram_2port address_b 0x%x\n", nAddr_b);


	char32bits2int(data_a, &nData_a);
	char32bits2int(data_b, &nData_b);

	//PRINTF("ram_2port data_a 0x%x\n", nData_a);
	//PRINTF("ram_2port data_b 0x%x\n", nData_b);


	//char32bits2int(q_a, &nQ_a);	
	//char32bits2int(q_b, &nQ_b);	

	//PRINTF("ram_2port q_a 0x%x\n", nQ_a);
	//PRINTF("ram_2port q_b 0x%x\n", nQ_b);

	//PRINTF("ram_2port wen_a 0x%x\n", wen_a[0]);
	//PRINTF("ram_2port wen_b 0x%x\n", wen_b[0]);

	if (nAddr_a & 0x3)
	{
		PRINTF("address_a is not 4-byte aligned\n");
		//nAddr_a &= (~0x3);
	}


	if (nAddr_b & 0x3)
	{
		PRINTF("address_b is not 4-byte aligned\n");
		//nAddr_b &= (~0x3);
	}


	if (nAddr_a < g_memory_size)
	{
		nAddr_a = nAddr_a >> 2;

		if (wen_a[0]) 
		{
			g_memory[nAddr_a] = nData_a;
		}
		else
		{
			nQ_a = g_memory[nAddr_a];
			int2char32bits(nQ_a, q_a); 
			//printf("nAddr_a 0x%x, nQ_a 0x%x, g_memory[0] 0x%x\n", nAddr_a, nQ_a, g_memory[0]);
			//print_char32bits(q_a);
		}
	}
	else
	{
		// exceeds memory size
		assert(0);
	}

	if (nAddr_b < g_memory_size)
	{
		nAddr_b = nAddr_b >> 2;

		if (wen_b[0]) 
		{
			g_memory[nAddr_b] = nData_b;
		}
		else
		{
			nQ_b = g_memory[nAddr_b];
			int2char32bits(nQ_b, q_b); 
		}
	}
	else
	{
		// exceeds memory size
		assert(0);
	}


//	PRINTF("RAM\n");
//	if (0 == wen_a[0])
//	{
//		PRINTF("  port_a read 0x%x: 0x%x\n", nAddr_a * 4, nQ_a);
//	}
//	else
//	{
//		PRINTF("  port_a write 0x%x: 0x%x\n", nAddr_a * 4, nData_a);
//	}
//	if (0 == wen_b[0])
//	{
//		PRINTF("  port_b read 0x%x: 0x%x\n", nAddr_b * 4, nQ_b);
//	}
//	else
//	{
//		PRINTF("  port_b write 0x%x: 0x%x\n", nAddr_b * 4, nData_b);
//	}

	return;
}
