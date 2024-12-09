#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define SKIP (-1)

char input[1024 * 1024] = {0};

long long int output[1024 * 1024] = {0};
size_t output_len = 0;

int
main(int argc, char **argv)
{
	fread(input, sizeof input, 1, stdin);

	/* Parse into a list of ints */
	char *cursor = input;
	size_t current_id = 0;
	bool isskip = true;
	while ('0' <= *cursor && *cursor <= '9') {
		isskip = !isskip;
		size_t amount = *cursor & 15;

		long long int setnum = (isskip) ? SKIP : current_id++;
		while (amount) {
			amount--;
			output[output_len++] = setnum;
		}
		cursor++;
	}

	/* defrag */
	size_t lhs_cursor = 0;
	size_t rhs_cursor = output_len - 1;

	while (true) {
		while (output[lhs_cursor] != SKIP) lhs_cursor++;
		while (output[rhs_cursor] == SKIP) rhs_cursor--;
		if (lhs_cursor > rhs_cursor) break;

		long long int tmp = output[lhs_cursor];
		output[lhs_cursor] = output[rhs_cursor];
		output[rhs_cursor] = tmp;
	}
	/* checksum */
	long long int sol = 0;
	long long int *solcursor = output;
	size_t i = 0;
	while (*solcursor != SKIP) sol += i++ * *solcursor++;

	printf("%lld\n", sol);
}
