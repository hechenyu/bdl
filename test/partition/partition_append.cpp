#include <iostream>
#include <memory>
#include "posix_file_writer.h"
#include "partition_writer.h"
#include "posix_file_reader.h"
#include "test_partition_util.h"
#include "posix_file_system.h"
#include "indexfile_writer.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 3) {
        cerr << "usage: " << argv[0] << " filelist_file ofile\n";
        return 1;
    }

    PosixFileSystem file_system;
    PartitionWriter partition_writer(argv[2], 
            file_system.create_file_writer(),
            file_system.create_file_reader());

    IndexfileWriter index_writer(argv[2]+string(".idx"), file_system.create_line_writer());

    auto file_list = get_file_list(argv[1]);
    for (auto &file_name : file_list) {
        auto file_data = read_all(file_name);
        auto file_type = get_suffix(file_name);
        auto index = partition_writer.write(file_name, file_type, (uint8_t *) file_data.data(), file_data.size());
        index_writer.write(IndexfileItem(file_name, index.offset, index.file_size));
        cout << "process " << file_type << " type: " << file_name << " ok" << endl;
    }

    return 0;
}

