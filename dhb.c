#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define DEC 1
#define HEX 2
#define BIN 3

#define PREFIX_LEN 2
#define HEX_DIGITS_PER_BYTE 2
#define HEX_MAX_LEN (sizeof(int) * HEX_DIGITS_PER_BYTE)

static void lowercase(char *s);
static int readhex(char *s, size_t len, int *n);
static int readbin(char *s, size_t len, int *n);
static void printb(int n);

int main(int argc, char *argv[])
{
	char *input;
	size_t input_len;
	int n = 0;
	int base = DEC;

	if (argc < 2) {
		exit(EXIT_FAILURE);
	}

	input = argv[1];
	lowercase(input);
	input_len = strlen(input);

	if (input_len > PREFIX_LEN) {
		if (input[0] == '0' && input[1] == 'x') {
			base = HEX;
		} else if (input[0] == '0' && input[1] == 'b') {
			base = BIN;
		}
	}

	switch (base) {
		case DEC:
			n = atoi(input);
			break;
		case HEX:
			if (readhex(input, input_len, &n) != 0) {
				exit(EXIT_FAILURE);
			}
			break;
		case BIN:
			if (readbin(input, input_len, &n) != 0) {
				exit(EXIT_FAILURE);
			}
			break;
		default:
			fprintf(stderr, "Invalid number\n");
			exit(EXIT_FAILURE);
			break;
	}

	printf("\t%d\t0x%X\t", n, n);
	printb(n);
	printf("\n");

	return 0;
}

static void lowercase(char *s)
{
	while (*s != '\0') {
		*s = tolower(*s);
		s++;
	}
}

static int readhex(char *s, size_t len, int *n)
{
	int r;
	if (len - PREFIX_LEN > HEX_MAX_LEN) {
		return -1;
	}
	r = sscanf(s, "0x%x", n);
	if (r != 1) {
		return -1;
	}
	return 0;
}

static int readbin(char *s, size_t len, int *n)
{
	size_t i;
	char ch;
	int out = 0x0;
	size_t numlen = len - PREFIX_LEN;
	size_t bitidx = 0;

	for (i = PREFIX_LEN; i < len; i++) {
		ch = s[i];
		if (ch == '1') {
			out = out | (0x1 << (numlen - bitidx - 1));
		} else if (ch == '0') {
			/* Nothing to do */
		} else {
			return -1;
		}
		bitidx++;
	}

	*n = out;
	return 0;
}

static void printb(int n)
{
	size_t i;
	size_t intsize;
	unsigned int m; /* Mask */
	int leading_zeros = 1; /* Do not print leading zeros */

	if (n == 0) {
		printf("0b0");
		return;
	}

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
