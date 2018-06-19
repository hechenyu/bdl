#include <memory>
#include <iostream>
#include "config_parser.h"
#include "posix_file_system.h"
#include "io_context.h"
#include "dataset_index.h"
#include "test_partition_util.h"

using namespace std;

int main(int argc, char *argv[])
{
    ConfigParser parser(argv[0]);
    parser.add_option("help,h")
          .add_string_option("list_file,f", "list file of file to read")
          .add_string_option("root", "root of io_context")
          .add_string_option("dataset", "dataset index name");

    parser.parse_command_line(argc, argv);

    if (parser.has_parsed_option("help") || !parser.has_parsed_option("list_file")) {
        parser.print_options_description(cout);
        exit(1);
    }

    string root_name = parser.get_string_variables("root", "/tmp");
    string dataset_index_name = parser.get_string_variables("dataset", "file_set");

    auto io_context = IOContext::create_io_context(root_name);
    DatasetIndex index(io_context, dataset_index_name, "a");

    auto file_list = get_file_list(parser.get_string_variables("list_file"));
    for (auto &file_name : file_list) {
        auto file_data = read_all(file_name);
        auto file_type = get_suffix(file_name);
        auto file_handle = index.appendFile(file_name, file_type);
        file_handle.writeAll(file_data);
        cout << "process " << file_type << " type: " << file_name << " ok" << endl;
    }

    return 0;
}
