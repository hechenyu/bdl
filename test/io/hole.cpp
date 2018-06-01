#include "wrapposix.h"
#include "posix_file_writer.h"
#include <fcntl.h>

char	buf1[] = "abcdefghij";
char	buf2[] = "ABCDEFGHIJ";

int
main(void)
{
    PosixFileWriter writer;
    writer.open("file.hole");
    writer.truncate();

	writer.write(buf1, 10);
	/* offset now = 10 */

	writer.seek(16384, SEEK_SET);
	/* offset now = 16384 */

	writer.write(buf2, 10);
	/* offset now = 16394 */

	return 0;
}
