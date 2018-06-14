#include <memory>
#include <string>
#include <iostream>
#include "config_parser.h"
#include "posix_file_system.h"
#include "io_context.h"
#include "dataset_index.h"
#include "print_dataset_index_item.h"

using namespace std;

int main(int argc, char *argv[])
{
    ConfigParser parser(argv[0]);
    parser.add_option("help,h")
          .add_option("list,t", "list datafile in partitions")
          .add_string_option("root", "root of io_context")
          .add_string_option("in_dataset", "input dataset index name")
          .add_string_option("out_dataset", "output dataset index name");

    parser.parse_command_line(argc, argv);

    if (parser.has_parsed_option("help")) {
        parser.print_options_description(cout);
        exit(1);
    }

    string root_name = parser.get_string_variables("root", "/tmp");
    string in_dataset_index_name = parser.get_string_variables("in_dataset", "file_set");
    string out_dataset_index_name = parser.get_string_variables("out_dataset", "file_set.ABC");
    bool list_flag = parser.has_parsed_option("list");

    auto io_context = make_shared<IOContext>(root_name, make_shared<PosixFileSystem>());
    DatasetIndex in_index(io_context, in_dataset_index_name, "r");
    DatasetIndex out_index(io_context, out_dataset_index_name, "a");

    for (auto item: in_index) {
        if (list_flag)
            cout << item << "\n";

        out_index.appendItem(item);
    }

    return 0;
}
