#include "wrapposix.h"

#define	BUFFSIZE	4096

int
main(void)
{
	int		n;
	char	buf[BUFFSIZE];

	while ((n = Read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
		Write(STDOUT_FILENO, buf, n);

	return 0;
}
