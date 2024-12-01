#include <stdlib.h>
#include <stdio.h>

/*
 * We give a capacity of 100000 since all of the numbers are a max of 5 digits.
 *
 * This means we can just use the integers as a key.
 */
static long long int map[100000] = {0};

int
main(int argc, char **argv)
{
	size_t input_size = 0;
	long long int *list_left  = calloc(2048, sizeof(int));
	long long int *list_right = calloc(2048, sizeof(int));
	char scanbuf[128] = {0};
	while (fgets(scanbuf, sizeof(scanbuf), stdin) != NULL) {
		/* Parse scanbuf */
		int i = 0;
		int j = 0;
		char leftnumstr[128] = {0};
		char rightnumstr[128] = {0};

		while (scanbuf[i] != ' ') {
			leftnumstr[i] = scanbuf[i];
			i++;
		}
		i += 3; /* Skip over the spaces. 3 is the correct, but 
			   hard-coded value */
		while (scanbuf[i]) {
			rightnumstr[j] = scanbuf[i];
			i++;
			j++;
		}
		char *tmp;
		list_left[input_size] = strtoll(leftnumstr, &tmp, 10);
		list_right[input_size] = strtoll(rightnumstr, &tmp, 10);
		input_size += 1;
	}

	long long int sol = 0;
	for (int i = 0; i < input_size; i++) {
		map[list_right[i]] += 1;
	}

	for (int i = 0; i < input_size; i++) {
		sol += list_left[i] * map[list_left[i]];
	}
	printf("%lld\n", sol);
}
