#ifndef __partition_pos_reader_factory_h
#define __partition_pos_reader_factory_h

#include <memory>
#include <string>
#include "i_partition_pos_reader_factory.h"

class IOContext;

class PartitionPosReaderFactory: public IPartitionPosReaderFactory {
private:
    std::shared_ptr<IOContext> io_context_;
    std::string cached_partition_path_;
    std::shared_ptr<PartitionPosReader> cached_partition_reader_;

public:
    PartitionPosReaderFactory(std::shared_ptr<IOContext> io_context); 

    std::shared_ptr<PartitionPosReader> get_partition_reader(const std::string &partition_path) override;
};

#endif
