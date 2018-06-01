#include "error.h"
#include "posix_file_reader.h"
#include "posix_file_writer.h"
#include <iostream>

#define	BUFFSIZE	4096

using namespace std;

int
main(int argc, char *argv[])
{
	int		n;
	char	buf[BUFFSIZE];
    if (argc != 3) {
        err_msg("usage: %s from to\n", argv[0]);
        return 0;
    }

    PosixFileReader reader;
    reader.open(argv[1]);

    PosixFileWriter writer;
    writer.open(argv[2]);
    writer.truncate();

	while ((n = reader.read(buf, BUFFSIZE)) > 0)
		writer.write(buf, n);

    cout << "process exit normally\n";

	return 0;
}
