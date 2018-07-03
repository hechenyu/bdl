#include <iostream>
#include <fstream>
#include <iomanip>
#include <numeric>
#include "output_functions.h"
#include "boost/format.hpp"
#include "chrono_timer_util.h"
#include "chrono_util.h"
#include "utc_to_string.h"

using namespace std;
using namespace std::chrono;

string make_file_prefix(const string &dir, const string &title)
{
    string out_file_name;
    if (!dir.empty())
        out_file_name += dir + "/";
    out_file_name += title;
    out_file_name += ".";
    out_file_name += utc_to_string(system_clock::now());

    return out_file_name;
}

uint64_t total_file_size(const std::vector<long> &file_size_list)
{
    return accumulate(file_size_list.begin(), file_size_list.end(), uint64_t(0));
}

void output_summary(const std::vector<long> &file_size_list,
        const vector<ChronoTimer> &open_time_list, const vector<ChronoTimer> &read_time_list,
        const string &out_file_name, const string &label)
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
    auto total_size = total_file_size(file_size_list);
    auto io_rate = total_size / total_time;

    const std::string fmt_str = R"({"label": %s, "open_time usec:": %.2f, "read_time usec": %.2f, "total_time usec": %.2f, "io_rate MB/s": %.2f, "file_number" : %d})";
    boost::format fmt(fmt_str);
    ofile << fmt % label % open_time % read_time % total_time % io_rate % file_size_list.size() << '\n';
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

void output_summary(const ChronoTimer &timer, int file_number, uint64_t total_size, const std::string &out_file_name)
{
    ofstream ofile;
    ofile.open(out_file_name);
    if (!ofile) {
        cout << "open output file fail: " << out_file_name << endl;
        exit(1);
    }

    double total_time = duration_to_microseconds(timer.elapsed());
    auto io_rate = total_size / total_time;
    auto iops = file_number / total_time * 1000 * 1000;

    const std::string fmt_str = R"({"total_time usec": %f, "io_rate MB/s": %f, "iops file/s": %f})";
    boost::format fmt(fmt_str);
    ofile << fmt % total_time % io_rate % iops << '\n';
}
