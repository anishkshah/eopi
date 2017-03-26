#include <stdio.h>
#include <stdlib.h>

#define max(a, b) ((a > b) ? a : b)

/* Kadanes Algorithm */
int max_subarray(int *input, int size)
{
	int i = 0;
	int max_current = input[0];
	int max_subarray = input[0];

	for (i = 0; i < size; ++i)
	{
		max_current = max(input[i], max_current + input[i]);
		max_subarray = max(max_current, max_subarray);
	}
	return max_subarray;
}


int main(int argc, char const *argv[])
{
	int a[] = {1, 2, 3, 4, 5, 6};
	int b[] = {6, 5, 4, 3, 2, 1};
	int c[] = {-6, -5, -3, -4, -2, -1};
	int d[] = {-6, -5, -3, 4, 2, -1};

	printf("Max of a %d\n", max_subarray(a, 6));
	printf("Max of b %d\n", max_subarray(b, 6));
	printf("Max of c %d\n", max_subarray(c, 6));
	printf("Max of d %d\n", max_subarray(d, 6));
	return 0;
}