#include "wrapposix.h"
#include <fcntl.h>

#define FILE_MODE   (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

char	buf1[] = "abcdefghij";
char	buf2[] = "ABCDEFGHIJ";

int
main(void)
{
    const char *filename = "test.txt";
    int fd = Open(filename, O_WRONLY | O_CREAT | O_TRUNC, FILE_MODE);

	Write(fd, buf1, 10);
	/* offset now = 10 */

	Write(fd, buf2, 10);
	/* offset now = 16394 */

    close(fd);

//    fd = Open(filename, O_WRONLY | O_APPEND);
    fd = Open(filename, O_WRONLY);

    Write(fd, (void *) "123", 3);

    Lseek(fd, 0, SEEK_SET);
    Write(fd, (void *) "456", 3);
    Write(fd, (void *) "789", 3);

    Lseek(fd, 0, SEEK_END);
    Write(fd, (void *) "xxxx", 4);
    Write(fd, (void *) "yyyy", 4);

	return 0;
}
