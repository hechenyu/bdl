#ifndef __dataset_direct_reader_h
#define __dataset_direct_reader_h

#include <memory>
#include <vector>

#include "i_partition_pos_reader_factory.h"
#include "dataset_index_item.h"
#include "dataset_file_read_handle.h"

class IOContext;
class PartitionPosReader;

class DatasetDirectReader {
private:
    std::shared_ptr<IOContext> io_context_;
    std::shared_ptr<IPartitionPosReaderFactory> partition_pos_reader_factory_;

public:
    typedef DatasetFileReadHandle FileReadHandle;

public:
    DatasetDirectReader(std::shared_ptr<IOContext> io_context);

    FileReadHandle openFile(DatasetIndexItem index_item);   // open file for read only
};

#endif

