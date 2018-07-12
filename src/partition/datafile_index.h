#ifndef __datafile_index_h
#define __datafile_index_h

#include <cstdint>

struct DatafileIndex {
    DatafileIndex() = default;
    DatafileIndex(uint32_t offset, uint32_t file_size):
        offset(offset), file_size(file_size) {}

    uint32_t offset = 0;
    uint32_t file_size = 0;
};

inline
bool operator ==(const DatafileIndex &lhs, const DatafileIndex &rhs)
{
    return (lhs.offset == rhs.offset) && (lhs.file_size == rhs.file_size);
}

#endif
