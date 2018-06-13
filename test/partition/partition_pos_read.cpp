#include <string>
#include <iostream>
#include <fstream>
#include "config_parser.h"
#include "posix_file_reader.h"
#include "partition_pos_reader.h"
#include "boost/filesystem.hpp"
#include "posix_file_system.h"
#include "indexfile_reader.h"

using namespace std;
namespace fs = boost::filesystem;

void write_file(const string &datafile_name, const uint8_t *data, int size)
{
    ofstream ofile(datafile_name);
    ofile.write((const char *)data, size);
}

int main(int argc, char *argv[])
{
    ConfigParser parser(argv[0]);
    parser.add_option("help,h")
          .add_option("list,t", "list datafile in partitions")
          .add_string_option("file,f", "partition file to read")
          .add_string_option("dir,d", "output directory(default .)");

    parser.parse_command_line(argc, argv);

    if (parser.has_parsed_option("help") || !parser.has_parsed_option("file")) {
        parser.print_options_description(cout);
        exit(1);
    }

    string partfile_name = parser.get_string_variables("file");
    string output_dir = parser.get_string_variables("dir", "");
    bool list_flag = parser.has_parsed_option("list");

    PosixFileSystem file_system;
    PartitionPosReader partition_pos_reader(partfile_name, file_system.create_file_reader());

    IndexfileReader index_reader(partfile_name+".idx", file_system.create_line_reader());

    if (!output_dir.empty())
        fs::create_directories(output_dir);

    while (index_reader.has_next()) {
        auto index_item = index_reader.next();
        auto datafile = partition_pos_reader.read(DatafileIndex(index_item->offset, index_item->file_size));
        auto metadata = datafile.metadata();
        auto datafile_name = metadata.file_name();

        if (list_flag) {
            cout << datafile_name << "\n";
        }

        if (!output_dir.empty())
            datafile_name = output_dir+"/"+datafile_name;
        fs::path path(datafile_name);

        fs::create_directories(path.parent_path());
        write_file(datafile_name, datafile.blob_data(), datafile.blob_size());
    }

    return 0;
}
