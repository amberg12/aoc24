#include <stdio.h>
#include <string.h>
#include <stdbool.h>

static inline long long int
parsenum(const char *);

static inline bool
can_valid(const char *c, long long int target);

static inline long long int
parsenum(const char *c) {
	long long int out = 0;
	while ('0' <= *c && *c <= '9') {
		out *= 10;
		out += *c & 15;
		c++;
	}
	return out;
}

static inline bool
numslist_can_be_target(
	long long int nums[],
	size_t nelems,
	int i,
	long long int root,
	long long int target
) {
	if (i == nelems) return root == target;

	long long int mult = root * nums[i];
	long long int add = root + nums[i];

	bool mult_ok = numslist_can_be_target(nums, nelems, i+1, mult, target);
	bool add_ok = numslist_can_be_target(nums, nelems, i+1, add, target);

	return mult_ok || add_ok;
}

static inline bool
can_valid(const char *c, long long int target)
{
	long long int nums[128] = {0};
	size_t nelems = 0;
	while (*c) {
		nums[nelems++] = parsenum(c);
		while (*c != ' ' && *c != '\n') {
			c++;
		}
		c++;
	}

	return numslist_can_be_target(nums, nelems, 1, nums[0], target);
}

int
main(int argc, char **argv)
{
	long long int sol = 0;

	char scanbuf[256] = {0};
	while (fgets(scanbuf, sizeof(scanbuf), stdin)) {
		char *cursor = scanbuf;
		long long int leftnum = parsenum(cursor);
		while (*cursor++ != ' ');
		if (can_valid(cursor, leftnum)) sol += leftnum;
		memset(scanbuf, 0, sizeof(scanbuf));
	}

	printf("%lld\n", sol);
}
