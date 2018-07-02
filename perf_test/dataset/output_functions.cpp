#include <iostream>
#include <fstream>
#include <iomanip>
#include "output_functions.h"
#include "boost/format.hpp"
#include "chrono_timer_util.h"
#include "chrono_util.h"
#include "utc_to_string.h"

using namespace std;
using namespace std::chrono;

void output_summary(
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
    ofile << fmt % open_time % read_time % total_time << '\n';
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
