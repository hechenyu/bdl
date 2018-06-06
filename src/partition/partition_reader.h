#ifndef __partition_reader_h
#define __partition_reader_h

#include <string>
#include <memory>
#include <vector>
#include "i_file_reader.h"
#include "datafile_view.h"
#include "section_memory_cache.h"

class PartitionReader {
private:
    std::shared_ptr<IFileReader> reader_;
    std::shared_ptr<SectionMemoryCache> section_; 
    long section_index_ = 0;
    long total_section_ = 0;
    std::vector<DatafileView> datafile_list_;
    int datafile_index_ = 0;

public:
    PartitionReader(const std::string &partition_path, std::shared_ptr<IFileReader> reader);
    ~PartitionReader();

    bool has_next();
    DatafileView next();

//    void rewind();
private:
    void get_next_section();    // get next non empty section
};

#endif
