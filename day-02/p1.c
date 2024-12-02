#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int
main(int argc, char **argv)
{
	long long int sol = 0;
	char scanbuf[128] = {0};
	while (fgets(scanbuf, sizeof(scanbuf), stdin) != NULL) {
		char *cursor = scanbuf;
		long long int prev = -1;

		bool negdiff = false;
		bool posdiff = false;
		bool baddiff = false;

		while (*cursor) {
			char *tmp = NULL;
			long long int this = strtoll(cursor, &tmp, 10);
			
			if (prev >= 0) {
				long long int diff = this - prev;

				if (diff < 0) negdiff = true;
				if (diff > 0) posdiff = true;
				if (diff < -3 || diff == 0 || diff > 3) baddiff = true;
			}

			while (*cursor != ' ' && cursor) cursor++;
			cursor++;
			prev = this;
		}
		if (!(posdiff && negdiff) && !baddiff) sol += 1;
		/* This missing memset took like 30 mins to debug :sob: */
		memset(scanbuf, 0, 128);
	}
	printf("%lld\n", sol);
}
