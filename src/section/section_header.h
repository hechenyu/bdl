#ifndef __section_header_h
#define __section_header_h

#include <cstdint>

#pragma pack(1)
struct SectionHeader {
    uint32_t magic;
    uint32_t CRC;
    uint32_t version;
    uint32_t section_size;
    uint64_t timestamp;
    uint32_t reserved1;
    uint32_t reserved2;
    uint8_t  files[];
};
#pragma pack()

#endif

