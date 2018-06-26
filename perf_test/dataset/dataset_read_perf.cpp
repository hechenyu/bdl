#include <memory>
#include <iostream>
#include "boost/filesystem.hpp"
#include "config_parser.h"
#include "posix_file_system.h"
#include "io_context.h"
#include "dataset_index.h"

using namespace std;
namespace fs = boost::filesystem;

int main(int argc, char *argv[])
{
    ConfigParser parser(argv[0]);
    parser.add_option("help,h")
          .add_option("list,t", "list datafile in partitions")
          .add_string_option("conf,f", "confile")
          .add_string_option("root", "root of io_context")
          .add_string_option("dataset", "dataset index name")
          ;

    parser.parse_command_line(argc, argv);

    if (parser.has_parsed_option("help")) {
        parser.print_options_description(cout);
        exit(1);
    }

    string root_name = parser.get_string_variables("root", "/tmp");
    string dataset_index_name = parser.get_string_variables("dataset", "file_set");
    bool list_flag = parser.has_parsed_option("list");

    auto io_context = IOContext::create_io_context(root_name);
    DatasetIndex index(io_context, dataset_index_name, "r");

    std::vector<DatasetIndexItem> index_item_list_; 
    for (auto item: index) {
        if (list_flag)
            cout << item.file_path() << "\n";

        index_item_list_.push_back(item);
    }

    return 0;
}
