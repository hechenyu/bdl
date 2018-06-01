#include "error.h"
#include "wrapposix.h"
#include <fcntl.h>

#define	BUFFSIZE	4096
#define FILE_MODE   (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

int
main(int argc, char *argv[])
{
	int		n;
	char	buf[BUFFSIZE];

    if (argc != 2) {
        err_msg("usage: %s file\n", argv[0]);
        return -1;
    }

    int fd = Open(argv[1], O_WRONLY | O_CREAT, FILE_MODE);
//    int fd = Open(argv[1], O_WRONLY | O_CREAT | O_EXCL, FILE_MODE);

	while ((n = Read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
		Write(fd, buf, n);

    close(fd);

	return 0;
}
