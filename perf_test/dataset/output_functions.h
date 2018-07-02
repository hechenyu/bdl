#ifndef __output_functions_h
#define __output_functions_h

#include <vector>
#include <string>
#include "chrono_timer.h"

void output_summary(
        const std::vector<ChronoTimer> &open_time_list, const std::vector<ChronoTimer> &read_time_list,
        const std::string &out_file_name);

void output_detail(const vector<string> &file_list, const vector<long> &file_size_list,
        const vector<ChronoTimer> &open_time_list, const vector<ChronoTimer> &read_time_list,
        const string &out_file_name);

#endif
