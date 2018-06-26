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
#include "chrono_timer.h"
#include "chrono_timer_util.h"
#include "chrono_util.h"
#include "utc_to_string.h"

using namespace std;
using namespace std::chrono;
namespace fs = boost::filesystem;

void output_detail(const vector<DatasetIndexItem> &index_item_list,
        const vector<ChronoTimer> &open_time_list, const vector<ChronoTimer> &read_time_list,
        const string &out_file_name);

void output_sum(
        const vector<ChronoTimer> &open_time_list, const vector<ChronoTimer> &read_time_list,
        const string &out_file_name);

int main(int argc, char *argv[])
{
    ConfigParser parser(argv[0]);
    parser.add_option("help,h")
          .add_option("list,t", "list datafile in partitions")
          .add_int_option("seed", "shuffle seed")
          .add_string_option("conf,f", "configure file")
          .add_string_option("root", "root of io_context")
          .add_string_option("dataset", "dataset index name")
          .add_string_option("dir,d", "the dir of statistics file to save result")
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
    bool list_flag = parser.has_parsed_option("list");

    // ===================== 读取Dataset Index Item ============================
    auto io_context = IOContext::create_io_context(root_name);
    DatasetIndex index(io_context, dataset_index_name, "r");

    vector<DatasetIndexItem> index_item_list; 
    for (auto item: index) {
        if (list_flag)
            cout << item.file_path() << "\n";

        index_item_list.push_back(item);
    }

    long seed = system_clock::now().time_since_epoch().count();
    if (parser.has_parsed_option("seed")) {
        seed = parser.get_int_variables("seed");
    }
    cout << "seed: " << seed << endl;

    if (seed > 0) {
        shuffle (index_item_list.begin(), index_item_list.end(), std::default_random_engine(seed));
    }

    string output_dir = parser.get_string_variables("dir", "");
    if (!output_dir.empty())
        fs::create_directories(output_dir);

    // ===================== 统计文件打开和读取时间 ============================
    vector<ChronoTimer> open_time_list;
    open_time_list.reserve(index_item_list.size());
    vector<ChronoTimer> read_time_list;
    read_time_list.reserve(index_item_list.size());

    ChronoTimer open_timer;
    ChronoTimer read_timer;
    for (auto item: index_item_list) {
        open_timer.start();
        auto datafile = index.openFile(item);
        open_timer.stop();
        open_time_list.push_back(open_timer);

        read_timer.start();
        auto data = datafile.readAll();
        read_timer.stop();
        read_time_list.push_back(read_timer);
        (void) data;
    }

    // ===================== 将结果保存到文件中 ============================
    string out_file_name;
    if (!output_dir.empty())
        out_file_name += output_dir + "/";
    out_file_name += basename(argv[0]);
    out_file_name += ".";
    out_file_name += utc_to_string(system_clock::now());

    output_detail(index_item_list, open_time_list, read_time_list, out_file_name+".csv");
    output_sum(open_time_list, read_time_list, out_file_name+".sum");

    return 0;
}

void output_detail(const vector<DatasetIndexItem> &index_item_list,
        const vector<ChronoTimer> &open_time_list, const vector<ChronoTimer> &read_time_list,
        const string &out_file_name)
{
    ofstream ofile;
    ofile.open(out_file_name);
    if (!ofile) {
        cout << "open output file fail: " << out_file_name << endl;
        exit(1);
    }

    ofile << "part path, offset, file size, open microsecs, read microsecs, file path\n";
    ofile << fixed;

    int n = index_item_list.size();
    for (int i = 0; i < n; i++) {
        auto &item = index_item_list[i];
        ofile << item.partition_path() << ","
            << item.offset() << ","
            << item.file_size() << ","
            << duration_to_microseconds(open_time_list[i].elapsed()) << ","
            << duration_to_microseconds(read_time_list[i].elapsed()) << ","
            << item.file_path() << "\n";
    }

}

void output_sum(
        const vector<ChronoTimer> &open_time_list, const vector<ChronoTimer> &read_time_list,
        const string &out_file_name)
{
    ofstream ofile;
    ofile.open(out_file_name);
    if (!ofile) {
        cout << "open output file fail: " << out_file_name << endl;
        exit(1);
    }

    double open_time = duration_to_microseconds(sum(open_time_list));
    double read_time = duration_to_microseconds(sum(read_time_list));
    double total_time = open_time + read_time;

    boost::format fmt("{\"open_time microseconds\": %f, \"read_time microseconds\": %f, \"total_time microseconds\": %f }");
    ofile << fmt % open_time % read_time % total_time;
}
