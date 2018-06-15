#ifndef __partition_writer_h
#define __partition_writer_h

#include <string>
#include <memory>
#include "datafile_index.h"
#include "i_file_reader.h"
#include "i_file_writer.h"
#include "datafile_metadata.h"
#include "section_memory_cache.h"

class PartitionWriter {
private:
    std::shared_ptr<IFileWriter> writer_;
    std::shared_ptr<SectionMemoryCache> section_; 
    long section_index_ = 0;

public:
    // open file for write and truncate
    PartitionWriter(const std::string &partition_path, std::shared_ptr<IFileWriter> writer);

    // open file for append
    PartitionWriter(const std::string &partition_path, std::shared_ptr<IFileWriter> writer, std::shared_ptr<IFileReader> reader);

    ~PartitionWriter();

    // write file to partition
    DatafileIndex write(const std::string &file_name, const std::string &file_type,
            const uint8_t *file_data, int file_size, 
            const DatafileMetadata::AttrMap &attrs = DatafileMetadata::AttrMap());
};

#endif
