#include <fstream>
#include <boost/algorithm/string.hpp>
#include "test_partition_util.h"
#include "error.h"

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

