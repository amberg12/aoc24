#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct dvec2 {
	int x, y;
};

size_t
get_linelen(const char *);

void
debug_display_grid(void);

struct dvec2
robot_move(int, struct dvec2);

void
box_move(int, struct dvec2);

bool
box_check_v(int, struct dvec2);

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
robot_move(int dir, struct dvec2 o)
{
	struct dvec2 d = o;
	if (dir == '^')
		d.y -= 1;
	else if (dir == 'v')
		d.y += 1;
	else if (dir == '>')
		d.x += 1;
	else if (dir == '<')
		d.x -= 1;

	if (grid[d.y][d.x] != '.' && grid[d.y][d.x] != '#') {
		bool ok = true;
		if (dir == 'v' || dir == '^')
			ok = box_check_v(dir, d);

		if (ok)
			box_move(dir, d);
	}
	
	if (grid[d.y][d.x] == '.') {
		grid[d.y][d.x] = '@';
		grid[o.y][o.x] = '.';
		return d;
	}
	return o;
}

bool
box_check_v(int dir, struct dvec2 o)
{
	if (grid[o.y][o.x] == '.')
		return true;

	if (grid[o.y][o.x] == '#')
		return false;
			
	struct dvec2 lhs = o;
	struct dvec2 rhs = o;
	if (grid[o.y][o.x] == '[')
		rhs.x++;
	else
		lhs.x--;

	int yoffset = (dir == 'v') ? 1 : -1;
	return box_check_v(dir, (struct dvec2) { .x = lhs.x, .y = lhs.y + yoffset })
		&& box_check_v(dir, (struct dvec2) { .x = rhs.x, .y = rhs.y + yoffset });
}

void
box_move(int dir, struct dvec2 o)
{
	if (grid[o.y][o.x] != '[' && grid[o.y][o.x] != ']')
		return;
	
	if (dir == '>' || dir == '<') {
		/* This case is essentially the same as part 1 */
		struct dvec2 d = o;
		if (dir == '>')
			d.x += 1;
		else
			d.x -= 1;
		box_move(dir, d);
		if (grid[d.y][d.x] == '.') {
			char tmp = grid[d.y][d.x];
			grid[d.y][d.x] = grid[o.y][o.x];
			grid[o.y][o.x] = tmp;
		}
		return;
	} else {
		/*
		  It gets more complicated here. There care cases like
		  ```
		  v

		   @
		   []
		  [][]
		  ```
		  where stuff gets pushed down in a tree-like way.
		*/
		struct dvec2 lhs = o;
		struct dvec2 rhs = o;

		if (grid[o.y][o.x] == '[')
			rhs.x++;
		else
			lhs.x--;
		int yoffset = (dir == 'v') ? 1 : -1;
		
		struct dvec2 nlhs = lhs;
		struct dvec2 nrhs = rhs;
		
		nlhs.y += yoffset;
		nrhs.y += yoffset;
		
		box_move(dir, nlhs);
		box_move(dir, nrhs);

		if (grid[nlhs.y][nlhs.x] == '.' && grid[nlhs.y][nlhs.x] == '.') {
			grid[nlhs.y][nlhs.x] = '[';
			grid[nrhs.y][nrhs.x] = ']';
			grid[lhs.y][lhs.x] = '.';
			grid[rhs.y][rhs.x] = '.';
		}
	}
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
		xlen = get_linelen(scanbuf) * 2;

		char *gcursor = &grid[ylen++][0];
		char *scursor = scanbuf;
		int xpos = 0;
		while (*scursor != '\n') {
			if (*scursor == '#') {
				gcursor[0] = '#';
				gcursor[1] = '#';
			} else if (*scursor == 'O') {
				gcursor[0] = '[';
				gcursor[1] = ']';
			} else if (*scursor == '@') {
				robot_pos = (struct dvec2) {
					.x = xpos,
					.y = ylen - 1,
				};
				gcursor[0] = '@';
				gcursor[1] = '.';
			} else {
				gcursor[0] = '.';
				gcursor[1] = '.';
			}
			xpos += 2;
			gcursor += 2;
			scursor += 1;
		}
	}
	
	int dir;
	while ((dir = fgetc(stdin)) != EOF) {
		if (dir == '\n')
			continue;

		robot_pos = robot_move(dir, robot_pos);
	}
	
	long long int sol = 0;
	for (int y = 0; y < ylen; y++) {
		for (int x = 0; x < xlen; x++) {
			if (grid[y][x] == '[')
				sol += 100 * y + x;
		}
	}
	printf("%lld\n", sol);
}

