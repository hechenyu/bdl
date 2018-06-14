#include <memory>
#include <iostream>
#include "posix_file_system.h"
#include "io_context.h"
#include "dataset_index.h"
#include "print_dataset_index_item.h"

using namespace std;

int main(int argc, char *argv[])
{
    string root = "/tmp";
    string index_path = "file_set";

    auto io_context = make_shared<IOContext>(root, make_shared<PosixFileSystem>());
    DatasetIndex index(io_context, index_path, "r");

    auto index_files = index.getIndexFiles();
    for (auto index_file: index_files) {
        for (auto item: index_file) {
            cout << item << "\n";
        }
    }

    return 0;
}
