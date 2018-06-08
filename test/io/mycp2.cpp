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

    auto file_reader = make_shared<PosixFileReader>();
    file_reader->open(argv[1]);

    auto file_writer = make_shared<PosixFileWriter>();
    file_writer->open(argv[2]);
    file_writer->truncate();

	FileLineReader reader(file_reader, 8192);
    FileLineWriter writer(file_writer, 8192);
    string str;
	while (reader.getline(str))
        writer.putline(str);

    return 0;
}
