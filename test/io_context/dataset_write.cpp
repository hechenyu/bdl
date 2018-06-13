#include <memory>
#include <iostream>
#include "posix_file_system.h"
#include "io_context.h"
#include "dataset_index.h"

using namespace std;

int main(int argc, char *argv[])
{
    string root = "/tmp";
    string index_path = "file_set";

    auto io_context = make_shared<IOContext>(root, make_shared<PosixFileSystem>());
    DatasetIndex index(io_context.get(), index_path, "a");
    return 0;
}
