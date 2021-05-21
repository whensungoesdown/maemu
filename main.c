#include <stdio.h>
#include <assert.h>

// a char represents 1 bit

#define HIGH_UNIT	2
#define LOW_UNIT	2
#define RUN_UNITS	16


int top (char bit_clk, int b_rising_edge, int b_falling_edge);

int main (void)
{
	int high_cycle_count = 0;
	int low_cycle_count = 0;
	int b_rising_edge = 0;
	int b_falling_edge = 0;
	char bit_clk =0;

	int run_cycles = 0;

	
	printf("Microarchitecture emulator\n");

	// main loop

	// start with a rising edge
	b_rising_edge = 1;
	b_falling_edge = 0;
	bit_clk = 1;

	while (run_cycles < RUN_UNITS)
	{

		if (1 == bit_clk)
		{
			if (high_cycle_count++ < HIGH_UNIT)
			{
			}
			else
			{
				// high duty cycle runs out

				bit_clk = 0;
				b_falling_edge = 1;
				high_cycle_count = 0; // clear to 0
				continue;
			}
		}
		else if (0 == bit_clk)
		{
			if (low_cycle_count++ < LOW_UNIT)
			{
			}
			else
			{
				bit_clk = 1;
				b_rising_edge = 1;
				low_cycle_count = 0;
				continue;
			}
		}
		else
		{
			assert(0);
		}

		top(bit_clk, b_rising_edge, b_falling_edge);



		// rising and falling edge only last for one cycle
		if (1 == b_rising_edge) b_rising_edge = 0;
		if (1 == b_falling_edge) b_falling_edge = 0;

		run_cycles++;
	}


	printf("\n\n");

	return 0;
}
