#include <stdio.h>
#undef fputc

int
fputc(int c, FILE *fp)
{
	return putc(c, fp);
}
