#ifndef _RAM_2PORT_H_
#define _RAM_2PORT_H_

#define MEMORY_SIZE 	2048

extern int* g_memory;

void
ram_2port (
	char address_a[32],
	char address_b[32],
	char clk,
	char data_a[32],
	char data_b[32],
	char wren_a,
	char wren_b,
	char q_a[32],
	char q_b[32]
	);
#endif
