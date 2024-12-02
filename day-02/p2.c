#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool
isok(long long int *list, size_t nelems, size_t skip)
{
	bool negdiff = false;
	bool posdiff = false;
	bool baddiff = false;
	
	int i = (skip == 0) ? 2 : 1;
	for (; i < nelems; i++) {
		if (i == skip) continue;
		long long int this = list[i];
		long long int prev = list[(i - 1 == skip) ? i - 2 : i - 1];
		long long int diff = this - prev;
		if (diff < 0) negdiff = true;
		if (diff > 0) posdiff = true;
		if (diff < -3 || diff == 0 || diff > 3) baddiff = true;
	}

	return (!(posdiff && negdiff) && !baddiff);
}

int
main(int argc, char **argv)
{
	long long int sol = 0;
	char scanbuf[128] = {0};
	while (fgets(scanbuf, sizeof(scanbuf), stdin) != NULL) {
		char *cursor = scanbuf;
		long long int nums[128] = {0};
		size_t nelems = 0;

		long long int thisnum = 0;
		while (*cursor != '\0') {
			/*
			 * Oh my fucking god. Why is strtoll so bad. It made more sense to just 
			 * roll out my own int parser this time. BAD STL!
			 */
			if (*cursor == ' ' || *cursor == '\n') {
				nums[nelems] = thisnum;
				nelems += 1;
				thisnum = 0;
			} else {
				thisnum *= 10;
				thisnum += (*cursor) & 15;
			}
			cursor++;
		}

		bool ok = false;
		for (int i = 0; i < nelems; i++) {
			if (isok(nums, nelems, i)) ok = true;
		}
		if (ok) sol += 1;

		memset(scanbuf, 0, 128);
		memset(nums, 0, 128 * sizeof(long long int));
	}
	printf("%lld\n", sol);
}
