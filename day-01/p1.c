#include <stdlib.h>
#include <stdio.h>

int
lli_cmp(const void *lhs, const void *rhs)
{
	return *(long long int*)lhs - *(long long int*)rhs;
}

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

	qsort(list_left, input_size, sizeof(long long int), lli_cmp);
	qsort(list_right, input_size, sizeof(long long int), lli_cmp);
	long long int sol = 0;
	for (size_t i = 0; i < input_size; i++) {
		long long int diff = list_left[i] - list_right[i];
		sol += (diff > 0) ? diff : -diff;
	}
	printf("%lld\n", sol);
}
