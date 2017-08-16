#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void permute(char *input, char *out, int *len, int *used)
{
	if(len == 5)
	{
		printf("out\n");
	}


}

int main(int argc, char const *argv[])
{
	char test[] = "hello";
	int len = 0;
	int used[5];
	char out[5];

	memset(used, 0 ,sizeof(used));
	memset(out, 0 ,sizeof(out));

	permute(test, out, &len, used);

	return 0;
}