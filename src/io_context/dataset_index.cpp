#include "dataset_index.h"

using namespace std;

DatasetIndex::DatasetIndex(IOContext *io_context, string path, string open_flag):
    DatasetIndex(io_context, path, open_flag, 0, 9999)
{
}

DatasetIndex::DatasetIndex(IOContext *io_context, string path, string open_flag, int min_part_id, int max_part_id):
    io_context_(io_context), min_part_id_(min_part_id), max_part_id_(max_part_id)
{
    std::tie(dataset_name_, index_name_) = parse_path(path);
}

tuple<string, string> DatasetIndex::parse_path(const string &path)
{
    auto pos = path.rfind('.');
    if (pos == string::npos)
        return make_tuple(path, string(""));

    return make_tuple(path.substr(0, pos-1), path.substr(pos+1));
}
