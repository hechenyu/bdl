#include <iostream>
#include <memory>
#include "posix_file_writer.h"
#include "partition_writer.h"
#include "posix_file_reader.h"
#include "test_partition_util.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 3) {
        cerr << "usage: " << argv[0] << " filelist_file ofile\n";
        return 1;
    }

    auto file_writer = make_shared<PosixFileWriter>();
    auto file_reader = make_shared<PosixFileReader>();
    PartitionWriter partition_writer(argv[2], file_writer, file_reader);

    auto file_list = get_file_list(argv[1]);
    for (auto &file_name : file_list) {
        auto file_data = read_all(file_name);
        auto file_type = get_suffix(file_name);
        partition_writer.write(file_name, file_type, (uint8_t *) file_data.data(), file_data.size());
        cout << "process " << file_type << " type: " << file_name << " ok" << endl;
    }

    return 0;
}

