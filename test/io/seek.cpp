#include "error.h"
#include "posix_file_writer.h"
#include <fcntl.h>
#include <iostream>

using namespace std;

char	buf1[] = "abcdefghij";
char	buf2[] = "ABCDEFGHIJ";

int
main(void)
{
    const char *filename = "test.txt";
    PosixFileWriter writer;
    writer.open(filename);
    writer.truncate();

	writer.write(buf1, 10);
	/* offset now = 10 */

	writer.write(buf2, 10);
	/* offset now = 16394 */

    writer.close();

    writer.open(filename);

    // append at end of file
    writer.seek(0, SEEK_END);
    writer.write("123", 3);

    // overwrite at begin of file
    writer.seek(0, SEEK_SET);
    writer.write("456", 3);
    writer.write("789", 3);

    cout << "current pos: " << writer.seek(0, SEEK_CUR) << endl;
    writer.seek(10, SEEK_CUR);
    writer.write("xxxx", 4);
    writer.write("yyyy", 4);

	return 0;
}
