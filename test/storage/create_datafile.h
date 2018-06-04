#ifndef __create_datafile_h
#define __create_datafile_h

#include <string>
#include <vector>
#include <map>

std::vector<uint8_t> create_datafile(
        const std::string &etag, const std::string &content_type,
        const std::map<std::string, std::string> attrs,
        const std::string &blob);

#endif

