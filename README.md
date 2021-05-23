# maemu

add clk,the clock cycle can be customized
````````
#define HIGH_CYCLE      5
#define LOW_CYCLE       5
````````````````
r-----f_____r-----f_____r-----



update:

````````
#define HIGH_UNIT      2
#define LOW_UNIT       2
````````````````

Each clock cycle takes 4 units to simulate.

Now a cycle is as the following:

`````
--__--__--__ ...
`````

The sequential logic runs at the rising edge and the combinational logic runs at the next -.
This is to simulate the setup time for the dff.
Otherwise, the function calling order will affect the circuit simulation

