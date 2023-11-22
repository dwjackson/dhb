#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <stdbool.h>

#define DEC 1
#define HEX 2
#define BIN 3

#define PREFIX_LEN 2
#define HEX_DIGITS_PER_BYTE 2
#define HEX_MAX_LEN (sizeof(int) * HEX_DIGITS_PER_BYTE)

static void lowercase(char *s);
static int readhex(char *s, size_t len, unsigned long *n);
static int readbin(char *s, size_t len, long *n);
static void printb(long n);

static bool is_number(const char *s, int (*is_digit)(int));
static bool is_dec(const char *s);
static bool is_hex(const char *s);

int main(int argc, char *argv[])
{
	char *input;
	size_t input_len;
	long n = 0;
	int base = DEC;

	if (argc < 2) {
		fprintf(stderr, "USAGE: dhb [NUMBER]\n");
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
			if (!is_dec(input)) {
				fprintf(stderr, "Not a number\n");
				exit(EXIT_FAILURE);
			}
			errno = 0;
			n = strtol(input, NULL, 10);
			if (errno != 0) {
				perror("strtol");
				exit(EXIT_FAILURE);
			}
			break;
		case HEX:
			if (readhex(input, input_len, (unsigned long *)&n) != 0) {
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

	printf("\t%ld\t0x%lX\t", n, n);
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

static int readhex(char *s, size_t len, unsigned long *n)
{
	int r;
	char *hexnum = s + 2;
	if (len - PREFIX_LEN > HEX_MAX_LEN) {
		return -1;
	}

	if (!is_hex(hexnum)) {
		fprintf(stderr, "Not a hexadecimal number\n");
		return -1;
	}

	errno = 0;
	r = sscanf(s, "0x%lx", n);
	if (r == 1) {
		return 0;
	}
	if (errno != 0) {
		perror("sscanf");
	}
	return -1;
}

static int readbin(char *s, size_t len, long *n)
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
			fprintf(stderr, "Not a binary number\n");
			return -1;
		}
		bitidx++;
	}

	*n = out;
	return 0;
}

static void printb(long n)
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

static bool is_dec(const char *s)
{
	return is_number(s, isdigit);
}

static bool is_hex(const char *s)
{
	return is_number(s, isxdigit);
}

static bool is_number(const char *s, int (*is_digit)(int))
{
	for (; *s != '\0'; s++) {
		if (!is_digit(*s)) {
			return false;
		}
	}
	return true;
}
