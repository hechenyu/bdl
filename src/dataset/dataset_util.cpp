#include <sstream>
#include <iomanip>
#include "dataset_util.h"
#include "dataset_config.h"

using namespace std;

std::string DatasetUtil::gen_dataset_path(const std::string &root_name, 
            const std::string &dataset_name)
{
    return root_name+"/"+dataset_name;
}

string DatasetUtil::gen_partition_path(const string &root_name, const string &dataset_name, int part_id)
{
    return root_name+"/"+dataset_name+"/"+part_id_to_string(part_id)+".part";
}

string DatasetUtil::gen_indexfile_path(const string &root_name,
            const string &dataset_name, int part_id)
{
    return root_name+"/"+dataset_name+"/"+part_id_to_string(part_id)+".idx";
}

string DatasetUtil::gen_indexfile_path(const string &root_name,
            const string &dataset_name, 
            const string &index_name, int part_id)
{
    if (index_name.empty())
        return gen_indexfile_path(root_name, dataset_name, part_id);

    return root_name+"/"+dataset_name+"/"+part_id_to_string(part_id)+"."+index_name+".idx";
}

string DatasetUtil::part_id_to_string(int part_id)
{
    ostringstream os;
    os << setfill('0') << setw(DatasetConfig::kPartIdSetW) << part_id;
    return os.str();
}

tuple<string, string> DatasetUtil::parse_dataset_index_name(const string &dataset_index_name)
{
    auto pos = dataset_index_name.rfind('.');
    if (pos == string::npos)
        return make_tuple(dataset_index_name, string(""));

    return make_tuple(dataset_index_name.substr(0, pos-1), dataset_index_name.substr(pos+1));
}

