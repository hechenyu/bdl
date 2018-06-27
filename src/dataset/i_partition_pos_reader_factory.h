#ifndef __i_partition_pos_reader_factory_h
#define __i_partition_pos_reader_factory_h

#include <memory>
#include <string>

class PartitionPosReader;

class IPartitionPosReaderFactory {
public:
    virtual ~IPartitionPosReaderFactory();
    virtual std::shared_ptr<PartitionPosReader> get_partition_reader(const std::string &partition_path) = 0;
};

#endif
