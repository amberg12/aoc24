#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct lld_slice {
	long long int *buf;
	size_t buflen;
};

struct pair_optional {
	bool is_pair;
	long long int a;
	long long int b;
};

struct pair_optional
has_even_digits(long long int x);

struct lld_slice
do_blink(long long int *buf, size_t buflen);

struct pair_optional
has_even_digits(long long int x)
{
	char buf[128] = {0};
	sprintf(buf, "%lld", x);

	size_t buflen = strlen(buf);
	if (buflen % 2 == 0) {
		char lbuf[64] = {0};
		char rbuf[64] = {0};
		memcpy(lbuf, buf, buflen / 2);
		memcpy(rbuf, buf + buflen / 2, buflen / 2);
		return (struct pair_optional) {
			.is_pair = true,
			.a = strtoll(lbuf, NULL, 10),
			.b = strtoll(rbuf, NULL, 10),
		};
	} else {
		return (struct pair_optional) {
			.is_pair = false,
		};
	}
}

struct lld_slice
do_blink(long long int *buf, size_t buflen)
{
	long long int *newbuf = malloc(buflen * 32);
	size_t newbuflen = 0;

	for (size_t i = 0; i < buflen; i++) {
		struct pair_optional pair = has_even_digits(buf[i]);
		if (buf[i] == 0) {
			newbuf[newbuflen] = 1;
			newbuflen++;
		} else if (pair.is_pair == true) {
			newbuf[newbuflen] = pair.a;
			newbuf[newbuflen + 1] = pair.b;
			newbuflen += 2;
		} else {
			newbuf[newbuflen] = buf[i] * 2024;
			newbuflen++;
		}
	}
	
	return (struct lld_slice) {
		.buf = newbuf,
		.buflen = newbuflen,
	};
}

int
main(int argc, char **argv)
{
	char input[128] = {0};
	fread(input, 1, sizeof input, stdin);

	size_t buflen = 0;
	long long int *buf = malloc(1024);

	/* Parse buf. */
	char *cursor = input;
	while (true) {
		if (*cursor == ' ') {
			buflen++;
		} else if (*cursor == '\n') {
			buflen++;
			break;
		} else {
			buf[buflen] *= 10;
			buf[buflen] += *cursor & 15;
		}
		cursor++;
	}

	for (int i = 0; i < 25; i++) {
		struct lld_slice slice = do_blink(buf, buflen);

		if (slice.buf != buf) {
			free(buf);
			buf = slice.buf;
		}
		buflen = slice.buflen;
	}
	printf("%lu\n", buflen);
}
