#ifndef __partition_writer_h
#define __partition_writer_h

#include <string>
#include <memory>
#include "i_file_writer.h"
#include "datafile_metadata.h"
#include "section_memory_cache.h"

class PartitionWriter {
private:
    std::string path_;
    std::shared_ptr<IFileWriter> writer_;
    std::shared_ptr<SectionMemoryCache> section_; 
    long section_index_ = 0;

public:
    PartitionWriter(const std::string &partition_path, std::shared_ptr<IFileWriter> writer);
    ~PartitionWriter();

    // write file to partition
    void write(const std::string &file_name, const std::string &file_type,
            const uint8_t *file_data, int file_size, const DatafileMetadata::AttrMap &attrs);
};

#endif
