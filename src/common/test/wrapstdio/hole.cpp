#include "wrapstdio.h"

char	buf1[] = "abcdefghij";
char	buf2[] = "ABCDEFGHIJ";

int
main(void)
{
    FILE *fp = Fopen("file.hole", "w");

	Fwrite2(buf1, 10, fp);
	/* offset now = 10 */

	Fseek(fp, 16384, SEEK_SET);
	/* offset now = 16384 */

	Fwrite2(buf2, 10, fp);
	/* offset now = 16394 */

	return 0;
}
