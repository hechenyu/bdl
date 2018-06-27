#ifndef __partition_pos_reader_pool_h
#define __partition_pos_reader_pool_h

#include <unordered_map>
#include <memory>
#include <string>
#include "i_partition_pos_reader_factory.h"

class IOContext;

class PartitionPosReaderPool: public IPartitionPosReaderFactory {
private:
    std::shared_ptr<IOContext> io_context_;
    typedef std::unordered_map<std::string, std::shared_ptr<PartitionPosReader>> PartitionPosReaderMap;
    PartitionPosReaderMap cached_partition_reader_;

public:
    PartitionPosReaderPool(std::shared_ptr<IOContext> io_context); 

    std::shared_ptr<PartitionPosReader> get_partition_reader(const std::string &partition_path) override;
};

#endif
