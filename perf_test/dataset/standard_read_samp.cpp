#include <memory>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <random>
#include <fstream>
#include <iomanip>
#include <atomic>
#include <thread>
#include "boost/filesystem.hpp"
#include "boost/format.hpp"
#include "config_parser.h"
#include "posix_file_system.h"
#include "get_file_list.h"
#include "posix_file_reader.h"
#include "chrono_timer.h"
#include "chrono_timer_util.h"
#include "chrono_util.h"
#include "utc_to_string.h"
#include "output_functions.h"
#include "samp_printer.h"

using namespace std;
using namespace std::chrono;
namespace fs = boost::filesystem;

atomic<int> g_file_number_readed;
atomic<uint64_t> g_file_size_readed;

void io_context_run(boost::asio::io_context *io)
{
    io->run();
}

int main(int argc, char *argv[])
{
    ConfigParser parser(argv[0]);
    parser.add_option("help,h")
          .add_option("verbose,v")
          .add_int_option("loop_times", "loop times to read")
          .add_int_option("interval_sec", "interval(seconds) of output")
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

    string label = parser.get_string_variables("label", basename(argv[0]));
    string out_file_name = make_file_prefix(output_dir, label);
    out_file_name += ".samp";
    ofstream ofile(out_file_name);
    if (!ofile) {
        cout << "open output file fail: " << out_file_name << endl;
        exit(1);
    }

    int loop_times = parser.get_int_variables("loop_times", 1);
    int interval_sec = parser.get_int_variables("interval_sec", 1); 

    boost::asio::io_context io;
    SampPrinter printer(io, interval_sec, &g_file_number_readed, &g_file_size_readed, ofile);

    thread th_pr(io_context_run, &io);

    for (int i = 0; i < loop_times; i++) {
        for (auto &file_name : file_list) {
            PosixFileReader reader;
            reader.open(file_name.c_str());
            long file_size = reader.file_size();
            vector<uint8_t> buffer;
            buffer.resize(file_size);
            reader.readn(buffer.data(), buffer.size());
            g_file_number_readed.fetch_add(1);
            g_file_size_readed.fetch_add(file_size);
        }
    }

    printer.stop();
    th_pr.join();

    return 0;
}

