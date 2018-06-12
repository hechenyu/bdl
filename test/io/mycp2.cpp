#include "error.h"
#include "posix_file_reader.h"
#include "file_line_reader.h"
#include "posix_file_writer.h"
#include "file_line_writer.h"
#include <iostream>
#include <string>
#include <memory>

using namespace std;

int main (int argc, char *argv[])
{
    if (argc != 3) {
        err_msg("usage: %s from to\n", argv[0]);
        return 0;
    }

	FileLineReader reader(make_shared<PosixFileReader>(), 8192);
    reader.open(argv[1]);

    FileLineWriter writer(make_shared<PosixFileWriter>(), 8192);
    writer.open_truncate(argv[2]);

    string str;
	while (reader.getline(str))
        writer.putline(str);

    return 0;
}
