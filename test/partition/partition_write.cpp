#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <memory>
#include <boost/algorithm/string.hpp>
#include "error.h"
#include "posix_file_writer.h"
#include "partition_writer.h"

using namespace std;
using namespace boost;

vector<string> get_file_list(const string &file_name)
{
    ifstream ifile;
    ifile.open(file_name);
    if (!ifile) {
        err_quit("open list file fail, file name: %s", file_name.c_str());
    }

    vector<string> file_list;
    string str;
    while (getline(ifile, str)) {
        trim(str);
        file_list.push_back(str);
    }

    return std::move(file_list);
}

string read_all(const string &file)
{
    ifstream in(file);    
    istreambuf_iterator<char>  beg(in),  end;    
    string  str(beg,  end);    
    return std::move(str);
}

string get_suffix(const string &file)
{
    size_t found = file.rfind('.');
    if (found != string::npos)
        return file.substr(found+1);
    else
        return "";
}

int main(int argc, char *argv[])
{
    if (argc != 3) {
        cerr << "usage: " << argv[0] << " filelist_file ofile\n";
        return 1;
    }

    auto file_writer = make_shared<PosixFileWriter>();
    PartitionWriter partition_writer(argv[2], file_writer);

    auto file_list = get_file_list(argv[1]);
    for (auto &file_name : file_list) {
        auto file_data = read_all(file_name);
        auto file_type = get_suffix(file_name);
        partition_writer.write(file_name, file_type, (uint8_t *) file_data.data(), file_data.size());
        cout << "process " << file_type << " type: " << file_name << " ok" << endl;
    }

    return 0;
}

