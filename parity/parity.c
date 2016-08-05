#include <stdio.h>

int get_parity(unsigned long input)
{
	int set_bits = 0;
	int i = 0;

	while(input)
	{
		if(input & 1) set_bits++;
		input = input>>1;
		i++;
	}

	return set_bits;
}

int main()
{	
	int result = 0;
	unsigned long test1 = 0b11110000111;		// odd
	unsigned long test2 = 0b111100001111;		// even
	unsigned long test3 = 0; 					// even
	unsigned long test4 = 0xffffffff;			// even

	result = get_parity(test1);
	printf("Parity for test1: %ld is %d with bits %d\n", test1, result%2, result);
	
	result = get_parity(test2);
	printf("Parity for test1: %ld is %d with bits %d\n", test2, result%2, result);
	
	result = get_parity(test3);
	printf("Parity for test1: %ld is %d with bits %d\n", test3, result%2, result);
	
	result = get_parity(test4);
	printf("Parity for test1: %lx is %d with bits %d\n", test4, result%2, result);
	return 0;
}
