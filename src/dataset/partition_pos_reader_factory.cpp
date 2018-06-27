#include "partition_pos_reader_factory.h"
#include "dataset_util.h"
#include "io_context.h"
#include "partition_pos_reader.h"

using namespace std;

PartitionPosReaderFactory::PartitionPosReaderFactory(shared_ptr<IOContext> io_context): io_context_(io_context)
{
}

shared_ptr<PartitionPosReader> PartitionPosReaderFactory::get_partition_reader(const string &partition_path)
{
    if (partition_path == cached_partition_path_)
        return cached_partition_reader_;

    auto file_system = io_context_->file_system();
    cached_partition_reader_ = make_shared<PartitionPosReader>(partition_path, file_system->create_file_reader());
    cached_partition_path_ = partition_path;

    return cached_partition_reader_;
}
