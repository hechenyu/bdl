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
#include "get_file_list.h"
#include "posix_file_reader.h"
#include "chrono_timer.h"
#include "chrono_timer_util.h"
#include "chrono_util.h"
#include "utc_to_string.h"
#include "output_summary.h"

using namespace std;
using namespace std::chrono;
namespace fs = boost::filesystem;

void output_detail(const vector<string> &file_list, const vector<long> &file_size_list,
        const vector<ChronoTimer> &open_time_list, const vector<ChronoTimer> &read_time_list,
        const string &out_file_name);

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

    // ===================== 统计文件打开和读取时间 ============================
    vector<ChronoTimer> open_time_list;
    open_time_list.reserve(file_list.size());
    vector<ChronoTimer> read_time_list;
    read_time_list.reserve(file_list.size());

    ChronoTimer open_timer;
    ChronoTimer read_timer;

    vector<uint8_t> buffer;
    vector<long> file_size_list;
    for (auto &file_name : file_list) {
        PosixFileReader reader;
        open_timer.start();
        reader.open(file_name.c_str());
        open_timer.stop();
        open_time_list.push_back(open_timer);

        long file_size = reader.file_size();
        buffer.resize(file_size);
        file_size_list.push_back(file_size);

        read_timer.start();
        reader.readn(buffer.data(), buffer.size());
        read_timer.stop();
        read_time_list.push_back(read_timer);
        (void) buffer;
    }

    // ===================== 将结果保存到文件中 ============================
    string out_file_name;
    if (!output_dir.empty())
        out_file_name += output_dir + "/";
    out_file_name += basename(argv[0]);
    out_file_name += ".";
    if (parser.has_parsed_option("label")) {
        out_file_name += parser.get_string_variables("label");
        out_file_name += ".";
    } 
    out_file_name += utc_to_string(system_clock::now());

    output_detail(file_list, file_size_list, open_time_list, read_time_list, out_file_name+".detail.csv");
    output_summary(open_time_list, read_time_list, out_file_name+".summary.json");

    return 0;
}

void output_detail(const vector<string> &file_list, const vector<long> &file_size_list,
        const vector<ChronoTimer> &open_time_list, const vector<ChronoTimer> &read_time_list,
        const string &out_file_name)
{
    ofstream ofile;
    ofile.open(out_file_name);
    if (!ofile) {
        cout << "open output file fail: " << out_file_name << endl;
        exit(1);
    }

    ofile << "file size, open microsecs, read microsecs, file path\n";
    ofile << fixed;

    assert(file_list.size() == file_size_list.size());
    assert(file_list.size() == open_time_list.size());
    assert(file_list.size() == read_time_list.size());

    int n = file_list.size();
    for (int i = 0; i < n; i++) {
        ofile << file_size_list[i] << ","
            << duration_to_microseconds(open_time_list[i].elapsed()) << ","
            << duration_to_microseconds(read_time_list[i].elapsed()) << ","
            << file_list[i] << "\n";
    }

}
