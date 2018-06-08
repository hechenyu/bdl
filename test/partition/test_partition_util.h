#ifndef __test_partition_util_h
#define __test_partition_util_h

#include <string>
#include <vector>

std::vector<std::string> get_file_list(const std::string &file_name);
std::string read_all(const std::string &file);
std::string get_suffix(const std::string &file);

#endif

