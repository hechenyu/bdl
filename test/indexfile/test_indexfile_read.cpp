#include "posix_file_reader.h"
#include "file_line_reader.h"
#include "indexfile_item.h"
#include "indexfile_reader.h"
#include "print_indexfile_item.h"
#include <iostream>
#include <string>
#include <memory>

using namespace std;

int main(int argc, char *argv[])
{
    string filename = "test.index";
    int buf_size = 2048;

    if (argc == 2) {
        filename = argv[1];
    }

    auto line_reader = make_shared<FileLineReader>(make_shared<PosixFileReader>(), buf_size);
    IndexfileReader reader(filename, line_reader);

    while (reader.has_next()) {
        auto item = reader.next();
        cout << *item << "\n";
    }

    return 0;
}
