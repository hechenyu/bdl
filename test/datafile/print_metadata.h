#ifndef __print_metadata_h
#define __print_metadata_h

#include "datafile_metadata.h"
#include <string>
#include <chrono>

std::string utc_to_string(const std::chrono::system_clock::time_point &tp);
void print(const DatafileMetadata &meta, const std::string &title);

#endif
