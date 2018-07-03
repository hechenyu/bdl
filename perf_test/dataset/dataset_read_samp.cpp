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
#include "io_context.h"
#include "dataset_index.h"
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
          .add_option("readbuf")
          .add_int_option("loop_times", "loop times to read")
          .add_int_option("interval_sec", "interval(seconds) of output")
          .add_string_option("seed", "shuffle seed")
          .add_string_option("conf,f", "configure file")
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
        io_conf.read_buffered = true;
    } else {
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

    int loop_times = parser.get_int_variables("loop_times", 1);
    int interval_sec = parser.get_int_variables("interval_sec", 1); 

    boost::asio::io_context io;
    SampPrinter printer(io, interval_sec, &g_file_number_readed, &g_file_size_readed, cout);

    thread th_pr(io_context_run, &io);
    
    for (int i = 0; i < loop_times; i++) {
//        ChronoTimer timer;
//        timer.start();
        for (auto item: index_item_list) {
            auto datafile = index.openFile(item);
            auto data = datafile.readAll();
            g_file_number_readed.fetch_add(1);
            g_file_size_readed.fetch_add(data.size());
        }
//        timer.stop();

#if 0
        // ===================== 将结果保存到文件中 ============================
        string label = parser.get_string_variables("label", basename(argv[0]));
        string out_file_name = make_file_prefix(output_dir, label);


        output_summary(timer, g_file_number_readed, g_file_size_readed, out_file_name+".json");
#endif
    }

    printer.stop();
    th_pr.join();

    return 0;
}
