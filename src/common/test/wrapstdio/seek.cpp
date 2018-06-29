#include "wrapstdio.h"
#include <fcntl.h>

#define FILE_MODE   (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

char	buf1[] = "abcdefghij";
char	buf2[] = "ABCDEFGHIJ";

int
main(void)
{
    const char *filename = "test.txt";
    FILE *fp = Fopen(filename, "w");

	Fwrite2(buf1, 10, fp);
	/* offset now = 10 */

	Fwrite2(buf2, 10, fp);
	/* offset now = 16394 */

    Fclose(fp);

    fp = Fopen(filename, "r+");

    Fwrite2((void *) "123", 3, fp);

    Fseek(fp, 0, SEEK_SET);
    Fwrite2((void *) "456", 3, fp);
    Fwrite2((void *) "789", 3, fp);

    Fseek(fp, 0, SEEK_END);
    Fwrite2((void *) "xxxx", 4, fp);
    Fwrite2((void *) "yyyy", 4, fp);

	return 0;
}
