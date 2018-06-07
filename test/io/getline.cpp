#include "error.h"
#include "posix_file_reader.h"
#include "file_line_reader.h"
#include <iostream>
#include <string>
#include <memory>

using namespace std;

int main (int argc, char *argv[])
{
    if (argc != 2) {
        err_msg("usage: %s file\n", argv[0]);
        return 0;
    }
    auto file_reader = make_shared<PosixFileReader>();
    file_reader->open(argv[1]);

	FileLineReader reader(file_reader, 8192);
    string str;
	while (reader.getline(str))
        cout << str << endl;

    return 0;
}
