#ifndef __section_memory_cache_h
#define __section_memory_cache_h

#include <vector>
#include <cstdint>
#include "section_config.h"
#include "section_header.h"
#include "datafile_view.h"
#include "i_file_reader.h"
#include "i_file_writer.h"

class SectionMemoryCache {
private:
    SectionHeader *header_ = nullptr;
    std::vector<uint8_t> buffer_;
    int used_size_ = 0;

public:
    SectionMemoryCache(int section_size); 

    // reset section memory cache
    void clear_data();

    // if not data in section return true
    bool is_empty();

    // read section data from disk
    void load(IFileReader &reader); 

    // write all data to file
    void flush(IFileWriter &writer);

    // free space of buffer in bytes
    int available_size() const;

    // append file to this section, 
    // if this section has no enough space to take in this file, return false
    // if success to append file, return true
    bool append_file(const uint8_t *file_data, int file_size);

    // get file list of this section
    std::vector<DatafileView> get_file_list() const;

    // section info 
    uint32_t magic() const;
    uint32_t CRC() const;
    uint32_t version() const;
    uint32_t section_size() const;
    uint64_t timestamp() const;
    const uint8_t *files_begin() const;

private:
    uint8_t *append_ptr();
    void init_header();
    uint32_t section_body_size();
    void check_section_header();
};

#endif
