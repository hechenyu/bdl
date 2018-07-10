#ifndef __dataset_file_read_handle_h 
#define __dataset_file_read_handle_h 

#include <memory>
#include <vector>
#include <stdint.h>

#include "dataset_index_item.h"

class PartitionPosReader;

class DatasetFileReadHandle {
private:
    std::shared_ptr<PartitionPosReader> partition_reader_;
    DatasetIndexItem index_item_;

public:
    DatasetFileReadHandle(std::shared_ptr<PartitionPosReader> partition_reader, 
            DatasetIndexItem index_item);

    std::vector<uint8_t> readAll();
};

#endif
