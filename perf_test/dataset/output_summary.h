#ifndef __output_summary_h
#define __output_summary_h

#include <vector>
#include <string>
#include "chrono_timer.h"

void output_summary(
        const std::vector<ChronoTimer> &open_time_list, const std::vector<ChronoTimer> &read_time_list,
        const std::string &out_file_name);

#endif
