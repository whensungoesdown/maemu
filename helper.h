#ifndef _HELPER_H_
#define _HELPER_H_


//#undef _DEBUG
#define _DEBUG

#ifdef _DEBUG
//#define PRINTF(f_, ...) printf((f_), __VA_ARGS__)
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(f_, ...) do {} while(0)
#endif

int setBit(int n, int k);
int clearBit(int n, int k);
int getBit(int n, int k);

int char32bits2int (char input[], int* poutput);

int int2char32bits (int input, char output[]);

int print_char32bits (char* input);

int charnbits2int (char input[], int* poutput, int n);

int int2charnbits (int input, char output[], int n);

int print_charnbits (char* input, int n);
#endif
