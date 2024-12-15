#include <stdio.h>
#include <string.h>

struct dvec2 {
	int x, y;
};

size_t
get_linelen(const char *);

struct dvec2
do_move(int, struct dvec2);

void
debug_display_grid(void);

char grid[1024][1024] = {0};
size_t xlen = 0;
size_t ylen = 0;

void
debug_display_grid(void)
{
	for (int i = 0; i < ylen; i++)
		printf("%s\n", grid[i]);
}

size_t
get_linelen(const char *input)
{
	size_t out = 0;
	while (input[++out] != '\n');
	return out;
}

struct dvec2
do_move(int dir, struct dvec2 t)
{
	struct dvec2 d = t;

	if (dir == '^')
		d.y -= 1;
	else if (dir == 'v')
		d.y += 1;
	else if (dir == '<')
		d.x -= 1;
	else if (dir == '>')
		d.x += 1;

	if (grid[d.y][d.x] == 'O')
		do_move(dir, d);
	
	if (grid[d.y][d.x] == '.') {
		char old = grid[t.y][t.x];
		char new = grid[d.y][d.x];
		grid[d.y][d.x] = old;
		grid[t.y][t.x] = new;
		return d;
	}
	
	return t;
}

int
main(int argc, char **argv)
{
	char scanbuf[1024] = {0};
	struct dvec2 robot_pos = { .x = 0, .y = 0 };
	while (fgets(scanbuf, sizeof scanbuf, stdin)) {
		/* In this case, we know we should start interpreting lines
		   as instructions */
		if (*scanbuf == '\n')
			break;
		xlen = get_linelen(scanbuf);

		struct dvec2 maybe_rpos = { .x = 0, .y = 0 };
		if (robot_pos.x == 0) {
			for (int x = 0; x < xlen; x++) {
				if (scanbuf[x] == '@') {
					robot_pos = (struct dvec2) {
						.x = x,
						.y = ylen
					};
				}
			}
		}
		
		memcpy(grid[ylen++], scanbuf, xlen);
	}
	
	int dir;
	while ((dir = fgetc(stdin)) != EOF) {
		if (dir == '\n')
			continue;

		/* putc(dir, stdout); */
		robot_pos = do_move(dir, robot_pos);
		/* debug_display_grid(); */
	}

	long long int sol = 0;

	for (int y = 0; y < ylen; y++) {
		for (int x = 0; x < xlen; x++) {
			if (grid[y][x] == 'O')
				sol += 100 * y + x;
		}
	}
	printf("%lld\n", sol);
}
