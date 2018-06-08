#include "posix_file_reader.h"
#include "file_line_reader.h"
#include "index_item.h"
#include "indexfile_reader.h"
#include "print_index_item.h"
#include <iostream>
#include <string>
#include <memory>

using namespace std;

int main(int argc, char *argv[])
{
    string filename = "test.index";
    int buf_size = 2048;

    auto file_reader = make_shared<PosixFileReader>();
    file_reader->open(filename.c_str());

    auto line_reader = make_shared<FileLineReader>(file_reader, buf_size);

    IndexfileReader reader(line_reader);

    while (reader.has_next()) {
        auto item = reader.next();
        cout << item << "\n";
    }

    return 0;
}
