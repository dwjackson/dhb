#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	char *input;
	int n;

	if (argc < 2) {
		exit(EXIT_FAILURE);
	}

	input = argv[1];

	n = atoi(input);

	printf("\t%d\t0x%X\n", n, n);

	return 0;
}
