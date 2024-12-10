/*
	This has to be the easiest part 2 yet. I had to reimplement a bug I
	found in part 1.
 */

#include <stdio.h>
#include <string.h>

size_t
get_linelen(const char *input);

void
scan_trail(size_t x, size_t y, char curr);

char input[1024 * 1024];

/*          y     x */
char trails[1024][1024];
size_t trail_xlen = 0;
size_t trail_ylen = 0;

long long int sol = 0;

size_t
get_linelen(const char *input)
{
	size_t out = 0;
	while (input[++out] != '\n');
	return out;
}

void
scan_trail(size_t x, size_t y, char curr)
{
	if (x < 0 || x >= trail_xlen) return;
	if (y < 0 || y >= trail_ylen) return;
	if (trails[y][x] != curr) return;

	if (trails[y][x] == '9') {
		sol++;
		return;
	}

	scan_trail(x + 1, y, curr + 1);
	scan_trail(x - 1, y, curr + 1);
	scan_trail(x, y + 1, curr + 1);
	scan_trail(x, y - 1, curr + 1);
}

int
main(int argc, char **argv)
{
	char scanbuf[256] = {0};

	while (fgets(scanbuf, sizeof scanbuf, stdin)) {
		trail_xlen = get_linelen(scanbuf);
		memcpy(trails[trail_ylen], scanbuf, trail_xlen);
		trail_ylen += 1;
		memset(scanbuf, 0, sizeof scanbuf);
	}

	for (size_t x = 0; x < trail_xlen; x++) {
		for (size_t y = 0; y < trail_ylen; y++) {
			scan_trail(x, y, '0');
		}
	}
	printf("%lld\n", sol);
}
