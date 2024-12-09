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
	size_t rhs_cursor = output_len - 1;

	long long int prev_id = -1;
	while (true) {
		size_t lhs_cursor = 0;
		while (output[lhs_cursor] != SKIP) lhs_cursor++;
		while (output[rhs_cursor] == SKIP || output[rhs_cursor] == prev_id) rhs_cursor--;
		if (lhs_cursor > rhs_cursor) break;

		prev_id = output[rhs_cursor];
		long long int this_id = output[rhs_cursor];
	
		size_t tmp_rhs = rhs_cursor;
		size_t idlen = 0;
		while (output[tmp_rhs--] == this_id) idlen++;

		while (true) {
			size_t tmp_lhs = lhs_cursor;
			size_t freelen = 0;
			while (output[tmp_lhs++] == SKIP) freelen++;
			if (freelen >= idlen) {
				break;
			}

			if (tmp_lhs > tmp_rhs)
				goto loopend; /* This goto is quite silly! */

			lhs_cursor++;
		}
		
		while (output[rhs_cursor] == this_id) {
			long long int tmp = output[lhs_cursor];
			output[lhs_cursor] = output[rhs_cursor];
			output[rhs_cursor] = tmp;
			lhs_cursor++;
			rhs_cursor--;
			/*
			 * Small edge case when the swap is done directly
			 * adjacent to regions.
			 */
			if (lhs_cursor > rhs_cursor) break;
		}
	loopend:
		continue;
	}
	/* checksum */
	long long int sol = 0;
	long long int *solcursor = output;

	for (size_t i = 0; i < output_len; i++) {
		long long int maybe = output[i];
		if (maybe == SKIP) continue;
		sol += maybe * i;
	}
	printf("%llu\n", sol);
}
