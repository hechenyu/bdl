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

	FileLineReader reader(make_shared<PosixFileReader>(), 8192);
    reader.open(argv[1]);
    string str;
	while (reader.getline(str))
        cout << str << endl;

    return 0;
}
