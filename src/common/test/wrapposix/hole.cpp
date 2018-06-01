#include "wrapposix.h"
#include <fcntl.h>

char	buf1[] = "abcdefghij";
char	buf2[] = "ABCDEFGHIJ";

int
main(void)
{
    int fd = Open("file.hole", O_RDWR | O_CREAT | O_TRUNC);

	Write(fd, buf1, 10);
	/* offset now = 10 */

	Lseek(fd, 16384, SEEK_SET);
	/* offset now = 16384 */

	Write(fd, buf2, 10);
	/* offset now = 16394 */

	return 0;
}
