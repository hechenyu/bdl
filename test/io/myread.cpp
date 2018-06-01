#include "error.h"
#include "posix_file_reader.h"
#include <iostream>
#include <string>

#define	BUFFSIZE	4096

using namespace std;

int
main(int argc, char *argv[])
{
	int		n;
	char	buf[BUFFSIZE];
    if (argc != 2) {
        err_msg("usage: %s file\n", argv[0]);
        return 0;
    }

    PosixFileReader reader;
    reader.open(argv[1]);

	while ((n = reader.read(buf, BUFFSIZE)) > 0)
        cout << string(buf, n) << ends;

	return 0;
}
