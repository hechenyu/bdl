#include "partition_pos_reader_pool.h"
#include "dataset_util.h"
#include "io_context.h"
#include "partition_pos_reader.h"

using namespace std;

PartitionPosReaderPool::PartitionPosReaderPool(shared_ptr<IOContext> io_context): io_context_(io_context)
{
}

shared_ptr<PartitionPosReader> PartitionPosReaderPool::get_partition_reader(const string &partition_path)
{
    auto iter = cached_partition_reader_.find(partition_path);
    if (iter == cached_partition_reader_.end()) {
        auto file_system = io_context_->file_system();
        cached_partition_reader_[partition_path] = 
            make_shared<PartitionPosReader>(partition_path, file_system->create_file_reader());
    }

    return cached_partition_reader_[partition_path];
}
