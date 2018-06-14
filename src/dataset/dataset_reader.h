#ifndef __dataset_reader_h
#define __dataset_reader_h

#include <memory>
#include <string>

class IOContext;
class PartitionPosReader;

class DatasetReader {
private:
    std::shared_ptr<IOContext> io_context_;
    std::string cached_partition_path_;
    std::shared_ptr<PartitionPosReader> cached_partition_reader_;

public:
    DatasetReader(std::shared_ptr<IOContext> io_context); 

    std::shared_ptr<PartitionPosReader> get_partition_reader(const std::string &partition_path);
};

#endif
