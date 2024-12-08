#include <stdio.h>
#include <string.h>
#include <stdint.h>

static inline size_t
get_linelen(const char *input);

static inline void
add_antis(size_t x, size_t y);

/*           y,    x */
uint8_t grid[1024][1024] = {0};
size_t grid_ylen = 0;
size_t grid_xlen = 0;

/* Antinodes may occur at the same location as regular nodes, so we store them
 * on a different layer. */
/*                y,    x */
uint8_t anti_grid[1024][1024] = {0};

static inline size_t
get_linelen(const char *input)
{
	size_t out = 0;
	while (input[++out] != '\n');
	return out;
}

static inline void
add_antis(size_t o_x, size_t o_y)
{
	uint8_t o_symbol = grid[o_y][o_x];
	if (o_symbol == '.') return;

	for (size_t x = 0; x < grid_xlen; x++) {
		for (size_t y = 0; y < grid_ylen; y++) {
			/* No line with self */
			if (x == o_x && y == o_y) return;
			uint8_t symbol = grid[y][x];
			if (symbol != o_symbol) continue;

			anti_grid[y][x] = '#';
			anti_grid[o_y][o_x] = '#';

			size_t xdiff = o_x - x;
			size_t ydiff = o_y - y;
			size_t xdiff_original = xdiff;
			size_t ydiff_original = ydiff;

			int added = 2;
			while (added != 0) {
				added = 0;
				/* Try from o_x */
				if (o_y > 0 && o_x > 0 
				    && anti_grid[o_y + ydiff][o_x + xdiff]
				    != '\0') {
					added++;
					anti_grid[o_y + ydiff][o_x + xdiff] = '#';
				}
				/* Try from o_y */
				if (y > 0 && x > 0 
				    && anti_grid[y - ydiff][x - xdiff]
				    != '\0') {
					added++;
					anti_grid[y - ydiff][x - xdiff] = '#';
				}
				xdiff += xdiff_original;
				ydiff += ydiff_original;
			}
		}
	}
	return;
}

int
main(int argc, char **argv)
{
	char scanbuf[256] = {0};
	while (fgets(scanbuf, sizeof scanbuf, stdin)) {
		if (!grid_xlen) grid_xlen = get_linelen(scanbuf);
		memcpy(grid[grid_ylen], scanbuf, grid_xlen);
		grid_ylen++;
		memset(scanbuf, 0, sizeof scanbuf);
	}
	memcpy(anti_grid, grid, sizeof grid); /* Not needed, but useful for 
	                                       * debugging */
	for (int x = 0; x < grid_xlen; x++) {
		for (int y = 0; y < grid_ylen; y++) add_antis(x, y);
	}
	long long int sol = 0;

	for (int x = 0; x < grid_xlen; x++) {
		for (int y = 0; y < grid_ylen; y++) {
			if (anti_grid[y][x] == '#') sol += 1;
		}
	}
	printf("%llu\n", sol);
}
