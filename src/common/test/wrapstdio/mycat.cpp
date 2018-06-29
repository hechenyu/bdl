#include <string.h>
#include "wrapstdio.h"

#define	BUFFSIZE	4096

int
main(void)
{
	int		n;
	char	buf[BUFFSIZE];

	while ((n = Fread2(buf, BUFFSIZE, stdin)) > 0)
		Fwrite2(buf, n, stdout);

	return 0;
}
