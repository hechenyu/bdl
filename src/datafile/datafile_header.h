#ifndef __datafile_header_h
#define __datafile_header_h

#include <cstdint>

#pragma pack(1)
struct DatafileHeader {
    uint32_t CRC;
    uint32_t total_size;
    uint32_t blob_size;
    uint16_t metadata_size;
    uint8_t  flags[2];
    uint8_t  blob[];
};
#pragma pack()

#endif
