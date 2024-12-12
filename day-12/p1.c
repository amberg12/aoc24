#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

struct reg_info {
	long long int area;
	long long int perim;
};

size_t
get_linelen(const char *);

struct reg_info
get_reg_info(size_t x, size_t y, char id);

char input[1024][1024] = {0};
bool searched[1024][1024] = {0};
size_t xlen = 0;
size_t ylen = 0;

size_t
get_linelen(const char *input)
{
	size_t out = 0;
	while (input[++out] != '\n');
	return out;
}

struct reg_info
get_reg_info(size_t x, size_t y, char id)
{
	if (id == '\n' || id == '\0' || (searched[y][x] && id == input[y][x]))
		return (struct reg_info) { .area = 0, .perim = 0 };

	if (input[y][x] != id || x > xlen || y > ylen)
		return (struct reg_info) { .area = 0, .perim = 1 };

	searched[y][x] = true;
	struct reg_info a = get_reg_info(x + 1, y, id);
	struct reg_info b = get_reg_info(x - 1, y, id);
	struct reg_info c = get_reg_info(x, y + 1, id);
	struct reg_info d = get_reg_info(x, y - 1, id);

	return (struct reg_info) {
		.area = 1 + a.area + b.area + c.area + d.area,
		.perim = a.perim + b.perim + c.perim + d.perim,
	};
}

int
main(int argc, char **argv)
{

	while (fgets(input[ylen++], 1024, stdin));
	xlen = get_linelen(input[0]);

	long long int sol = 0;
	for (int y = 0; y < ylen; y++) {
		for (int x = 0; x < xlen; x++) {
			struct reg_info r = get_reg_info(x, y, input[y][x]);
			sol += r.area * r.perim;
		}
	}
	printf("%lld\n", sol);
}
