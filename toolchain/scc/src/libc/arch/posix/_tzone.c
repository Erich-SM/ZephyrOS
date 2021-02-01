#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../../libc.h"

#define TOKENSIZ 10

enum {
	EOS,
	NUM,
	STR,
};

enum {
	GREGORIAN,
	JULIAN,
};

static char st[TOKENSIZ], ds[TOKENSIZ], tokstr[TOKENSIZ];
static int tok;

char *_tzname[2] = { st, ds };
time_t _tzstdoff, _tzdstoff;
time_t _tzstart, _tzend;
int _tzjulian;

static int
next(char *str)
{
	int n, t;
	static char *s;

	if (str)
		s = str;

	switch (*s) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		n = strspn(s, "0123456789");
		t = NUM;
		break;
	case '+':
	case '-':
	case ':':
	case ',':
		n = 1;
		t = *s;
		break;
	case '\0':
		n = 0;
		t = EOS;
		break;
	default:
		n = strcspn(s, "+-0123456789");
		t = STR;
		break;
	}

	if (n >= TOKENSIZ-1)
		return -1;
	memcpy(tokstr, s, n);
	tokstr[n] = '\0';
	s += n;

	return tok = t;
}

static int
accept(int c)
{
	if (tok != c)
		return 0;
	return next(NULL);
}

static int
num(int max)
{
	int n;

	if (tok == EOS)
		return 0;
	if (tok != NUM)
		return -1;
	n = atoi(tokstr);
	if (n < 0 || n > max)
		return -1;
	return n;
}

static long
offset(void)
{
	int sign = 1;
	int n;
	long off;

	if (tok == EOS)
		return -1;

	switch (tok) {
	case '+':
		sign = -1;
	case '-':
		next(NULL);
		break;
	default:
		return -1;
	}

	if ((n = num(24)) < 0)
		return -1;
	off = n * SECHOUR;
	next(NULL);
	if (tok == EOS)
		goto ret;

	if (!accept(':'))
		return -1;
	if ((n = num(60)) < 0)
		return -1;
	off += n * SECMIN;
	next(NULL);
	if (tok == EOS)
		goto ret;

	if (!accept(':'))
		return -1;
	if ((n = num(60)) < 0)
		return -1;
	off += n;
	next(NULL);

 ret:
	return sign * off;
}

static int
std(void)
{
	time_t off;

	if (tok != STR)
		return 0;
	strcpy(st, tokstr);
	next(NULL);

	if ((off = offset()) == -1)
		return 0;
	_tzstdoff = off;

	return 1;
}

static int
dst(void)
{
	time_t off;

	if (tok != STR)
		return 0;
	strcpy(ds, tokstr);
	next(NULL);

	if ((off = offset()) == -1)
		_tzdstoff = off;
	else
		_tzdstoff = _tzstdoff + SECHOUR;

	return 1;
}

static int
yday(void)
{
	int type, n;

	if (tok == STR && !strcmp(tokstr, "J"))
		type = JULIAN;
	else if (tok == NUM)
		type = GREGORIAN;
	else
		return -1;

	switch (type) {
	case JULIAN:
		next(NULL);
		n = num(365);
		next(NULL);
		if (n == 0)
			return -1;
		_tzjulian = 1;
		break;
	case GREGORIAN:
		n = num(365);
		next(NULL);
		break;
	}

	return n;
}

static int
rule(void)
{
	if (tok == EOS)
		return 0;
	if (!accept(','))
		return 0;
	if ((_tzstart = yday()) == -1)
		return 0;
	if (!accept(','))
		return 0;
	if ((_tzend = yday()) == -1)
		return 0;
}

void
_tzset(void)
{
	char *tz = getenv("TZ");
	int i;

	_tzstdoff = _tzdstoff = (time_t) -1;
	_tzstart = _tzend = (time_t) -1;
	_tzjulian = 0;

	if (!tz)
		return;
	next(tz);

	if (!std())
		return;
	if (!dst())
		return;
	if (!rule())
		return;
}
