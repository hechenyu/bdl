#include <string>
#include <iostream>
#include "config_parser.h"
#include "posix_file_reader.h"
#include "partition_reader.h"

using namespace std;

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
    string output_dir = parser.get_string_variables("dir", ".");
    bool list_flag = parser.has_parsed_option("list");

    auto file_reader = make_shared<PosixFileReader>();
    PartitionReader partition_reader(partfile_name, file_reader);

    while (partition_reader.has_next()) {
        auto datafile = partition_reader.next();
        auto metadata = datafile.metadata();
        auto datafile_name = metadata.file_name();
        if (list_flag) {
            cout << datafile_name << "\n";
        }
    }

    return 0;
}
