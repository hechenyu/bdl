#include "error.h"
#include "posix_file_writer.h"
#include <iostream>
#include <string>

using namespace std;

int
main(int argc, char *argv[])
{
	int		n;

    if (argc != 2) {
        err_msg("usage: %s file\n", argv[0]);
        return -1;
    }

    PosixFileWriter writer;
    writer.open(argv[1]);
    writer.truncate();

    string buf;
	while (getline(cin, buf)) {
        buf += '\n';
        writer.write(buf.data(), buf.length());
    }

	return 0;
}
