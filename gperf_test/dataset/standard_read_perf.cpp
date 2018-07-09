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
#include "get_file_list.h"
#include "posix_file_reader.h"

using namespace std;
using namespace std::chrono;
namespace fs = boost::filesystem;

int main(int argc, char *argv[])
{
    ConfigParser parser(argv[0]);
    parser.add_option("help,h")
          .add_option("verbose,v")
          .add_string_option("seed", "shuffle seed")
          .add_string_option("conf", "configure file")
          .add_string_option("list_file", "list file of file to read")
          .add_string_option("dir", "the dir of statistics file to save result")
          .add_string_option("label", "out file label")
          ;

    parser.parse_command_line(argc, argv);

    if (parser.has_parsed_option("conf")) {
        auto conf_file = parser.get_string_variables("conf");
        if (!fs::exists(conf_file)) {
            cerr << "configure file not exists: " << conf_file << '\n';
            exit(1);
        }
        parser.parse_config_file(conf_file);
    }

    if (parser.has_parsed_option("help") || !parser.has_parsed_option("list_file")) {
        parser.print_options_description(cout);
        exit(1);
    }

    // ===================== 读取file list ============================
    auto file_list = get_file_list(parser.get_string_variables("list_file"));
    bool list_flag = parser.has_parsed_option("verbose");
    if (list_flag) {
        for (auto &file_name: file_list) {
            cout << file_name << "\n";
        }
    }

    long seed = system_clock::to_time_t(system_clock::now());
    if (parser.has_parsed_option("seed")) {
        seed = stol(parser.get_string_variables("seed"));
    }
    cout << "seed: " << seed << endl;

    if (seed > 0) {
        shuffle (file_list.begin(), file_list.end(), std::default_random_engine(seed));
    }

    string output_dir = parser.get_string_variables("dir", "");
    if (!output_dir.empty())
        fs::create_directories(output_dir);

    for (auto &file_name : file_list) {
        PosixFileReader reader;
        reader.open(file_name.c_str());
        long file_size = reader.file_size();
        vector<uint8_t> buffer;
        buffer.resize(file_size);
        reader.readn(buffer.data(), buffer.size());
        (void) buffer;
    }

    return 0;
}

