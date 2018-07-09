#include <memory>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <random>
#include <fstream>
#include <iomanip>
#include "boost/filesystem.hpp"
#include "boost/format.hpp"
#include "config_parser.h"
#include "posix_file_system.h"
#include "io_context.h"
#include "dataset_index.h"

using namespace std;
using namespace std::chrono;
namespace fs = boost::filesystem;

int main(int argc, char *argv[])
{
    ConfigParser parser(argv[0]);
    parser.add_option("help,h")
          .add_option("verbose,v")
          .add_option("readbuf")
          .add_string_option("seed", "shuffle seed")
          .add_string_option("conf", "configure file")
          .add_string_option("root", "root of io_context")
          .add_string_option("dataset", "dataset index name")
          .add_string_option("dir,d", "the dir of statistics file to save result")
          .add_string_option("label", "out file label")
          ;

    parser.parse_command_line(argc, argv);

    if (parser.has_parsed_option("help")) {
        parser.print_options_description(cout);
        exit(1);
    }

    if (parser.has_parsed_option("conf")) {
        auto conf_file = parser.get_string_variables("conf");
        if (!fs::exists(conf_file)) {
            cerr << "configure file not exists: " << conf_file << '\n';
            exit(1);
        }
        parser.parse_config_file(conf_file);
    }

    string root_name = parser.get_string_variables("root", "/tmp");
    string dataset_index_name = parser.get_string_variables("dataset", "file_set");
    bool list_flag = parser.has_parsed_option("verbose");

    IOContext::Configure io_conf;
    if (parser.has_parsed_option("readbuf")) {
        cout << "readbuf is on\n";
        io_conf.read_buffered = true;
    } else {
        cout << "readbuf is off\n";
        io_conf.read_buffered = false;
    }

    // ===================== 读取Dataset Index Item ============================
    auto io_context = IOContext::create_io_context(root_name, io_conf);
    DatasetIndex index(io_context, dataset_index_name, "r");

    vector<DatasetIndexItem> index_item_list; 
    for (auto item: index) {
        if (list_flag)
            cout << item.file_path() << "\n";

        index_item_list.push_back(item);
    }

    long seed = system_clock::to_time_t(system_clock::now());
    if (parser.has_parsed_option("seed")) {
        seed = stol(parser.get_string_variables("seed"));
    }
    cout << "seed: " << seed << endl;

    if (seed > 0) {
        shuffle (index_item_list.begin(), index_item_list.end(), std::default_random_engine(seed));
    }

    string output_dir = parser.get_string_variables("dir", "");
    if (!output_dir.empty())
        fs::create_directories(output_dir);

    for (auto item: index_item_list) {
        auto datafile = index.openFile(item);
        auto data = datafile.readAll();
        (void) data;
    }

    return 0;
}

