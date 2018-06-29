#include "error.h"
#include "wrapstdio.h"

#define	BUFFSIZE	4096

int
main(int argc, char *argv[])
{
	int		n;
	char	buf[BUFFSIZE];

    if (argc != 2) {
        err_msg("usage: %s file\n", argv[0]);
        return -1;
    }

    FILE *fp = Fopen(argv[1], "w");

	while ((n = Fread2(buf, BUFFSIZE, stdin)) > 0)
		Fwrite2(buf, n, fp);

    Fclose(fp);

	return 0;
}
