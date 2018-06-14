#include "dataset_partition_reader.h"
#include "dataset_util.h"
#include "io_context.h"
#include "partition_pos_reader.h"

using namespace std;

DatasetReader::DatasetReader(shared_ptr<IOContext> io_context, const string &dataset_name): 
    io_context_(io_context), dataset_name_(dataset_name)
{
}

shared_ptr<PartitionPosReader> DatasetReader::get_partition_reader(const string &partition_name)
{
    if (partition_name == cached_partition_name_)
        return cached_partition_reader_;

    auto root_name = io_context_->root_name();
    auto file_system = io_context_->file_system();
    auto partition_path = DatasetUtil::gen_partition_path(root_name, dataset_name_, partition_name);
    cached_partition_reader_ = make_shared<PartitionPosReader>(partition_path, file_system->create_file_reader());
    cached_partition_name_ = partition_name;

    return cached_partition_reader_;
}
