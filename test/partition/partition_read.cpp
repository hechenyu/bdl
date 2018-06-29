#include <string>
#include <iostream>
#include <fstream>
#include "config_parser.h"
#include "posix_file_reader.h"
#include "partition_reader.h"
#include "boost/filesystem.hpp"

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

    auto file_reader = make_shared<PosixFileReader>();
    PartitionReader partition_reader(partfile_name, file_reader);

    if (!output_dir.empty())
        fs::create_directories(output_dir);

    long offset = 0;
    while (partition_reader.has_next()) {
        auto datafile = partition_reader.next();
        auto metadata = datafile.metadata();
        auto datafile_name = metadata.file_name();

        if (list_flag) {
            cout << datafile_name << "\n";
            cout << "CRC: " << datafile.CRC() << "\n";
            cout << "total_size: " << datafile.total_size() << "\n";
            cout << "blob_size: " << datafile.blob_size() << "\n";
            cout << "metadata_size: " << datafile.metadata_size() << "\n";
            cout << "offset: " << offset << "\n";
        }
        offset += datafile.total_size();

        if (!output_dir.empty())
            datafile_name = output_dir+"/"+datafile_name;
        fs::path path(datafile_name);

        fs::create_directories(path.parent_path());
        write_file(datafile_name, datafile.blob_data(), datafile.blob_size());
    }

    return 0;
}
