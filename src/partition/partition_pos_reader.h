#ifndef __partition_reader_h
#define __partition_reader_h

#include <string>
#include <vector>
#include <memory>
#include "i_file_reader.h"
#include "datafile_index.h"
#include "datafile_view.h"

class PartitionPosReader {
private:
    std::shared_ptr<IFileReader> reader_;
    std::vector<uint8_t> file_cache_;

public:
    PartitionPosReader(const std::string &partition_path, std::shared_ptr<IFileReader> reader);
    ~PartitionPosReader();

    DatafileView read(DatafileIndex index);
};

#endif
