#ifndef CLOCK_H
#define CLOCK_H

#include <time.h>

#define RUSAGE_SELF	0

typedef long int clock_t;

struct timeval {
	long int tv_sec;
	long int tv_usec;
};

struct rusage {
	struct timeval ru_utime;
	struct timeval ru_stime;
	long int ru_maxrss;
	long int ru_ixrss;
	long int ru_idrss;
	long int ru_isrss;
	long int ru_minflt;
	long int ru_majflt;
	long int ru_nswap;
	long int ru_inblock;
	long int ru_oublock;
	long int ru_msgsnd;
	long int ru_msgrcv;
	long int ru_nsignals;
	long int ru_nvcsw;
	long int ru_nivcsw;
};

#endif
