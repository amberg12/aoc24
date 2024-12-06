#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define MIB (1024 * 1024)

typedef enum : size_t {
	DIR_UP = 0,
	DIR_RIGHT = 1,
	DIR_DOWN = 2,
	DIR_LEFT = 3,
} Movement_Direction;

static inline size_t
get_linelen(const char *input);

static inline size_t
find_char(char find, const char *input);

static size_t directions[4] = {0};

char input[1024 * 1024] = {0};

static inline size_t
find_char(char find, const char *input)
{ /* We are assuming that the function will never not return. */
	size_t out = 0;
	while (input[out] != find) out++;
	return out;
}

static inline size_t
get_linelen(const char *input)
{
	size_t out = 0;
	while (input[++out] != '\n');
	return out;
}

int
main(int argc, char **argv)
{
	fread(input, 1, 1024 * 1024, stdin);

	/* Init useful data*/
	long long int sol = 0;
	size_t linelen = get_linelen(input);
	size_t linelen_inclf = linelen + 1;
	size_t max_i = strlen(input);
	directions[0] = -linelen_inclf;
	directions[1] = 1;
	directions[2] = linelen_inclf;
	directions[3] = -1;

	size_t guard_loc = find_char('^', input);

	Movement_Direction dir = DIR_UP;

	while (input[guard_loc] != '\n' 
	       && guard_loc != 0 
	       && guard_loc < max_i) {
		/*
		 * It turns out this step must be done first. I came into a 
		 * case where I was off by ~2 because of going over the 
		 * initial `^`, and rather then fix the root cause I just
		 * subtracted one from the solution.
		 */
		if (input[guard_loc] != 'X') sol += 1;
		input[guard_loc] = 'X';

		while (input[guard_loc + directions[dir]] == '#') {
			dir = (dir + 1) % 4;
			printf("-*- another step -*-\n%s", input);
		}
		guard_loc += directions[dir];
	}
	printf("-*- another step -*-\n%s", input);
	printf("%lld\n", sol);
}
