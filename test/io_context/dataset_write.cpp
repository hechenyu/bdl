#include <memory>
#include <iostream>
#include "config_parser.h"
#include "posix_file_system.h"
#include "io_context.h"
#include "dataset_index.h"

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

    IOContext io_context(root_name, make_shared<PosixFileSystem>());
    DatasetIndex index(&io_context, dataset_index_name, "a");

    return 0;
}
