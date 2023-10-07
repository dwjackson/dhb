#include <stdlib.h>
#include <stdio.h>

static void printb(int n);

int main(int argc, char *argv[])
{
	char *input;
	int n;

	if (argc < 2) {
		exit(EXIT_FAILURE);
	}

	input = argv[1];

	n = atoi(input);

	printf("\t%d\t0x%X\t", n, n);
	printb(n);
	printf("\n");

	return 0;
}

static void printb(int n)
{
	size_t i;
	size_t intsize;
	unsigned int m; /* Mask */
	int leading_zeros = 1; /* Do not print leading zeros */

	if (n < 256) {
		intsize = 8;
	} else if (n < 65536) {
		intsize = 16;
	} else {
		intsize = sizeof(int) * 8;
	}

	m = 1 << (intsize - 1);

	printf("0b");

	for (i = 0; i < intsize; i++) {
		if (m & n) {
			leading_zeros = 0;
			printf("1");
		} else if (!leading_zeros) {
			printf("0");
		}

		m >>= 1;
	}
}
