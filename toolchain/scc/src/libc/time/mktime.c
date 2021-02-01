#include <limits.h>
#include <time.h>

#include "../libc.h"
#undef mktime

static int
norm(int *val, int *next, int qty)
{
	int v = *val, n = *next, d;

	if (v < 0) {
		d = -v / qty + 1;
		v += d * qty;
		if (n > INT_MAX - d)
			return 0;
		n -= d;
	}
	if (v >= qty) {
		d = v / qty;
		v -= d * qty;
		if (n < INT_MIN + d)
			return 0;
		n += d;
	}

	*val = v;
	*next = n;
	return 1;
}

static int
normalize(struct tm *tm)
{
	int mon, day, year, yday;
	struct tm aux = *tm;

	if (!norm(&tm->tm_sec, &tm->tm_min, 60)   ||
	    !norm(&tm->tm_min, &tm->tm_hour, 60)  ||
	    !norm(&tm->tm_hour, &tm->tm_mday, 24) ||
	    !norm(&tm->tm_mon, &tm->tm_year, 12)) {
		return 0;
	}

	if (tm->tm_year < 0)
		return 0;

	day = tm->tm_mday;
	yday = 0;
	year = 1900 + tm->tm_year;
	_daysmon[FEB] = FEBDAYS(year);

	for (mon = tm->tm_mon; day < 1; --mon) {
		if (mon == JAN) {
			if (year == 1900)
				return 0;
			year--;
			_daysmon[FEB] = FEBDAYS(year);
			mon = DEC+1;
		}
		day += _daysmon[mon-1];
	}

	for (; day > _daysmon[mon]; ++mon) {
		day -= _daysmon[mon];
		if (mon == DEC) {
			if (year == _MAXYEAR)
				return 0;
			year++;
			_daysmon[FEB] = FEBDAYS(year);
			mon = JAN-1;
		}
	}

	for (int i = 0; i < mon; i++)
		yday += _daysmon[i];

	tm->tm_mon = mon;
	tm->tm_year = year - 1900;
	tm->tm_mday = day;
	tm->tm_yday = yday + day - 1;
	tm->tm_wday = (_newyear(tm->tm_year) + tm->tm_yday) % 7;

	return 1;
}

time_t
mktime(struct tm *tm)
{
	int i, year, dst;
	time_t t;
	struct tm *aux;

	if (!normalize(tm))
		return -1;

	t = 0;
	year = tm->tm_year + 1900;
	for (i = EPOCH; i < year; i++)
		t += _daysyear(i) * SECDAY;

	for (i = 0; i < tm->tm_mon; i++)
		t += _daysmon[i] * SECDAY;

	t += tm->tm_sec;
	t += tm->tm_min * SECMIN;
	t += tm->tm_hour * SECHOUR;
	t += (tm->tm_mday-1) * SECDAY;

	aux = localtime(&t);

	t += aux->tm_gmtoff;

	return t;
}
