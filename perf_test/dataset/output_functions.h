#ifndef __output_functions_h
#define __output_functions_h

#include <vector>
#include <string>
#include "chrono_timer.h"

void output_summary(const std::vector<long> &file_size_list,
        const std::vector<ChronoTimer> &open_time_list, const std::vector<ChronoTimer> &read_time_list,
        const std::string &out_file_name);

void output_detail(const std::vector<std::string> &file_list, const std::vector<long> &file_size_list,
        const std::vector<ChronoTimer> &open_time_list, const std::vector<ChronoTimer> &read_time_list,
        const std::string &out_file_name);

#endif
