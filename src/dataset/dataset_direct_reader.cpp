#include "dataset_direct_reader.h"
#include "partition_pos_reader_factory.h"
#include "partition_pos_reader_pool.h"

using namespace std;

DatasetDirectReader::DatasetDirectReader(shared_ptr<IOContext> io_context): io_context_(io_context)
{
#ifdef USE_PARTITION_POS_READER_POOL
    partition_pos_reader_factory_ = make_shared<PartitionPosReaderPool>(io_context_);
#else
    partition_pos_reader_factory_ = make_shared<PartitionPosReaderFactory>(io_context_);
#endif
}

DatasetDirectReader::FileReadHandle DatasetDirectReader::openFile(DatasetIndexItem index_item)
{
    auto partition_reader = partition_pos_reader_factory_->get_partition_reader(index_item.partition_path());
    return FileReadHandle(partition_reader, index_item);
}

DatasetDirectReader::FileReadHandle DatasetDirectReader::openFile(std::string serialized_item)
{
    return openFile(DatasetIndexItem(serialized_item)); 
}
