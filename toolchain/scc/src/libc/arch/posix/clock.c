#include "clock.h"

extern int _getrusage(int, struct rusage*);

static clock_t
convtick(struct rusage r)
{
	return r.ru_utime.tv_sec*CLOCKS_PER_SEC +
	       r.ru_stime.tv_usec / (1000000 / CLOCKS_PER_SEC);
}


clock_t
clock(void)
{
	struct rusage ru;
	clock_t c;

	if (_getrusage(RUSAGE_SELF, &ru))
		return ((clock_t) -1);
	return convtick(ru);
}
