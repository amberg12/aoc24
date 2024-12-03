#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define BIG_MEM_BLOCK_LEN (1024 * 1024 * 1024)

static long long int
check_mult_from(char *cursor);

static long long int
check_mult_from(char *cursor)
{
	long long int lhs = 0;
	long long int rhs = 0;

	if (memcmp(cursor, "mul(", 4) != 0) {
		return 0;
	}
	cursor += 4;

	bool fdig = false;
	while (isdigit(*cursor)) {
		lhs *= 10;
		lhs += *cursor & 15;
		++cursor;
		fdig = true;
	}

	if (*cursor != ',' || !fdig) {
		return 0;
	}

	cursor++;
	fdig = false;
	while (isdigit(*cursor)) {
		rhs *= 10;
		rhs += *cursor & 15;
		++cursor;
		fdig = true;
	}

	if (*cursor != ')' || !fdig) {
		return 0;
	}
	return lhs * rhs;
}

int
main(int argc, char **argv)
{
	long long int sol = 0;
	char *scanbuf = malloc(BIG_MEM_BLOCK_LEN);
	while (fgets(scanbuf, BIG_MEM_BLOCK_LEN, stdin)) {
		char *cursor = scanbuf;

		while (*cursor) {
			sol += check_mult_from(cursor++);
		}

		memset(scanbuf, 0, BIG_MEM_BLOCK_LEN);
	}

	printf("%lld\n", sol);
}
