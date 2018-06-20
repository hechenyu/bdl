#include <memory>
#include <iostream>
#include "boost/filesystem.hpp"
#include "config_parser.h"
#include "posix_file_system.h"
#include "io_context.h"
#include "dataset_index.h"
#include "print_dataset_index_item.h"
#include "write_file.h"

using namespace std;
namespace fs = boost::filesystem;

int main(int argc, char *argv[])
{
    ConfigParser parser(argv[0]);
    parser.add_option("help,h")
          .add_option("list,t", "list datafile in partitions")
          .add_string_option("root", "root of io_context")
          .add_string_option("dataset", "dataset index name")
          .add_string_option("dir,d", "output directory(default .)");

    parser.parse_command_line(argc, argv);

    if (parser.has_parsed_option("help")) {
        parser.print_options_description(cout);
        exit(1);
    }

    string root_name = parser.get_string_variables("root", "/tmp");
    string dataset_index_name = parser.get_string_variables("dataset", "file_set");
    string output_dir = parser.get_string_variables("dir", "");
    bool list_flag = parser.has_parsed_option("list");

    auto io_context = IOContext::create_io_context(root_name);
    DatasetIndex index(io_context, dataset_index_name, "r");

    if (!output_dir.empty())
        fs::create_directories(output_dir);

    auto index_files = index.getIndexFiles();
    for (auto index_file: index_files) {
        for (auto item: index_file) {
            if (list_flag)
                cout << item << "\n";
            
            auto datafile_name = item.file_path();
            auto datafile = index.openFile(item);
            auto data = datafile.readAll();

            if (!output_dir.empty())
                datafile_name = output_dir+"/"+datafile_name;
            fs::path path(datafile_name);

            fs::create_directories(path.parent_path());
            write_file(datafile_name, data);
        }
    }

    return 0;
}
