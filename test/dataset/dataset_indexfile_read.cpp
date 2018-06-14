#include "dataset_indexfile_reader.h"
#include "print_dataset_index_item.h"
#include "posix_file_system.h"
#include <iostream>
#include <string>
#include <memory>

using namespace std;

int main(int argc, char *argv[])
{
    string filename = "test.index";
    string partition_path = "test.part";

    if (argc == 2) {
        filename = argv[1];
    }

    auto file_system = make_shared<PosixFileSystem>();
    DatasetIndexfileReader reader(file_system, filename, partition_path);

    for (auto item: reader) {
        cout << item << "\n";
    }

    return 0;
}

