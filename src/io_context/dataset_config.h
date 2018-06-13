#ifndef __dataset_config_h
#define __dataset_config_h

#include <string>

class DatasetConfig {
public:
    static const int kMinPartId = 0;
    static const int kMaxPartId = 9999;
    static const int kPartIdSetW = 4;
    static const std::string kPartFileSuffix;
};

#endif
