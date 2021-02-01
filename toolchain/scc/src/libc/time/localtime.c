#include <string.h>
#include <time.h>

#include "../libc.h"
#undef localtime

static time_t
gmtoff(char *tz)
{
	for (struct tzone *t = tzones; t->name; t++)
		if (!strcmp(t->name, tz))
			return t->gmtoff;
	return 0;
}

struct tm *
localtime(const time_t *timep)
{
	struct tm *tm;
	time_t t;
	int yday;
	static int first = 1;

	t = *timep;
	tm = gmtime(&t);
	yday = tm->tm_yday;

	if (first) {
		_tzset();
		if (_tzstdoff == -1)
			_tzstdoff = gmtoff(_tzname[0]);
		if (_tzdstoff == -1)
			_tzdstoff = gmtoff(_tzname[1]);
	}
	first = 0;

	tm->tm_gmtoff = _tzstdoff;
	tm->tm_zone = _tzname[0];
	tm->tm_isdst = 0;

	if (_tzjulian	       &&
	    ((yday + 1) < 60)  ||
	    (FEBDAYS(tm->tm_year) < 29))
		yday++;

	if (yday >= _tzstart &&
	    yday <= _tzend   &&
	    tm->tm_hour >= 2) {
		tm->tm_gmtoff = _tzdstoff;
		tm->tm_zone = _tzname[1];
		tm->tm_isdst = 1;
	}

	t += tm->tm_gmtoff;
	tm = gmtime(&t);

	return tm;
}
