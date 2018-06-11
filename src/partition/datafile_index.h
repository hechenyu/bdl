#ifndef __datafile_index_h
#define __datafile_index_h

#include <cstdint>

struct DatafileIndex {
    uint32_t offset;
    uint32_t file_size;
};

#endif
