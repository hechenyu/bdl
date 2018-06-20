#ifndef __write_file_h
#define __write_file_h

#include <string>
#include <fstream>

template <typename SeqT>
void write_file(const std::string &datafile_name, const SeqT &data)
{
    std::ofstream ofile(datafile_name);
    ofile.write((const char *) data.data(), data.size());
}

#endif
