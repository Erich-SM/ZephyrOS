.POSIX:
PROJECTDIR =../../..
include $(PROJECTDIR)/scripts/rules.mk
include ../rules.mk

OBJS =\
	_daysyear.$O\
	asctime.$O\
	ctime.$O\
	difftime.$O\
	gmtime.$O\
	localtime.$O\
	mktime.$O\
	strftime.$O\
	tz.$O\

all: $(LIBC)

$(LIBC): $(OBJS)
	$(MKLST)

$(OBJS): tz.c

tz.c: timezone.lst
	awk -f gentz.awk $< >$@

dep: inc-dep

include deps.mk
