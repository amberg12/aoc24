#include <stdio.h>
#include <string.h>

size_t
get_linelen(const char *input);

void
scan_trail(size_t x, size_t y, char curr);

char input[1024 * 1024];

/* Trails should be made out of '0'-'9' or '#'.
 * '#' is like a 9, but already visited.
 * */
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
		trails[y][x] = '#';
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
			/* There should probably be a smarter way of unsetting
			 * stuff, but this works. Anyway, it only takes ~20ms 
			 * on my thinkpad. */
			for (size_t x1 = 0; x1 < trail_xlen; x1++) {
				for (size_t y1 = 0; y1 < trail_ylen; y1++) {
					if (trails[y1][x1] == '#') trails[y1][x1] = '9';
				}
			}
		}
	}
	printf("%lld\n", sol);
}
