#include <stdio.h>
#include <string.h>
#include <math.h>

struct button {
	long long int x;
	long long int y;
};

struct button
line_to_button(const char *);

struct button
solve(struct button, struct button, struct button);

struct button
line_to_button(const char *l)
{
	while (*l++ != 'X');
	l++;
	long long int x = 0;
	while ('0' <= *l && *l <= '9') {
		x *= 10;
		x += *l++ & 15;
	}
	while (*l++ != 'Y');
	l++;
	long long int y = 0;
	while ('0' <= *l && *l <= '9') {
		y *= 10;
		y += *l++ & 15;
	}
	return (struct button) { .x = x, .y = y };
}

struct button
solve(struct button a, struct button b, struct button target)
{
	/*
	  High school matrix maths came in clutch here.
	 */
	double ma = a.x;
	double mb = b.x;
	double mc = a.y;
	double md = b.y;
	double me = target.x;
	double mf = target.y;

	double outx = (md * me - mb * mf) / (ma * md - mb * mc);
	double outy = (ma * mf - mc * me) / (ma * md - mb * mc);
	
	if (fabs(outx - round(outx)) > 1e-6 || fabs(outy - round(outy)) > 1e-6)
                return (struct button) { .x = 0, .y = 0 };
	
	return (struct button) { .x = outx, .y = outy };
}

int
main(int argc, char **argv)
{
	char scanbuf[256] = {0};
	long long int sol = 0;
	while (fgets(scanbuf, sizeof scanbuf, stdin)) {
		if (*scanbuf == '\n') continue;
		struct button a;
		struct button b;
		struct button p;
		if (memcmp(scanbuf, "Button A:", 8) == 0)
			a = line_to_button(scanbuf);
		if (memcmp(scanbuf, "Button B:", 8) == 0)
			b = line_to_button(scanbuf);

		if (memcmp(scanbuf, "Prize:", 6) == 0) {
			p = line_to_button(scanbuf);
			p.x += 10000000000000;
			p.y += 10000000000000;
			struct button res = solve(a, b, p);
			sol += res.x * 3 + res.y;
		}
		memset(scanbuf, 0, sizeof scanbuf);
	}
	printf("%lld\n", sol);
}
