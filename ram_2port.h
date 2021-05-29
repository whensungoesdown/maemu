#ifndef _RAM_2PORT_H_
#define _RAM_2PORT_H_

#define MEMORY_SIZE 	2048

extern int* g_memory;

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
	);

#endif
