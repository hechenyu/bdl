#ifndef __dataset_partition_reader_h
#define __dataset_partition_reader_h

#include <memory>
#include <string>

class IOContext;
class PartitionPosReader;

class DatasetReader {
private:
    std::shared_ptr<IOContext> io_context_;
    std::string dataset_name_;
    std::string cached_partition_name_;
    std::shared_ptr<PartitionPosReader> cached_partition_reader_;

public:
    DatasetReader(std::shared_ptr<IOContext> io_context, const std::string &dataset_name); 

    std::shared_ptr<PartitionPosReader> get_partition_reader(const std::string &partition_name);
};

#endif
