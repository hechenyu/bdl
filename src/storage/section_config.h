#ifndef __section_config_h
#define __section_config_h

#include <cstdint>

class SectionConfig {
public:
    const static int kMaxFileSize = 16*1024*1024-32;
    const static uint32_t kSectionMagic = 0x1234abcd;
    const static uint32_t kSectionVersion = 1;
};

#endif

